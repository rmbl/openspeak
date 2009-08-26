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

#include "Platform.hpp"
#include <boost/thread.hpp>

namespace openSpeak
{

    /** \brief Typedefs for easier access to heavily used boost::thread stuff */
    typedef boost::mutex::scoped_lock MutexLocker;
    typedef boost::mutex Mutex;

    /** \class Thread
     *  \brief Creates a new thread and runs the entry () function in it
     *
     *  The Thread class is an abstract base class which needs to be inherited
     *  to easily create a new thread.
     */
    class DLL_SPEC Thread
    {
     public:
        /** \brief The constructor of the Thread class */
        Thread (void);

        /** \brief The destructor of the Thread class */
        virtual ~Thread (void);

        /** \brief Create the thread and run the entry () function in it */
        void run (void);

        /** \brief Let the running thread sleep for a defined time
         *  \param milliseconds The amount of milliseconds to sleep
         */
        void sleep (uint milliseconds);

        /** \brief Wait for the thread to terminate */
        void join (void) const;

        /** \brief Abstract function which contents will get run inside the thread */
        virtual void entry (void) = 0;

     protected:
        boost::thread *mThread; /**< The thread object */
        boost::mutex  mMutex;   /**< The protecting mutex */
    };

}

#endif
