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

#ifndef __OS_CLIENT_CORE_HPP__
#define __OS_CLIENT_CORE_HPP__

#include "EventMgr.hpp"
#include "Singleton.hpp"
#include "Config.hpp"
#include "CmdLineParser.hpp"
#include "Log.hpp"
#include "PluginMgr.hpp"

namespace openSpeak
{

    namespace Client
    {

        class Core : public EventMgr, public Singleton <Core>
        {
         public:
            /** \brief The constructor of the Core class
             *  \param cfg The config to use
             *  \param cmdline The CmdLineParser to use
             *  \param log The log to log messages to
             */
            Core (Config *cfg, CmdLineParser *cmdline, Log *log);

            /** \brief The destructor of the Core class */
            ~Core (void);

            /* These two functions are currently unimplemented,
               they are just a hint at what will be added.

            void connect (const std::string &server, const ushort &port,
                    const std::string &password);

            void disconnect (void);
            */

            /** \brief Get the value of an option either from the cmdline or config
             *  \param option The option for which to get the value
             *  \param def The default value
             *  \return The value of the option
             */
            std::string getOption (const std::string &option,
                    const std::string &def = "");

            /** \brief Set the value of an optionExists
             *  \param option The option for which to set the value
             *  \param value The value of the option
             */
            void setOption (const std::string &option, const std::string &value);

            /** \brief Log a message in the user specified log
             *  \param msg The message to log
             *  \param lvl The level of importance of the message
             */
            inline void logMsg (const std::string &msg, const Log::Level &lvl) const
            {
                mLog->logMsg (msg, lvl);
            }

         protected:
            Config          *mConfig;
            CmdLineParser   *mCmdLine;
            Log             *mLog;

            PluginMgr       *mPluginMgr;
        };

    }

}

#endif
