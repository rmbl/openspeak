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
#include <vector>
#include <string>

namespace openSpeak
{

    /** \brief Often used vector */
    typedef std::vector <std::string> StringVector;

    namespace FileUtils
    {
        /** \brief Checks if a file exists in the filesystem
         *  \param file The file to check for
         *  \return True if the file was found
         */
        bool fileExists (const std::string &file);

        /** \brief Check if a directory exists in the filesystem
         *  \param dir The directory to check for
         *  \return True if the directory was found
         */
        bool dirExists (const std::string &dir);

        /** \brief Create the given directory
         *  \param dir The directory to create
         *  \throw openSpeak::Exception if creating the directory fails
         */
        void mkdir (const std::string &dir);

        /** \brief Find files matching the pattern
         *	\param pattern The pattern the files need to match
         */
        StringVector findFiles (const std::string &pattern);

        /** \brief Return the path to all (per user) configuration files
         *  \return The path to all (per user) configuration files
         */
        std::string getConfigPath (void);

        /** \brief Return the path where the data is
         *  \return The path where the data is
         */
        std::string getDataPath (void);

        /** \brief Return the path where plugins should be
         *  \return The path where plugins should be
         */
        std::string getLibPath (void);

        /** \brief Return the current working dir
         *  \return The path the binary is working in
         */
        std::string getCurrentPath (void);

    }

}

#endif
