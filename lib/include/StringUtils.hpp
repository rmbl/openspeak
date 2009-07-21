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

#ifndef __OS_STRING_UTILS_HPP__
#define __OS_STRING_UTILS_HPP__

#include <sstream>
#include <cstdlib>
#include <vector>

namespace openSpeak
{
    namespace StringUtils
    {
        /** \brief Convert any type to a std::string
         *  \param t The variable we want to convert
         *  \return String with the variable
         */
        template <typename T> std::string toString (const T &t)
        {
            std::stringstream tmp;
            tmp << t;
            return tmp.str ();
        }

        /** \brief Convert any string to an uppercase one
         *  \param str The string to convert
         *  \return The converted string
         */
        std::string toUpper (std::string &str);

        /** \brief Convert any string to an uppercase one
         *  \param str The string to convert
         *  \return The converted string
         */
        std::string toUpper (const std::string &str);

        /** \brief Convert any string into a boolean variable
         *  \param str The string to convert
         *  \return False if the string is false, 0 or empty
         */
        inline bool toBool (const std::string &str) 
        { 
            return (!str.empty () && (str == "true" || str == "1" || str == "yes")); 
        }

        /** \brief Convert any string into an integer variable
         *  \param str The string to convert
         *  \return The converted integer value
         */
        inline int toInt (const std::string &str) { return atoi (str.c_str ()); }

        /** \brief Convert any string into an unsigned short variable
         *  \param str The string to convert
         *  \return The converted unsigned short value
         */
        inline ushort toUShort (const std::string &str) 
        { 
            return static_cast <ushort> (strtoul (str.c_str (), 0, 10)); 
        }

        /** \brief Convert any string into a long variable
         *  \param str The string to convert
         *  \return The converted long value
         */
        inline long toLong (const std::string &str) { return atol (str.c_str ()); }

        /** \brief Convert any string into a floating point variable
         *  \param str The string to convert
         *  \return The converted floating point value
         */
        inline float toFloat (const std::string &str) { return (float)atof (str.c_str ()); }
        
        /** \brief Split a string into several pieces
         *  \param str The string to split
         *  \param where Where to split the string
         *  \return Vector containing all pieces of the string
         */
        std::vector <std::string> split (const std::string &str, char where);
        
        /** \brief Remove whitespaces at the front and end of a string
         *  \param str The string to trim
         */
        void trim (std::string &str);
    }

}

#endif
