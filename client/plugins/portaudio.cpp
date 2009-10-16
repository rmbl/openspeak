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

#include "Plugin.hpp"
#include "Exception.hpp"
#include "NLS.hpp"
#include "AudioInputProvider.hpp"
#include "AudioOutputProvider.hpp"

#include <portaudio.h>

/* This should be just a temporary fix! Should be given by voicecodec and/or
 * settings/config.
 */
#define AUDIO_CHANNELS 1
#define SAMPLERATE 44100
#define FRAMESIZE 200

using namespace openSpeak::Client;

class PortAudioWrapper : public AudioInput, public AudioOutput
{
 public:
    PortAudioWrapper (void) : mRunning (false)
    { }

    virtual ~PortAudioWrapper (void)
    {
        if (mRunning)
        {
            Pa_CloseStream (mStream);
            Pa_Terminate ();
        }
    }

    virtual bool init (void)
    {
        if (mRunning)
            return true;

        PaError error = Pa_Initialize ();
        if (error != paNoError)
            return false;

        error = Pa_OpenDefaultStream (&mStream, AUDIO_CHANNELS, AUDIO_CHANNELS,
                paInt16, SAMPLERATE, FRAMESIZE, 0, 0);
        if (error != paNoError)
            return false;

        error = Pa_StartStream (mStream);
        if (error != paNoError)
            return false;

        return mRunning = true;
    }

    virtual char* getAudioInput (void)
    {
        if (!mRunning)
            return 0;

        char *buffer = new char[2*FRAMESIZE];
        PaError error = Pa_ReadStream (mStream, buffer, FRAMESIZE);
        if (error != paNoError)
            EXCEPTION (_("Error while reading from stream"));
        return buffer;
    }

    virtual void setAudioOutput(char* out)
    {
        if (!mRunning)
            return;

        PaError error = Pa_WriteStream (mStream, out, FRAMESIZE);
        if (error != paNoError)
            EXCEPTION (_("Error while writing to stream"));
    }

    virtual std::string getName (void)
    {
        return "PortAudio";
    }

 protected:
    bool mRunning;

    /** \brief PortAudio stream strutured passed to initialize the audio device
     */
	PaStream *mStream;
};

class PortAudioPlugin : public Plugin
{
 public:
    PortAudioPlugin (void) : Plugin ("PortAudio Plugin", "0.1",
            "Philipp Gildein <rmbl@openspeak-project.org>")
    {
        Description = _("Adds audio in/output through the portaudio library");
        mWrap = new PortAudioWrapper ();
        registerClass ("AudioInput", mWrap);
        registerClass ("AudioOutput", mWrap);
    }

 protected:
    PortAudioWrapper *mWrap;
};

PLUGIN (PortAudioPlugin);
