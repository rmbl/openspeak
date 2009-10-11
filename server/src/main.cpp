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
#include "NLS.hpp"

using namespace openSpeak;

int main (int argc, char** argv)
{
    int ret = 0;
    CmdLineParser *cmdline = 0;
    Config *config = 0;

    if (!initNLS ("openspeak"))
    {
        std::cerr << "Initialising NLS failed!\n";
        return -1;
    }

    try
    {
    /* Parse the commandline */
        cmdline = new CmdLineParser (_("openSpeak Server"), "0.2-git");
        CmdLineParser::CmdLineOption options[] = {
            { "debug", 'd', CmdLineParser::OPTION_ARG_NONE, _("Display more informations"), "" },
            {0}
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
        new LogMgr (confdir + "log/openspeakd.log",
                StringUtils::toBool (cmdline->getOption ("debug")) ?
                Log::LVL_DEBUG : Log::LVL_SILENT);
        LOG_SILENT (_("Started logging"));

    /* Open the config file and parse it */
        config = new Config ("openspeakd.conf");
        config->parse ();
        LOG_DEBUG (format (_("Parsed config file %1%openspeakd.conf")) % confdir);
    }
    catch (Exception ex)
    {
        if (LogMgr::getSingleton () && !ex.empty ())
            LOG_FATAL (format (_("Exception: %1%")) % ex.what ());
        else if (!ex.empty ())
            ex.print ();
        ret = -1;
    }
    catch (...)
    {
        if (LogMgr::getSingleton ())
            LOG_FATAL (_("Catched unknown exception."));
        else
            std::cout << _("Catched unknown exception");
        ret = -1;
    }

    delete cmdline;
    if (config)
        delete config;

    if (LogMgr::getSingleton ())
    {
        LOG_SILENT (_("Finished logging "));
        delete LogMgr::getSingleton ();
    }

    return ret;
}
