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

#ifndef __OS_CLIENT_PLUGIN_HPP__
#define __OS_CLIENT_PLUGIN_HPP__

#include "EventMgr.hpp"
#include <string>

namespace openSpeak
{

    namespace Client
    {

        /** \class Plugin
         *  \brief Represents a plugin
         *
         *  The plugin class contains all informations and important functions
         *  for a plugin to work.
         */
        class Plugin
        {
         public:
            /** \brief Vector to save all events in */
            typedef std::vector <std::pair <std::string, EventMgr::EventFunction> >
                    EventVector;

            /** \brief Vector to save all classes in */
            typedef std::vector <std::pair <std::string, void*> > ClassVector;
            
            /** \brief Default empty constructor */
            Plugin (void) { }

            /** \brief Initialize the plugin with the most important informations
             *  \param name The name of the plugin
             *  \param version The current version of the plugin
             *  \param author The author of the plugin
             */
            Plugin (const std::string &name, const std::string &version,
                    const std::string &author)
                    : Name (name), Version (version), Author (author)
            {
                
            }

            /** \brief Register a function with an event
             *  \param event The event to register for
             *  \param function The function to register with the event
             */
            void registerEvent (const std::string &event,
                    EventMgr::EventFunction function)
            {
                Events.push_back (std::make_pair (event, function));
            }

            /** \brief Register a class with the specific manager
             *  \param type The type of class to register
             *  \param classptr Pointer to the class
             */
            void registerClass (const std::string &type, void* classptr)
            {
                Classes.push_back (std::make_pair (type, classptr));
            }

            std::string Name;       /**< The name of the plugin */
            std::string Version;    /**< The version of the plugin */
            std::string Author;     /**< The author of the plugin */
            
            std::string SOName;     /**< Name of the shared object file */
            void* Handle;           /**< Handle from the dlopen function */
            bool Loaded;            /**< Is the plugin loaded? */

            EventVector Events;     /**< Vector containing all events */
            ClassVector Classes;    /**< Vector containing all classes */
        };

    }

}

#endif
