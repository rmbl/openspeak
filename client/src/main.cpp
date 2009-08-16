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

#include "Exception.hpp"
#include "FileUtils.hpp"
#include "LogMgr.hpp"
#include "Config.hpp"
#include "CmdLineParser.hpp"
#include "Core.hpp"
#include "StringUtils.hpp"

using namespace openSpeak;

int main (int argc, char** argv)
{
    CmdLineParser *cmdline = 0;
    Log *log = 0;
    Config *config = 0;
    Client::Core *core = 0;

    try
    {
    /* Parse the commandline */
        cmdline = new CmdLineParser ("openSpeak", "0.1-git");
        CmdLineParser::CmdLineOption options[] = {
            { "debug", 'd', CmdLineParser::OPTION_ARG_NONE, "Display more informations", "" },
            0
        };
        cmdline->addOption (options);
        cmdline->parseArguments (argc, argv);

    /* Check if the config path exists and if not create it */
        std::string confdir = FileUtils::getConfigPath ();
        if (!FileUtils::dirExists (confdir))
            FileUtils::mkdir (confdir);

    /* Also check for the log dir in the config dir */
        if (!FileUtils::dirExists (confdir + "log/"))
            FileUtils::mkdir (confdir + "log/");

    /* Create the log file */
        new LogMgr (confdir + "log/openspeak.log",
                StringUtils::toBool (cmdline->getOption ("debug")) ?
                Log::LVL_DEBUG : Log::LVL_ERROR);
        log = LogMgr::getSingleton ()->getDefaultLog ();
        log->logMsg (" ~*~ Started logging ~*~ ", Log::LVL_SILENT);

    /* Open the config file and parse it */
        config = new Config ("openspeak.conf");
        config->parse ();
        log->logMsg ("Parsed config file " + confdir + "openspeak.conf", Log::LVL_DEBUG);

    /* Create the client core to start the rest */
        core = new Client::Core (config, cmdline, log);
    }
    catch (Exception ex)
    {
        if (log && !ex.empty ())
            log->logMsg ("Exception: " + std::string (ex.what ()), Log::LVL_FATAL);
        else if (!ex.empty ())
            ex.print ();
    }
    catch (...)
    {
        if (log)
            log->logMsg ("Catched unknown exception.", Log::LVL_FATAL);
        else
            std::cout << "Catched unknown exception";
    }

    if (core)
        delete core;
    if (config)
        delete config;
    delete cmdline;

    if (log)
        log->logMsg (" ~*~ Finished logging ~*~", Log::LVL_SILENT);
    if (LogMgr::getSingleton ())
        delete LogMgr::getSingleton ();

    return 0;
}
