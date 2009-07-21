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

#include "StringUtils.hpp"
#include <algorithm>

namespace openSpeak
{

    namespace StringUtils
    {

        std::string toUpper(std::string &str)
        {
            std::transform(str.begin(), str.end(), str.begin(), (int(*)(int)) std::toupper);
            return str;
        }

        std::string toUpper(const std::string &str)
        {
            std::string tmp = str;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), (int(*)(int)) std::toupper);
            return tmp;
        }

    }
    
}