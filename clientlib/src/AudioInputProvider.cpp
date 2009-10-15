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

#include "AudioInputProvider.hpp"
#include "Exception.hpp"
#include "LogMgr.hpp"
#include "NLS.hpp"

namespace openSpeak
{

    namespace Client
    {

        AudioInputProvider::AudioInputProvider ()
            : PluginInterfaceProvider ("AudioInput")
        {
            mInput = 0;
        }

        void AudioInputProvider::useInterface (const std::string &name)
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
                    mInput = dynamic_cast <AudioInput*> ((PluginInterface*)*it);
                    if (!mInput)
                    {
                        delete *mIFaces.begin ();
                        mIFaces.erase (mIFaces.end ());
                        EXCEPTION (format (_("Interface %1% is invalid")) % name);
                    }
                /* Try to initialise it and delete it if it fails */
                    else if (!_tryInterface ())
                    {
                        delete mInput;
                        EXCEPTION (format (_("Interface %1% failed to initialise")) %
                                name);
                    }
                    return;
                }
            }

            EXCEPTION (format (_("Interface %1% not found")) % name);
        }

        void AudioInputProvider::useDefaultInterface ()
        {
            mInput = 0;

        /* Get the first one available */
            while (mIFaces.size () > 0 && !mInput)
            {
            /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                mInput = dynamic_cast <AudioInput*> (*mIFaces.begin ());

            /* Delete the interface if it's incorrect */
                if (!mInput)
                {
                    LOG_DEBUG (format (_("Removing invalid interface %1%")) %
                            (*mIFaces.begin ())->getName ());
                    delete *mIFaces.begin ();
                    mIFaces.erase (mIFaces.end ());
                }
            /* Try to initialise it and delete it if it fails */
                else if (!_tryInterface ())
                {
                    LOG_ERROR (format (_("Interface %1% failed to initialise")) %
                            (*mIFaces.begin ())->getName ());
                    delete mInput;
                    mInput = 0;
                }
            }

        /* Check if a valid interface was found */
            if (!mInput)
                EXCEPTION (_("No valid interface available"));
        }

        char* AudioInputProvider::getAudioInput () const
        {
            if (!mInput)
                EXCEPTION (_("No interface chosen"));
            return mInput->getAudioInput ();
        }

        bool AudioInputProvider::_tryInterface () const
        {
            bool ret = false;

            try
            {
                ret = mInput->init ();
            }
            catch (openSpeak::Exception &e)
            {
                LOG_ERROR (e.what ());
            }

            return ret;
        }

    }

}
