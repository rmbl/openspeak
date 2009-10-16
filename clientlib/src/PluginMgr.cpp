/**  openSpeak - The open source VoIP application
  *  Copyright (C) 2006 - 2009  openSpeak Team (http://openspeak-project.org)
  *
  *  This program is free software; you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation; either version 2 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License along
  *  with this program; if not, write to the Free Software Foundation, Inc.,
  *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
  */

#include "PluginMgr.hpp"
#include "Exception.hpp"
#include "FileUtils.hpp"
#include "Types.hpp"
#include "LogMgr.hpp"
#include "PluginInterfaceProvider.hpp"
#include "NLS.hpp"

#if defined (OS_POSIX_COMPAT)
#   include <dlfcn.h>
#elif defined (OS_PLATFORM_WIN32)
#	include <windows.h>
#	define dlclose FreeLibrary
#	define dlsym GetProcAddress
#	define dlopen(x,y) LoadLibrary(x)
#endif


namespace openSpeak
{

    namespace Client
    {

        PluginMgr::PluginMgr ()
        {
            mEventMgr = 0;
        }

        PluginMgr::~PluginMgr ()
        {
        /* Destroy all instances and close all handles when exiting */
            for (PluginMap::const_iterator it = mPlugins.begin ();
                    it != mPlugins.end (); ++it)
            {
                dlhandle_t handle = it->second->Handle;
                it->second->Destroy (it->second);
                dlclose (handle);
            }
        }

        void PluginMgr::loadPlugins (Config* cfg)
        {
        /* Check if there is an eventmgr specified */
            if (!mEventMgr)
                EXCEPTION (_("Can't load plugins without an event mgr registered"));

        /* Search for .so files in the libdir using glob */
            std::string plugindir = FileUtils::getLibPath ();
            StringVector plugins = FileUtils::findFiles (plugindir + "*.so");

        /* Loop through all found files and load them */
            for (StringVector::const_iterator it = plugins.begin ();
                    it != plugins.end (); ++it)
            {
                dlhandle_t handle = dlopen ((*it).c_str (), RTLD_LAZY);
                if (!handle)
                {
                    LOG_ERROR (format (_("Loading plugin %1% failed")) % *it);
                    continue;
                }
            /* Get the create and destroy functions and create the plugin */
                Plugin::createFunc *create = (Plugin::createFunc*)dlsym (
                        handle, "createPlugin");
                Plugin::destroyFunc *destroy = (Plugin::destroyFunc*)dlsym (
                        handle, "destroyPlugin");
                if (!create || !destroy)
                {
                    LOG_ERROR (format (_("Plugin %1% is not a valid openSpeak Plugin")) % *it);
                    dlclose (handle);
                    continue;
                }

                Plugin *plug = create ();
                plug->Handle = handle;
                plug->Loaded = false;
                plug->Destroy = destroy;

            /* Strip the .so before saving */
                plug->SOName = *it;
                std::string::size_type index = plug->SOName.find_last_of ('/');
                plug->SOName = plug->SOName.substr (index + 1,
                        plug->SOName.size () - index - 4);
                mPlugins[plug->SOName] = plug;

                LOG_DEBUG (format (_("Loaded plugin %1% (%2%) %3% from %4%")) % 
                        plug->Name % plug->SOName % plug->Version % plug->Author);
            }

        /* Check each of the libraries if they're enabled and load them if they are */
            for (PluginMap::const_iterator it = mPlugins.begin ();
                    it != mPlugins.end (); ++it)
            {
                if (StringUtils::toBool (cfg->getOption
                        ("plugin." + it->second->SOName + ".enable")))
                    loadPlugin (it->second->SOName);
            }
        }

        void PluginMgr::loadPlugin (const std::string &plugin)
        {
        /* Check if the plugin is loaded */
            PluginMap::const_iterator it = mPlugins.find (plugin);
            if (it == mPlugins.end ())
                EXCEPTION (format (_("Unknown plugin %1%")) % plugin);
            else if (it->second->Loaded)
                return;

            LOG_DEBUG (format (_("Activating plugin %1% (%2% events, %3% classes)")) %
                    plugin % it->second->Events.size () % it->second->Classes.size ());

        /* Load it if its not, begin with the events */
            for (Plugin::EventVector::const_iterator i = it->second->Events.begin ();
                    i != it->second->Events.end (); ++i)
                it->second->EventConnections.push_back (mEventMgr->connect (
                        i->first, i->second));

        /* And continue with the classes */
            for (Plugin::ClassVector::const_iterator i = it->second->Classes.begin ();
                    i != it->second->Classes.end (); ++i)
            {
                PluginIFaceMap::const_iterator iface = mIFaces.find (i->first);
                if (iface == mIFaces.end ())
                    EXCEPTION (format (_("Unknown interface '%1%'")) % i->first);
                
                iface->second->addClass (i->second);
            }

        }

        void PluginMgr::unloadPlugin (const std::string &plugin)
        {
        /* Check if the plugin is unloaded */
            PluginMap::const_iterator it = mPlugins.find (plugin);
            if (it == mPlugins.end ())
                EXCEPTION (format (_("Unknown plugin %1%")) % plugin);
            else if (!it->second->Loaded)
                return;

        /* Unload it if its not, begin with the events */
            for (Plugin::EventConnectionVector::const_iterator
                    i = it->second->EventConnections.begin ();
                    i != it->second->EventConnections.end (); ++i)
                mEventMgr->disconnect (*i);

        /* And continue with the classes */
            for (Plugin::ClassVector::const_iterator i = it->second->Classes.begin ();
                    i != it->second->Classes.end (); ++i)
            {
                PluginIFaceMap::const_iterator iface = mIFaces.find (i->first);
                if (iface == mIFaces.end ())
                    EXCEPTION (format (_("Unknown interface '%1%' found while unloading")) % i->first);

                iface->second->removeClass (i->second);
            }
        }
        
        void PluginMgr::registerEventMgr (EventMgr *ptr)
        {
            if (!ptr)
                EXCEPTION (_("Recieved a null pointer"));
                
            mEventMgr = ptr;
        }
        
        void PluginMgr::registerIFaceProvider (PluginInterfaceProvider *provider)
        {
            if (!provider)
                EXCEPTION (_("Recieved a null pointer"));
            else if (provider->Type.empty ())
                EXCEPTION (_("Recieved pointer with empty type"));
            
            mIFaces.insert (std::make_pair (provider->Type, provider));
        }

    }

}
