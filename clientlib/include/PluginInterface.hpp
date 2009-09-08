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

#ifndef __OS_CLIENT_PLUGIN_INTERFACE_HPP__
#define __OS_CLIENT_PLUGIN_INTERFACE_HPP__

#include "Platform.hpp"
#include <string>

namespace openSpeak
{

    namespace Client
    {
        
        /** \class PluginInterface
         *  \brief Baseclass used to implement PluginInterfaces
         */
        class DLL_SPEC PluginInterface
        {
         public:
            /** \brief The constructor of the PluginInterface class
             *  \param name The name to use in config dialogs
             */
            PluginInterface (const std::string &name)
                    : Name (name)
            {                
            }
            
            /** \brief The destructor for the PluginInterface class */
            virtual ~PluginInterface () { }    
            
            std::string Name;   /**< The name to use in config dialogs */
        };
    
    }
    
}

#endif
