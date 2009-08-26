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

#ifndef __OS_CMD_LINE_PARSER_H__
#define __OS_CMD_LINE_PARSER_H__

#include "Platform.hpp"
#include <string>
#include <map>
#include <vector>

namespace openSpeak
{

    class DLL_SPEC CmdLineParser
    {
     public:
         /** \brief Different types of commandline arguments */
        enum Arguments
        {
                OPTION_ARG_NONE,  	/**< Option doesn't take any argument */
                OPTION_ARG_STRING,	/**< Option takes a string argument */
                OPTION_ARG_INT 		/**< Option takes a int argument */
        };
        
        /** \brief Define a valid cmdlineoption with this struct */
        struct CmdLineOption 
        {
            const char* Long;           /**< Ex: "max-connections" */
            char Short;             	/**< Ex: 'm' */
            int Type;               	/**< Ex: C_OPTION_ARG_INT */
            const char* HelpText;      	/**< Ex: "Specifies the maximum number 
                                        of connections allowed on the server" */
            const char* ArgHelper;      /**< Ex: "N" */
        };
        
     private:
        /** \brief The map where we're saving all given options */
        typedef std::map <std::string, std::string> ConfigMap;
        
        /** \brief Vector containing all possible options */
        typedef std::vector <CmdLineOption> OptionsVector;
        
     public:
      	/** \brief The constructor of the CmdLineParser class
         *	\param apptitle The title of the application using the CmdLineParser class
         *	\param version The version number of the application
         * */
        CmdLineParser (const std::string &apptitle, const std::string &version);
        
        /** \brief Add a single CmdLineOption by giving all parameters. */ 
        void addOption (const char* Long, char Short, int Type, 
                const char* HelpText, const char* ArgHelper = "");

        /** \brief Add a single CmdLineOption by copying.
         *
         *  Add the Option to the _optionsSet linked list.
         *	This is the "generic" addOption method, other overloads rely on this one.
         *	\param option The CmdLineOption to add
         * */
        void addOption (CmdLineOption option);

        /** \brief Add multiple CmdLineOption's through an array
         *
         *	Allow many options to be added in one time.
         *	An array, ending with a { NULL } element must be given, see this example :
         *	\code
         *	CmdLineOption ServerOptions[] = {
         *		{"help", 'h', C_OPTION_HELP, NULL, "Print this help message", ""},
         *		{"daemon", 'd', C_OPTION_ARG_NONE, &daemon, "Use this option to make the server fork to the background", ""},
         *		{"listen", 'l', C_OPTION_ARG_INT, &listen_port, "Specifies on which port the server is listening (Not Implemented Option)", "N"},
         *		{NULL}
         *	};
         *	\endcode
         *	This function relies on addOption (COption Option)
         *	\param option An array of CmdLineOption's
         * */
        void addOption (CmdLineOption* option);
        
        /** \brief Parse the given commandline
         *	\param argc The number of arguments
         *	\param argv All arguments
         * */
        void parseArguments (int argc, char* argv[]);
        
        /** \brief Get the value of an option
         *  \param option The option for which to get the value
         *  \return The value of the option or an empty string
         */
        std::string getOption (const std::string &option) const;
          
     private:     
        /** \brief Find the requested option in the OptionsVector
         *  \param option The option to search for
         *  \return The option if found or null
         */
        const CmdLineOption* findOption (const std::string &option) const;
        
        /** \brief Show the help text
         *  \param command The name of the called program (argv[0])
         */
        void showHelp(char* command) const;
        
        /** \brief Show some version informations */
        void showVersion(void) const;
     
        ConfigMap mValues;      /**< The commandline options get saved here */
        OptionsVector mOptions; /**< The possible cmdline options */

        const std::string mApplicationTitle;   /**< Contains the application's title */
        const std::string mApplicationVersion; /**< Contains the application's version */
    };

}

#endif
