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

#ifndef __OS_CLIENT_VOICE_CODEC_PROVIDER_HPP__
#define __OS_CLIENT_VOICE_CODEC_PROVIDER_HPP__

#include "PluginInterfaceProvider.hpp"

namespace openSpeak
{

    namespace Client
    {
        
        /** \class VoiceCodecProvider
         *  \brief Provides a public interface to one VoiceCodec class
         *
         *  The VoiceCodecProvider class provides a public interface for
         *  functions of the VoiceCodec class which might be loaded from
         *  a plugin.
         */
        class VoiceCodecProvider : public PluginInterfaceProvider
        {
         public:
            /** \brief The constructor of the VoiceCodecProvider class */
            VoiceCodecProvider (void);
            
            /** \brief The deconstructor of the VoiceCodecProvider class */
            virtual ~VoiceCodecProvider (void) { }
            
            /** \brief Use the specified interface for all operations
             *  \param name The name of the interface to use
             *  \throw Throws an exception if the interface is unknown
             */
            virtual void useInterface (const std::string &name);

            /** \brief Use a "default" interface
             *  \throw Throws an exception if no interface is available
             *          or the interface fails to load.
             *
             *  Which interface to use is in the responsibility of the
             *  subclass developers. Possiblities include using the first one
             *  in the vector or including a list of favorites.
             */
            virtual void useDefaultInterface (void);
            
            /** \brief Encode the voice frame
             *  \param voice The voice frame
             *  \return The encoded voice frame
             *  \throw Exception if no interface is chosen
             */
            char* encodeVoice (char* voice);
            
            /** \brief Decode the encoded voice frame
             *  \param enc The encoded voice frame
             *  \return The original voice frame
             *  \throw Exception if no interface is chosen
             */
            char* decodeVoice (char* enc);
         
         protected:
            VoiceCodec  *mCodec;    /**< The used codec interface */
        };
        
    }

}

#endif
