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

#include "Plugin.hpp"
#include <boost/bind.hpp>
#include <iostream>

using namespace openSpeak::Client;

class DummyPlugin : public Plugin
{
 public:
    DummyPlugin (void)
            : Plugin ("Dummy Plugin", "0.1",
            "Philipp Gildein <rmbl@openspeak-project.org>")
    {
        Description = "Just a dummy plugin";
    }
    
    void testEvent (Event evt)
    {
        std::cerr << "DummyPlugin::testEvent";
    }
};

void testEvent2 (Event evt)
{
    std::cerr << "testEvent2";
}

PLUGIN (DummyPlugin)

EVENTS_BEGIN ()
    EVENT ("activated", boost::bind (&DummyPlugin::testEvent, (DummyPlugin*)plugin, _1))
    EVENT ("activated", &testEvent2)
EVENTS_END ()
