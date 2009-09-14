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
                if ((*it)->Name == name)
                {
                /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                    mOutput = dynamic_cast <AudioOutput*> ((PluginInterface*)*it);
                    if (!mOutput)
                    {
                        delete *mIFaces.begin ();
                        mIFaces.erase (mIFaces.end ());
                        EXCEPTION (format (_("Interface %1% is invalid")) % name);
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
            while (mIFaces.size () > 0)
            {
            /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                mOutput = dynamic_cast <AudioOutput*> (*mIFaces.begin ());

            /* Delete the interface if it's incorrect */
                if (!mOutput)
                {
                    LOG_DEBUG (format (_("Removing invalid interface %1%")) % 
                            (*mIFaces.begin ())->Name);
                    delete *mIFaces.begin ();
                    mIFaces.erase (mIFaces.end ());
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

    }

}
