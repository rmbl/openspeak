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
  
#ifndef __OS_CLIENT_PLUGIN_MGR_HPP__
#define __OS_CLIENT_PLUGIN_MGR_HPP__

#include "Singleton.hpp"
#include "Config.hpp"
#include "Plugin.hpp"

#include <string>
#include <map>

namespace openSpeak
{
    
    namespace Client
    {

        class PluginMgr : public Singleton <PluginMgr>
        {
         private:
            /** \brief Map in which all plugin informations are saved */
            typedef std::map <std::string, Plugin*> PluginMap;
            
         public:         
            /** \brief The deconstructor of the PluginMgr class */
            ~PluginMgr (void);
         
            /** \brief Load all plugins
             * 
             *  Load all plugins in the lib directory and enable the ones that
             *  are also enabled in the configuration file.
             * 
             *  \param cfg The config file
             */
            void loadPlugins (Config *cfg);
         
            /** \brief Load the plugin
             *  \param plugin The name of the plugin and its .so file
             */
            void loadPlugin (const std::string &plugin);
         
            /** \brief Unload the plugin
             *  \param plugin The name of the plugin and its .so file
             */
            void unloadPlugin (const std::string &plugin);
        
         private:
            PluginMap mPlugins;
        };

    }

}

#endif
