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

#include "Thread.hpp"
#include "Exception.hpp"
#include "NLS.hpp"

namespace openSpeak
{

	Thread::Thread ()
            : mThread (0)
	{
	}

	Thread::~Thread ()
	{
		if (mThread)
			delete mThread;
	}

	void Thread::run ()
	{
		MutexLocker lock (mMutex);
		if (mThread)
            EXCEPTION (_("Thread was already created"));

		mThread = new boost::thread (boost::bind (&Thread::entry, this));
	}

	void Thread::sleep (uint ms)
	{
		MutexLocker lock (mMutex);
        if (!mThread)
            EXCEPTION (_("Thread is not running"));
		boost::xtime time;
		time.sec = 0;
		time.nsec = ms * 1000;
		mThread->sleep (time);
	}

    void Thread::join () const
    {
        if (!mThread)
            EXCEPTION (_("Thread is not running"));
        mThread->join ();
    }

}

