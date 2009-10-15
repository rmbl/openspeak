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
#include "NLS.hpp"

namespace openSpeak
{

    namespace Client
    {

        Core::Core (Config *cfg, CmdLineParser *cmdline, Log *log)
                : mConfig (cfg), mCmdLine (cmdline), mLog (log)
        {
            logMsg (_("Core: Starting up"), Log::LVL_INFO);
        }

        Core::~Core ()
        {
            logMsg (_("Core: Shutting down"), Log::LVL_INFO);
            if (mPluginMgr)
            {
                delete mPluginMgr;
                logMsg (_("Core: Closed PluginMgr"), Log::LVL_INFO);
            }
        }

        void Core::entry ()
        {
        /* Create PluginMgr and add Core as eventmgr */
            mPluginMgr = new PluginMgr ();
            mPluginMgr->registerEventMgr (this);

        /* Create all needed PluginInterfaceProviders */
            AudioInputProvider *audioin = new AudioInputProvider ();
            AudioOutputProvider *audioout = new AudioOutputProvider ();

            logMsg (_("Core: Initialized interface providers"), Log::LVL_INFO);

        /* Try to load all plugins */
            try
            {
                logMsg (_("Core: Loading plugins"), Log::LVL_INFO);
                mPluginMgr->loadPlugins (mConfig);
                logMsg (_("Core: Finished loading plugins"), Log::LVL_INFO);
            }
            catch (openSpeak::Exception &ex)
            {
                logMsg (ex.what (), Log::LVL_ERROR);
            }

        /* Initialize the audio stuff */
            _initAudio (audioin, audioout);

        /* Delete all PluginInterfaceProviders after we're finished */
            delete audioin;
            delete audioout;
        }

        void Core::_initAudio (AudioInputProvider *in, AudioOutputProvider *out)
        {
        /* Try to initialize audio input */
            if (mConfig->optionExists ("audio.input"))
            {
                try
                {
                    in->useInterface (mConfig->getOption ("audio.input"));
                }
                catch (openSpeak::Exception &ex)
                {
                    logMsg (format (_("Core: Using audio input interface %1% failed")) %
                            mConfig->getOption ("audio.input"), Log::LVL_ERROR);
                    logMsg (ex.what (), Log::LVL_ERROR);
                }
            }

        /* If it failed or no option is set, try to use default interface */
            if (!in->hasInterface ())
            {
                try
                {
                    in->useDefaultInterface ();
                }
                catch (openSpeak::Exception &ex)
                {
                    logMsg ("Core: Using the default audio input interface failed",
                            Log::LVL_ERROR);
                    logMsg (ex.what (), Log::LVL_ERROR);
                }
            }

        /* Try to initialize audio input */
            if (mConfig->optionExists ("audio.output"))
            {
                try
                {
                    out->useInterface (mConfig->getOption ("audio.output"));
                }
                catch (openSpeak::Exception &ex)
                {
                    logMsg (format (_("Core: Using audio input interface %1% failed")) %
                            mConfig->getOption ("audio.output"), Log::LVL_ERROR);
                    logMsg (ex.what (), Log::LVL_ERROR);
                }
            }

        /* If it failed or no option is set, try to use default interface */
            if (!out->hasInterface ())
            {
                try
                {
                    out->useDefaultInterface ();
                }
                catch (openSpeak::Exception &ex)
                {
                    logMsg ("Core: Using the default audio input interface failed",
                            Log::LVL_ERROR);
                    logMsg (ex.what (), Log::LVL_ERROR);
                }
            }
        }

    }
}
