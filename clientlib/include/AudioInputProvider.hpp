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

#ifndef __OS_CLIENT_AUDIO_INPUT_PROVIDER_HPP__
#define __OS_CLIENT_AUDIO_INPUT_PROVIDER_HPP__

#include "Platform.hpp"
#include "PluginInterfaceProvider.hpp"
#include "PluginInterface.hpp"

namespace openSpeak
{

    namespace Client
    {

        /** \class AudioInput
         *  \brief Abstract class to implement an AudioInput interface
         */
        class DLL_SPEC AudioInput : virtual public PluginInterface
        {
         public:
            /** \brief The virtual deconstructor of the AudioInput class */
            virtual ~AudioInput (void) { }

            /** \brief Initialise the output device and return a status
             *  \return True if everything worked
             *  \throw Can also throw an openSpeak::Exception to signal failure
             *      and supply an error message
             */
            virtual bool init (void) = 0;

            /** \brief Gets the audio input from the implementation
             *  \return The audio input frame
             */
            virtual char* getAudioInput (void) = 0;
        };

        /** \class AudioInputProvider
         *  \brief Provides a public interface to one AudioInput class
         *
         *  The AudioInputProvider class provides a public interface for
         *  functions of the AudioInput class which might be loaded from
         *  a plugin.
         */
        class AudioInputProvider : public PluginInterfaceProvider
        {
         public:
            /** \brief The constructor of the AudioInputProvider class */
            AudioInputProvider (void);

            /** \brief The deconstructor of the AudioInputProvider class */
            virtual ~AudioInputProvider (void) { }

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

            /** \brief Check if an interface is loaded
             *  \return True if an interface is loaded
             */
            virtual bool hasInterface (void) const { return mInput; }

            /** \brief Get the input from the choosen interface
             *  \return The audio input frame
             *  \throw Throws an exception if no interface got chosen
             */
            char* getAudioInput (void) const;

         protected:
            /** \brief Try to initialise the interface
             *  \return True if everything worked
             */
            bool _tryInterface () const;

            AudioInput *mInput;  /**< The interface used to get audio input */
        };

    }

}

#endif
