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
                EXCEPTION ("Given name is empty");
            
        /* Search for the interface and set it for later usage */
            for (InterfaceVector::const_iterator it = mIFaces.begin (); 
                    it != mIFaces.end (); ++it)
            {
                if ((*it)->Name == name)
                {
                /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                    mInput = dynamic_cast <AudioInput*> ((PluginInterface*)*it);
                    if (!mInput)
                    {
                        delete *mIFaces.begin ();
                        mIFaces.erase (mIFaces.end ()); 
                        EXCEPTION ("Interface " + name + " is invalid");
                    }
                    break;
                }
            }
            
            EXCEPTION ("Interface " + name + " not found");
        }
        
        void AudioInputProvider::useDefaultInterface ()
        {
            mInput = 0;
                    
        /* Get the first one available */
            while (mIFaces.size () > 0)
            {
            /* Do a typesafe-cast to avoid having incorrect PluginInterfaces */
                mInput = dynamic_cast <AudioInput*> (*mIFaces.begin ());
                
            /* Delete the interface if it's incorrect */
                if (!mInput)
                {
                    LogMgr::getSingleton ()->getDefaultLog ()->logMsg (
                            "Removing invalid interface " + (*mIFaces.begin ())->Name,
                            Log::LVL_DEBUG);
                    delete *mIFaces.begin ();
                    mIFaces.erase (mIFaces.end ());
                }
            }

        /* Check if a valid interface was found */
            if (!mInput)
                EXCEPTION ("No valid interface available");
        }
        
        char* AudioInputProvider::getAudioInput () const
        {
            if (!mInput)
                EXCEPTION ("No interface chosen");
            return mInput->getAudioInput ();
        }
            
    }

}
