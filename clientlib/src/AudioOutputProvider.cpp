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

#include "AudioOutputProvider.hpp"
#include "Exception.hpp"
#include "LogMgr.hpp"
#include "NLS.hpp"

namespace openSpeak
{

    namespace Client
    {

        AudioOutputProvider::AudioOutputProvider ()
            : PluginInterfaceProvider ("AudioOutput")
        {
            mOutput = 0;
        }

        void AudioOutputProvider::useInterface (const std::string &name)
        {
            if (name.empty ())
                EXCEPTION (_("Given name is empty"));

        /* Search for the interface and set it for later usage */
            for (InterfaceVector::const_iterator it = mIFaces.begin ();
                    it != mIFaces.end (); ++it)
            {
                if ((*it)->getName () == name)
                {
                /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                    mOutput = dynamic_cast <AudioOutput*> ((PluginInterface*)*it);
                    if (!mOutput)
                    {
                        delete *mIFaces.begin ();
                        mIFaces.erase (mIFaces.end ());
                        EXCEPTION (format (_("Interface %1% is invalid")) % name);
                    }
                /* Try to initialise it and delete it if it fails */
                    else if (!_tryInterface ())
                    {
                        delete mOutput;
                        EXCEPTION (format (_("Interface %1% failed to initialise")) %
                                name);
                    }
                    return;
                }
            }

            EXCEPTION (format (_("Interface %1% not found")) % name);
        }

        void AudioOutputProvider::useDefaultInterface ()
        {
            mOutput = 0;

        /* Get the first one available */
            while (mIFaces.size () > 0 && !mOutput)
            {
            /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                mOutput = dynamic_cast <AudioOutput*> (*mIFaces.begin ());

            /* Delete the interface if it's incorrect */
                if (!mOutput)
                {
                    LOG_DEBUG (format (_("Removing invalid interface %1%")) %
                            (*mIFaces.begin ())->getName ());
                    delete *mIFaces.begin ();
                    mIFaces.erase (mIFaces.begin ());
                }
            /* Try to initialise it and delete it if it fails */
                else if (!_tryInterface ())
                {
                    LOG_ERROR (format (_("Interface %1% failed to initialise")) %
                            (*mIFaces.begin ())->getName ());
                    delete mOutput;
                    mOutput = 0;
                    mIFaces.erase (mIFaces.begin ());
                }
            }

        /* Check if a valid interface was found */
            if (!mOutput)
                EXCEPTION (_("No valid interface available"));
        }

        void AudioOutputProvider::setAudioOutput (char *out) const
        {
            if (!mOutput)
                EXCEPTION (_("No interface chosen"));
            mOutput->setAudioOutput (out);
        }

        bool AudioOutputProvider::_tryInterface () const
        {
            bool ret = false;

            try
            {
                ret = mOutput->init ();
            }
            catch (openSpeak::Exception &e)
            {
                LOG_ERROR (e.what ());
            }

            return ret;
        }

    }

}
