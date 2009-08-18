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
#include "Exception.hpp"
#include "FileUtils.hpp"

#include <fstream>
#include <cstdlib>
#include <limits.h>

#if defined (OS_PLATFORM_WIN32)
#	include <windows.h>
#   include <direct.h>
#	include <shlobj.h>
#elif defined (OS_POSIX_COMPAT)
#   include <sys/stat.h>
#   include <dirent.h>
#   include <glob.h>
#endif

#ifdef OS_PLATFORM_LINUX
#   include <linux/limits.h>
#endif

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
#if defined (OS_POSIX_COMPAT)
            DIR *fs = opendir (dir.c_str());
            bool exists = fs != NULL;
            closedir (fs);
            return exists;
#elif defined (OS_PLATFORM_WIN32)
            WIN32_FIND_DATA FileData;
            return FindFirstFile (std::string (dir + "*").c_str(),
                    &FileData) != INVALID_HANDLE_VALUE;
#endif
        }

        void mkdir (const std::string &dir)
        {
#if defined (OS_POSIX_COMPAT)
            if (::mkdir (dir.c_str(),
                    S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1)
#elif defined (OS_PLATFORM_WIN32)
            if (_mkdir (dir.c_str ()) == -1)
#endif
                EXCEPTION ("Can't create directory " + dir);
        }

        StringVector findFiles (const std::string &pattern)
        {
            StringVector ret;
#if defined (OS_POSIX_COMPAT)
            glob_t globs;
            int ret = glob (pattern.c_str (), GLOB_ERR, 0, &globs);
            if (ret != 0 || plugins.gl_pathc == 0)
                return ret;

            for (uint i = 0; i < plugins.gl_pathc; ++i)
            {
                if (plugins.gl_pathv[i])
                    ret.push_back (plugins.gl_pathv[i]);
            }

            globfree (&glob);
#elif defined (OS_PLATFORM_WIN32)
            WIN32_FIND_DATA find;
            HANDLE hndl = FindFirstFile (pattern.c_str (), &find);
            if (hndl == INVALID_HANDLE_VALUE)
                return ret;

            BOOL morefiles = TRUE;
            while (morefiles)
            {
                ret.push_back (find.cFileName);
                morefiles = FindNextFile (hndl, &find);
            }

            FindClose (hndl);
#endif
            return ret;
        }

        std::string getConfigPath ()
        {
#if defined (OS_PLATFORM_LINUX)
            char* home = getenv ("HOME");
            return std::string (home) + "/.config/openspeak/";
#elif defined (OS_PLATFORM_WIN32)
            //TODO: Check this code on windows
            TCHAR szPath [MAX_PATH];
            SHGetFolderPath (NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath);
            return std::string (szPath) + "/openspeak/";
#endif
        }

        std::string getDataPath ()
        {
#if defined (OS_POSIX_COMPAT)
            return OS_PREFIX + std::string ("/share/openspeak/");
#elif defined (OS_PLATFORM_WIN32)
            return getCurrentPath () + "/data/";
#endif
        }

        std::string getLibPath ()
        {
#if defined (OS_POSIX_COMPAT)
            return OS_PREFIX + std::string ("/lib/openspeak/");
#else
            return getCurrentPath () + "/plugins/";
#endif
        }

        std::string getCurrentPath ()
        {
#if defined (OS_POSIX_COMPAT)
            char buf[PATH_MAX];
            getcwd (buf, PATH_MAX - 1);
            return std::string (buf);
#elif defined (OS_PLATFORM_WIN32)
            //TODO: Check this code on windows
            TCHAR szDirectory [MAX_PATH];
            GetCurrentDirectory (MAX_PATH - 1, szDirectory);
            return std::string (szDirectory);
#endif
        }
    }
}
