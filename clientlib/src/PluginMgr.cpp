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

#ifdef OS_POSIX_COMPAT
#   include <glob.h>
#   include <dlfcn.h>
#endif

namespace openSpeak
{

    namespace Client
    {
        
        PluginMgr::~PluginMgr ()
        {
        /* Close all handles when exiting */
            for (PluginMap::const_iterator it = mPlugins.begin ();
                    it != mPlugins.end (); ++it)
                dlclose (it->second->Handle);
        }

        void PluginMgr::loadPlugins (Config* cfg)
        {
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
                        EXCEPTION ("Loading plugin " + std::string (plugins.gl_pathv[i]) + " failed");

                /* Get the getPlugin () function and save the Plugin* in the map */
                    Plugin* (*func)(void) = (Plugin* (*)())dlsym (handle, "getPlugin");
                    if (!func)
                        EXCEPTION ("Plugin " + std::string (plugins.gl_pathv[i]) +
                                " is not a valid openSpeak Plugin");

                    Plugin* plug = func ();
                    plug->Handle = handle;
                    plug->Loaded = false;

                /* Strip the .so before saving */
                    std::string soname = plugins.gl_pathv[i];
                    soname = soname.substr (0, soname.size () - 4);
                    plug->SOName = soname;
                    mPlugins[soname] = plug;

                    LogMgr::getSingleton ()->getDefaultLog ()->logMsg (
                            "Loaded plugin " + plug->Name + " " + plug->Version +
                            " from " + plug->Author, Log::LVL_DEBUG);
                }
            }

            globfree (&plugins);

            // Check each of the libraries if they're enabled and load them if they are
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
            if (it->second->Loaded)
                return;

        /* Load it if its not */
            //TODO: Add events and classes
        }

        void PluginMgr::unloadPlugin (const std::string &plugin)
        {
        /* Check if the plugin is unloaded */
            PluginMap::const_iterator it = mPlugins.find (plugin);
            if (it == mPlugins.end ())
                EXCEPTION ("Unknown plugin " + plugin);
            if (!it->second->Loaded)
                return;

        /* Unload it if its not */
            //TODO: Remove events and classes
        }

    }

}
