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

#include "Config.hpp"
#include "Exception.hpp"
#include "FileUtils.hpp"
#include "StringUtils.hpp"

namespace openSpeak
{
    
    Config::Config(const std::string &filename)
            : mFilename (filename), mParsed (false)
    {

    }

    Config::~Config()
    {
    /* Save the currently loaded file */
        if (mParsed)
            save ();
        if (mFile.is_open ())
            mFile.close ();
    }

    void Config::parse()
    {
        if (mFilename.empty ())
            EXCEPTION ("The filename is empty");

        bool found = false;
        std::string file = FileUtils::getConfigPath () + mFilename;
        if (!FileUtils::fileExists (file))
        {
            file = FileUtils::getCurrentPath () + mFilename;
            if (FileUtils::fileExists (file))
                found = true;
        }
        else
        {
            found = true;
        }

    /* If the file doesn't exists just open it and return */
        if (!found)
        {
            mFilename = FileUtils::getConfigPath () + mFilename;
            mParsed = true;
            return;
        }
        
        mFilename = file;
        
    /* Parse the ini file */
        mFile.open (mFilename.c_str (), std::ios::in);
        
        std::string section, line, key;
        int lineno = 0;
        while (!mFile.eof ())
        {
            ++lineno;
            getline (mFile, line);
            StringUtils::trim (line);
            
        /* Got a comment or empty line */
            if (line.empty () || line[0] == ';' || line[0] == '#')
            {
                continue;
            }
        /* Got a section header */
            else if (line[0] == '[' && line[line.size () - 1] == ']')
            {
                section = line.substr(1, line.size () - 2);
            }
        /* Got a key = value pair */
            else
            {
                std::vector <std::string> str = StringUtils::split (line, '=');
                if (str.size () > 2)
                {
                    EXCEPTION ("Invalid line in " + mFilename + " (Line: " + 
                            StringUtils::toString (lineno));
                }
                
                StringUtils::trim (str[0]); StringUtils::trim (str[1]);
                key = section + "." + str[0];
                mOptions[key] = (str.size () == 2) ? str[1] : "";
            }
        }
        
        mFile.close ();        
        mParsed = true;
    }

    void Config::save ()
    {
        if (!mParsed)
            EXCEPTION ("Can't save a unparsed file");
            
        if (mFile.is_open ())
            mFile.close ();
        mFile.clear ();
        mFile.open (mFilename.c_str (), std::ios::out);
        
    /* Sort all data by sections */
        ConfigMap sections;
        ConfigMap::iterator it;
        for (it = mOptions.begin (); it != mOptions.end (); ++it)
        {
            std::vector <std::string> str = StringUtils::split (it->first, '.');

            std::string section, pair;

            if (str.size () > 1)
            {
                section = StringUtils::join (str, str.size () - 1, ".");
                pair = str.back () + " = " + it->second + "\n";
            }
            else
            {
                section = "";
                pair = str[0] + " = " + it->second + "\n";
            }
            
            if (sections.find (section) != sections.end ())
                sections[section] += pair;
            else
                sections.insert (std::make_pair (section, pair));
        }
        
    /* Parse all data in the map and save it */
        for (it = sections.begin (); it != sections.end (); ++it)
        {
            if (!it->first.empty ())
                mFile << "[" << it->first << "]\n";
            mFile << it->second << "\n";
        }

    /* Save the file */
        mFile.flush ();
        mFile.close ();
        if (mFile.fail ())
            EXCEPTION ("Saving file " + mFilename + " failed");
    }

    std::string Config::getOption (const std::string &option, const std::string &def)
    {
        if (optionExists (option))
            return mOptions[option];
        else if (!def.empty ())
            return mOptions[option] = def;
        else
            return std::string ();
    }

    void Config::setOption (const std::string &option, const std::string &value)
    {
        if (option.empty ())
            EXCEPTION ("Can't set an empty option");

        mOptions[option] = value;
        save();
    }

    bool Config::optionExists (const std::string &option) const
    {
    /* Search for the option in the config */
        ConfigMap::const_iterator it = mOptions.find (option);
        return it != mOptions.end ();
    }

}
