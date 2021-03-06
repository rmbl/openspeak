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
 
/**
  *  Written by François "Kubrick" GUERRAZ (kubrick_at_fgv6_dot_net) for the openSpeak Project.
  */

#include "CmdLineParser.hpp"
#include "Exception.hpp"
#include "Types.hpp"
#include "NLS.hpp"

#include <cstring>
#include <iostream>

namespace openSpeak
{

    CmdLineParser::CmdLineParser(const std::string &apptitle, const std::string &version)
            : mApplicationTitle(apptitle), mApplicationVersion(version)
    {

    }

    void CmdLineParser::addOption (const char* Long, char Short, int Type, 
            const char* HelpText, const char* ArgHelper)
    {
        CmdLineOption option = { Long, Short, Type, HelpText, ArgHelper };
        mOptions.push_back (option);
    }

    void CmdLineParser::addOption (CmdLineOption option)
    {
        mOptions.push_back (option);
    }

    void CmdLineParser::addOption (CmdLineOption* option)
    {
    /* Loop as long as there are options in the array */
        while (option->Long != 0)        
            mOptions.push_back (*option++);
    }

    void CmdLineParser::parseArguments (int argc, char* argv[])
    {
        std::string option;
        const CmdLineOption* found;
        
    /* Loop through all arguments and parse them */
        for (uint i = 1; i < (uint)argc; ++i)
        {
        /* Check if it should be a short or long option */
            if (strlen (argv[i]) == 2)
            {
                if (argv[i][0] != '-' || argv[i][1] == '-')
                    EXCEPTION (format (_("Invalid short option %1%")) % argv[i]);
                    
            /* Search for the short option */
                option = std::string (argv[i]).substr (1);
            }
            else if (strlen (argv[i]) > 2)
            {
                if (argv[i][0] != '-' || argv[i][1] != '-')
                    EXCEPTION (format (_("Invalid long option %1%")) % argv[i]);
                    
            /* Search for the long option */
                option = std::string (argv[i]).substr (2);
            }
            else
            {
                EXCEPTION (format (_("Argument %1% is invalid")) % argv[i]);
            }

            if (option == "help" || option == "h")
                showHelp (argv[0]);
            else if (option == "version" || option == "v")
                showVersion ();
            found = findOption (option);

        /* Throw error if it hasn't been found */
            if (!found)
                EXCEPTION (format (_("Unknown option %1%")) % argv[i]);

            if (found->Type != OPTION_ARG_NONE)
            {
                if (++i == (uint)argc)
                    EXCEPTION (format (_("Option %1% takes an argument")) % argv[i]);
                mValues.insert (std::make_pair (found->Long, argv[i]));
            }
            else
            {
                mValues.insert (std::make_pair (found->Long, "true"));
            }
        }
    }
    
    std::string CmdLineParser::getOption (const std::string &option) const
    {
        ConfigMap::const_iterator it = mValues.find (option);
        return (it != mValues.end ()) ? it->second : std::string ();
    }

    const CmdLineParser::CmdLineOption* CmdLineParser::findOption 
            (const std::string &option) const
    {
        for (OptionsVector::const_iterator it = mOptions.begin ();
                it != mOptions.end (); ++it )
        {
            if ((option.size () == 1 && option[0] == it->Short) ||
                    (option.size () > 1 && option == it->Long))
                return &(*it);
        }
        return 0;
    }
    
    void CmdLineParser::showHelp(char* command) const
    {
    /* Print some general informatins about the program */
        std::cout << format (_("This is the command line help for %1% %2%")) % 
                mApplicationTitle % mApplicationVersion << "\n";        
        
    /* Print all possible options */
        std::cout << command << " [-h|--help] [-v|--version]";
        
        for (OptionsVector::const_iterator it = mOptions.begin ();
                it != mOptions.end (); ++it)
        {
            if (strlen (it->ArgHelper))
                std::cout << " [-" << it->Short << "|--" << it->Long << " "
                        << it->ArgHelper << "]";
            else
                std::cout << " [-" << it->Short << "|--" << it->Long << "]";                
        }
        std::cout << "\n\n";

    /* Print the options with detailed informations */
        std::cout << "-h,--help\n\t\t" << _("Print out this help") << "\n";
        std::cout << "-v,--version\n\t\t" << _("Print out version informations") << "\n";
    
        for (OptionsVector::const_iterator it = mOptions.begin ();
                it != mOptions.end (); ++it)
        {
            if (strlen (it->ArgHelper))
                std::cout << "-" << it->Short << ",--" << it->Long << " " <<
                        it->ArgHelper << "\n\t\t" << it->HelpText << "\n";
            else
                std::cout << "-" << it->Short << ",--" << it->Long << "\n\t\t" <<
                        it->HelpText << "\n";
        }
        std::cout << "\n";
        
    /* Throw an empty exception to terminate the program */
        EXCEPTION ("");
    }

    void CmdLineParser::showVersion(void) const
    {
    /* Show some version informations */
        std::cout << mApplicationTitle << " " << mApplicationVersion << "\n\n";
        
        std::cout << format (_("%1% is licensed under the terms of the GPL.\n"
                "See COPYING for more informations.\n"
                "Copyright (c) 2006 - 2009 openSpeak Team (http://openspeak-project.org)\n"
                "For authors see the AUTHORS file\n")) % mApplicationTitle;
        
    /* Throw an empty exception to terminate the program */
        EXCEPTION ("");
    }


}

