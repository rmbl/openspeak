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

#ifndef __OS_FILE_UTILS_HPP__
#define __OS_FILE_UTILS_HPP__

#include "Platform.hpp"
#include <string>

namespace openSpeak
{
    
    namespace FileUtils
    {
        
        bool fileExists (std::string file);
        
        std::string getConfigPath (void);
        
        std::string getDataPath (void);
        
        std::string getCurrentPath (void);
    }
    
}

#endif
