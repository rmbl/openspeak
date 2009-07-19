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

#ifndef __OS_SINGLETON_HPP__
#define __OS_SINGLETON_HPP__

#include <cassert>

namespace openSpeak
{
	
	/** \class Singleton
	 *	\brief Abstract class which provides other classes an easy way to implement singleton behaviour.
	 *
	 *	The Singleton class is an easy way to add singleton behaviour to a class. This means that there can only be one instance of the class
	 *	and you can easily access the class from everywhere with a simple Classname::getSingleton().
	 */
    template <typename T> class Singleton
    {
     protected:
		/** \brief The instance we're using */
        static T* mSingleton;

     public:
		/** \brief The constructor of the Singleton class */
        Singleton (void)
        {
            assert (!mSingleton);
            mSingleton = static_cast <T*> (this);
        }

		/** \brief The destructor of the Singleton class */
        ~Singleton (void)
        {
            assert (mSingleton);
            mSingleton = 0;
        }

		/** \brief Get the instance of the class */
        static T* getSingleton (void) { return mSingleton; }
    };

    template <typename T> T* Singleton <T>::mSingleton = 0;

}

#endif
