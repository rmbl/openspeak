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

#ifndef __OS_CONFIG_HPP__
#define __OS_CONFIG_HPP__

#include <string>
#include <fstream>
#include <map>

namespace openSpeak
{

    /** \class Config
     *  \brief Opens an INI config file and parses it
     *
     *  The Config class opens an INI file and parses all of its nodes.
     *  New options or changed options get saved back to the file after
     *  destroying the class or setting the option.
     */
    class Config
    {
     private:
        /** \brief The map where we're saving all options in the config */
        typedef std::map <std::string, std::string> ConfigMap;

     public:
        /** \brief Iterator typedefs to ease the use */
        typedef ConfigMap::const_iterator   ConstIterator;
        typedef ConfigMap::iterator         Iterator;     
     
        /** \brief The constructor of the Config class
         *  \param filename The file we want to parse
         */
        Config (const std::string &filename);

        /** \brief The destructor of the Config class */
        ~Config (void);

        /** \brief Parse the config file */
        void parse (void);

        /** \brief Save all options into the configuration file */
        void save (void);

        /** \brief Get the value of an option from the config file
         *  \param option The option we want the value from
         *  \param def The default value
         *  \return String with the value
         */
        std::string getOption (const std::string &option, const std::string &def = "");

        /** \brief Set an option in the config file
         *  \param option The option we want to change/add
         *  \param value The value of the option
         */
        void setOption (const std::string &option, const std::string &value);

        /** \brief Check for the existance of one option
         *  \param option The option to check
         *  \return Returns true if the option exists
         */
        bool optionExists (const std::string &option) const;
        
        /** \brief Return an iterator to iterate through all options
         *  \return An iterator to the first element
         */
        inline ConstIterator begin (void) const { return mOptions.begin (); }
        inline Iterator begin (void) { return mOptions.begin (); }
        
        /** \brief Return an iterator to the element behind the last element
         *  \return An iterator to the element behind the last element
         */
        inline ConstIterator end (void) const { return mOptions.end (); }
        inline Iterator end (void) { return mOptions.end (); }

     private:
        ConfigMap       mOptions;           /**< The map which contains all options */
        std::fstream    mFile;              /**< The config file */
        std::string     mFilename;          /**< The name of the current file */
        bool            mParsed;            /**< True if the file has already been parsed */
    };

}

#endif
