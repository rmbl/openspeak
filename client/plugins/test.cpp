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

#include <iostream>

openSpeak::Client::Plugin *plugin;

void __attribute__ ((constructor)) my_init ()
{
    plugin = new openSpeak::Client::Plugin ("Dummy Plugin", "0.1", 
            "Philipp Gildein <rmbl@openspeak-project.org>");
    plugin->Description = "Just a dummy plugin";
}

void __attribute__ ((destructor)) my_fini ()
{
    delete plugin;
}
