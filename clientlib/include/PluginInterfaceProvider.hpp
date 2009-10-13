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

#include "PluginInterface.hpp"
#include "FileUtils.hpp"
#include <string>
#include <vector>

namespace openSpeak
{

    namespace Client
    {

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

            /** \brief The destructor of the PluginInterfaceProvider class
             *
             *  Cleans up all PluginInterfaces
             */
            virtual ~PluginInterfaceProvider (void);

            /** \brief Add a class to the interface by loading it from the Plugin
             *  \param plugin The plugin to load from
             *  \throw Throws an exception if the pointer is null
             */
            void addClass (PluginInterface* plugin);

            /** \brief Remove a class from the interface
             *  \param plugin The plugin which contains the class
             *  \throw Throws an exception if the pointer is null
             */
            void removeClass (PluginInterface *plugin);

            /** \brief Get a list with the names of all interfaces
             *  \return List with the names of all interfaces
             */
            StringVector getInterfaces (void);

            /** \brief Use the specified interface for all operations
             *  \param name The name of the interface to use
             *  \throw Throws an exception if the interface is unknown
             */
            virtual void useInterface (const std::string &name) = 0;

            /** \brief Use a "default" interface
             *  \throw Throws an exception if no interface is available
             *          or the interface fails to load.
             *
             *  Which interface to use is in the responsibility of the
             *  subclass developers. Possiblities include using the first one
             *  in the vector or including a list of favorites.
             */
            virtual void useDefaultInterface (void) = 0;

            /** \brief Check if an interface is loaded
             *  \return True if an interface is loaded
             */
            virtual bool hasInterface (void) const = 0;

            std::string     Type;       /**< The type of interface to provide */

         protected:
            InterfaceVector mIFaces;    /**< Vector containing all interfaces */
        };

    }

}

#endif
