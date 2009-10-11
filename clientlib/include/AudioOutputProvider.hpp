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

#ifndef __OS_CLIENT_AUDIO_OUTPUT_PROVIDER_HPP__
#define __OS_CLIENT_AUDIO_OUTPUT_PROVIDER_HPP__

#include "Platform.hpp"
#include "PluginInterfaceProvider.hpp"
#include "PluginInterface.hpp"

namespace openSpeak
{

    namespace Client
    {

        /** \class AudioOutput
         *  \brief Abstract class to implement an AudioOutput interface
         */
        class DLL_SPEC AudioOutput : public PluginInterface
        {
         public:
            /** \brief The virtual deconstructor of the AudioInput class */
            virtual ~AudioOutput (void) { }

            /** \brief Initialise the output device and return a status
             *  \return True if everything worked
             *  \throw Can also throw an openSpeak::Exception to signal failure
             *      and supply an error message
             */
            virtual bool init (void) = 0;

            /** \brief Set the next frame on the choosen interface
             *  \param out The audio output frame
             */
            virtual void setAudioOutput (char* out) = 0;
        };

        /** \class AudioOutputProvider
         *  \brief Provides a public interface to one AudioOutput class
         *
         *  The AudioOutputProvider class provides a public interface for
         *  functions of the AudioOutput class which might be loaded from
         *  a plugin.
         */
        class AudioOutputProvider : public PluginInterfaceProvider
        {
         public:
            /** \brief The constructor of the AudioOutputProvider class */
            AudioOutputProvider (void);

            /** \brief The deconstructor of the AudioOutputProvider class */
            virtual ~AudioOutputProvider (void) { }

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

            /** \brief Set the next frame on the choosen interface
             *  \param out The audio output frame
             *  \throw Throws an exception if no interface got chosen
             */
            void setAudioOutput (char* out) const;

         protected:
            /** \brief Try to initialise the interface
             *  \return True if everything worked
             */
            bool _tryInterface () const;

            AudioOutput *mOutput;    /**< The interface used to output sound */
        };

    }

}

#endif
