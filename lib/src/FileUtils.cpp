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
  
#include "Platform.hpp"
#include "FileUtils.hpp"

#include <fstream>
#include <cstdlib>
#include <limits.h>

#if defined (OS_PLATFORM_WIN32)
#   include <windows.h>
#elif defined (OS_PLATFORM_LINUX)
#   include <linux/limits.h>
#   include <dirent.h>
#endif

#define T(x) #x

namespace openSpeak
{
    
    namespace FileUtils
    {       
        
        bool fileExists (const std::string &file)
        {
            std::fstream ftest;
            ftest.open (file.c_str(), std::ios::in);
            bool open = ftest.is_open ();
            ftest.close ();
            return open;
        }

        bool dirExists (const std::string &dir)
        {
#ifdef OS_POSIX_COMPAT
            DIR *fs = opendir (dir.c_str());
            bool exists = fs != NULL;
            closedir (fs);
            return exists;
#elif OS_PLATFORM_WIN32
            WIN32_FIND_DATA FileData
            return FindFirstFile (std::string (dir + "*").c_str(),
                    &FileData) != INVALID_HANDLE_VALUE;
#endif
        }

        std::string getConfigPath ()
        {
#ifdef OS_PLATFORM_LINUX
            char* home = getenv ("HOME");
            return std::string (home) + "/.config/openspeak/";
#elif OS_PLATFORM_WIN32
            //TODO: Check this code on windows
            TCHAR szPath[MAX_PATH];
            SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath);
            return std::string (szPath) + "\\openspeak\\";
#endif
        }
        
        std::string getDataPath ()
        {
#ifdef OS_POSIX_COMPAT
            //TODO: Check if this define works
            return OS_PREFIX + std::string ("/share/openspeak/");
#elif OS_PLATFORM_WIN32 
            return getCurrentPath () + "\\data\\";
#endif
        }
        
        std::string getCurrentPath ()
        {
#ifdef OS_POSIX_COMPAT
            char buf[PATH_MAX];
            getcwd (buf, PATH_MAX - 1);
            return std::string (buf);
#elif OS_PLATFORM_WIN32
            //TODO: Check this code on windows
            TCHAR szDirectory[MAX_PATH];
            GetCurrentDirectory(MAX_PATH - 1, szDirectory);
            return std::string (szDirectory);
#endif
        }
    }
}
