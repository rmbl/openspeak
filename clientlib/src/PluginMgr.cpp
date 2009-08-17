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

#ifdef OS_POSIX_COMPAT
#   include <glob.h>
#   include <dlfcn.h>
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
                void* handle = it->second->Handle;
                it->second->Destroy (it->second);
                dlclose (handle);
            }
        }

        void PluginMgr::loadPlugins (Config* cfg)
        {
        /* Check if there is an eventmgr specified */
            if (!mEventMgr)
                EXCEPTION ("Can't load plugins without an event mgr registered");

        /* Search for .so files in the libdir using glob */
            std::string plugindir = FileUtils::getLibPath ();
            glob_t plugins;
            int ret = glob (std::string (plugindir + "*.so").c_str (),
                    GLOB_ERR, 0, &plugins);

        /* Return or throw an exception if it wasn't successful */
            if (ret == GLOB_ABORTED || ret == GLOB_NOSPACE)
                EXCEPTION ("Searching for plugins failed");
            else if (ret != 0 || plugins.gl_pathc == 0)
                return;

        /* Loop through all found files and load them */
            for (uint i = 0; i < plugins.gl_pathc; ++i)
            {
                if (plugins.gl_pathv[i])
                {
                    void* handle = dlopen (plugins.gl_pathv[i], RTLD_LAZY);
                    if (!handle)
                    {
                        LogMgr::getSingleton ()->getDefaultLog ()->logMsg (
                                "Loading plugin " + std::string (plugins.gl_pathv[i]) +
                                " failed", Log::LVL_ERROR);
                        continue;
                    }
                /* Get the create and destroy functions and create the plugin */
                    Plugin::createFunc *create = (Plugin::createFunc*)dlsym (
                            handle, "createPlugin");
                    Plugin::destroyFunc *destroy = (Plugin::destroyFunc*)dlsym (
                            handle, "destroyPlugin");
                    if (!create || !destroy)
                    {
                        LogMgr::getSingleton ()->getDefaultLog ()->logMsg (
                                "Plugin " + std::string (plugins.gl_pathv[i]) +
                                " is not a valid openSpeak Plugin", Log::LVL_ERROR);
                        dlclose (handle);
                        continue;
                    }

                    Plugin *plug = create ();
                    plug->Handle = handle;
                    plug->Loaded = false;
                    plug->Destroy = destroy;

                /* Strip the .so before saving */
                    plug->SOName = plugins.gl_pathv[i];
                    std::string::size_type index = plug->SOName.find_last_of ('/');
                    plug->SOName = plug->SOName.substr (index + 1,
                            plug->SOName.size () - index - 4);
                    mPlugins[plug->SOName] = plug;

                    LogMgr::getSingleton ()->getDefaultLog ()->logMsg (
                           "Loaded plugin " + plug->Name + " (" +plug->SOName + ") " +
                            plug->Version + " from " + plug->Author, Log::LVL_DEBUG);
                }
            }

            globfree (&plugins);

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
                EXCEPTION ("Unknown plugin " + plugin);
            else if (it->second->Loaded)
                return;

            LogMgr::getSingleton ()->getDefaultLog ()->logMsg ("Activating plugin "+plugin+
                    " with " + StringUtils::toString (it->second->Events.size ()) + " events", Log::LVL_DEBUG);

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
                    EXCEPTION ("Unknown interface '" + i->first + "'");
                
                iface->second->addClass (i->second);
            }

        }

        void PluginMgr::unloadPlugin (const std::string &plugin)
        {
        /* Check if the plugin is unloaded */
            PluginMap::const_iterator it = mPlugins.find (plugin);
            if (it == mPlugins.end ())
                EXCEPTION ("Unknown plugin " + plugin);
            else if (!it->second->Loaded)
                return;

        /* Unload it if its not */
            for (Plugin::EventConnectionVector::const_iterator
                    i = it->second->EventConnections.begin ();
                    i != it->second->EventConnections.end (); ++i)
                mEventMgr->disconnect (*i);
            //TODO: Add classes
        }
        
        void PluginMgr::registerEventMgr (EventMgr *ptr)
        {
            if (!ptr)
                EXCEPTION ("Recieved a null pointer");
                
            mEventMgr = ptr;
        }
        
        void PluginMgr::registerIFaceProvider (PluginInterfaceProvider *provider)
        {
            if (!provider)
                EXCEPTION ("Recieved a null pointer");
            else if (provider->Type.empty ())
                EXCEPTION ("Recieved pointer with empty type");
            
            mIFaces.insert (std::make_pair (provider->Type, provider));
        }

    }

}
