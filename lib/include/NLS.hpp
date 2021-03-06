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

#ifndef __OS_NLS_HPP__
#define __OS_NLS_HPP__

#include <libintl.h>
#include <locale.h>
#include <string>

#include <boost/format.hpp>

#define _(x) gettext(x)

using boost::format;

namespace openSpeak
{

    /** \brief Initialise the NLS system
     *  \param domain The textdomain to use
     *  \return True if everything went fine
     */
    bool initNLS (const std::string &domain);
 
}

#endif
