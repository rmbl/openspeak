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

#include "Exception.hpp"
#include "EventMgr.hpp"
#include "LogMgr.hpp"
#include "NLS.hpp"

#include <boost/assign/ptr_map_inserter.hpp>

namespace openSpeak
{

    namespace Client
    {

        EventMgr::EventMgr ()
        {

        }

        EventMgr::~EventMgr ()
        {

        }

        void EventMgr::create (const std::string &event)
        {
            EventMap::const_iterator it = mEvents.find (event);
            if (it == mEvents.end ())
                boost::assign::ptr_map_insert (mEvents) (event);
        }

        EventMgr::EventConnection EventMgr::connect (const std::string &event,
                EventFunction function)
        {
            EventMap::iterator it = mEvents.find (event);
            if (it == mEvents.end ())
                EXCEPTION (_("Event doesn't exist"));

            return it->second->connect (function);
        }

        void EventMgr::disconnect (EventConnection con)
        {
            if (!con.connected ())
                EXCEPTION (_("Event is not connected"));

            con.disconnect ();
        }

        void EventMgr::fireEvent (const std::string &event, Event evt)
        {
            EventMap::iterator it = mEvents.find (event);
            if (it == mEvents.end ())
                EXCEPTION (_("Event doesn't exist"));

            (*it->second) (evt);
        }

    }

}
