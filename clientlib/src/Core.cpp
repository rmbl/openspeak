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

#include "Core.hpp"
#include "Exception.hpp"

namespace openSpeak
{

    namespace Client
    {

        Core::Core (Config *cfg, CmdLineParser *cmdline, Log *log)
                : mConfig (cfg), mCmdLine (cmdline), mLog (log)
        {
            logMsg ("Core: Starting up", Log::LVL_INFO);

            mPluginMgr = new PluginMgr ();
            mPluginMgr->registerEventMgr (this);

            try
            {
                logMsg ("Core: Loading plugins", Log::LVL_INFO);
                mPluginMgr->loadPlugins (mConfig);
                logMsg ("Core: Finished loading plugins", Log::LVL_INFO);
            }
            catch (openSpeak::Exception &ex)
            {
                logMsg (ex.what (), Log::LVL_ERROR);
            }
        }

        Core::~Core ()
        {
            logMsg ("Core: Shutting down", Log::LVL_INFO);
            delete mPluginMgr;
            logMsg ("Core: Closed PluginMgr", Log::LVL_INFO);
        }

    }
}
