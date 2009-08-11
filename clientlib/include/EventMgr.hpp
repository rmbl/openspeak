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

#ifndef __OS_CLIENT_EVENT_MGR_HPP__
#define __OS_CLIENT_EVENT_MGR_HPP__

#include "Event.hpp"

#include <string>
#include <map>
#include <boost/signal.hpp>

namespace openSpeak
{

    namespace Client
    {

        /** \class EventMgr
         *  \brief Manages registered events and calls connected functions
         * 
         *  The EventMgr class manages the registered events and calls the
         *  associated functions when an event gets fired.
         */
        class EventMgr
        {
            friend class Plugin;
            
         private:
            /** \brief The type all event functions should've */
            typedef void (*EventFunction)(Event);
         
            /** \brief The map where all signals are stored */
            typedef std::map <std::string, boost::signal <void (Event)>* > EventMap;
            
         public:
            /** \brief The constructor of the EventMgr class */
            EventMgr (void);
            
            /** \brief The destructor of the EventMgr class */
            ~EventMgr (void);
            
            /** \brief Create a new event 
             *  \param event The name of the event
             */
            void create (const std::string &event);
            
            /** \brief Connect a function to an event 
             *  \param event The event to connect to
             *  \param function The function to connect to the event
             */
            void connect (const std::string &event, EventFunction function);
            
            /** \brief Disconnect a function from an event
             *  \param event The event to disconnect the function from
             *  \param function The function to disconnect
             */
            void disconnect (const std::string &event, EventFunction function = 0);
            
            /** \brief Fire an event and call all connected functions
             *  \param event The event to fire
             *  \param evt The event supplied as the argument
             */
            void fireEvent (const std::string &event, Event evt);
         
         private:
            EventMap mEvents;   /**< The map containing all events */
        };

    }

}

#endif
