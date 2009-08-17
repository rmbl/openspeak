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

#ifndef __OS_THREAD_HPP__
#define __OS_THREAD_HPP__

#include "Types.hpp"
#include <boost/thread.hpp>

namespace openSpeak
{

    typedef boost::mutex::scoped_lock MutexLocker;
    typedef boost::mutex Mutex;

    class Thread
    {
     public:
        Thread(void);
        virtual ~Thread(void);

        void run(void);
        void sleep(uint milliseconds);
        void join(void) const;

        virtual void entry(void) = 0;
     protected:
        boost::thread *mThread;
        boost::mutex  mMutex;
    };

}

#endif
