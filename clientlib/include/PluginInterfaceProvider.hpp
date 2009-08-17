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

#ifndef __OS_CLIENT_PLUGIN_INTERFACE_PROVIDER_HPP__
#define __OS_CLIENT_PLUGIN_INTERFACE_PROVIDER_HPP__

#include <string>
#include <vector>

namespace openSpeak
{

    namespace Client
    {
        
        class PluginInterface
        {
        };
 
        /** \class PluginInterfaceProvider 
         *  \brief Provides plugin classes with a specified interface
         * 
         *  The PluginInterfaceProvider class is used as a base class for
         *  classes providing an interface for plugins to use.
         */
        class PluginInterfaceProvider
        {
         protected:
            /** \brief The vector in which all classes are stored */
            typedef std::vector <PluginInterface*> InterfaceVector;
            
         public:
            /** \brief The constructor of the PluginInterfaceProvider class
             *  \param type The typename of the provided interface
             */
            PluginInterfaceProvider (const std::string &type);
            
            /** \brief Add a class to the interface by loading it from the Plugin
             *  \param plugin The plugin to load from
             */
            void addClass (PluginInterface* plugin);


            /** \brief Remove a class from the interface
             *  \param plugin The plugin which contains the class
             */
            void removeClass (PluginInterface *plugin);

            std::string     Type;       /**< The type of interface to provide */
            
         protected:
            InterfaceVector mIFaces;    /**< Vector containing all interfaces */
        };
    
    }

}

#endif
