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

#ifndef __OS_EXCEPTION_HPP__
#define __OS_EXPEPTION_HPP__

#include "Platform.hpp"
#include "StringUtils.hpp"
#include <exception>
#include <iostream>

namespace openSpeak
{
	/** \class Exception
	 *	\brief Provides an easy way to throw exceptions with some informations
	 *
	 *	The Exception class is meant as an easy way to throw exceptions on 
     *  errors with the help of the EXCEPTION() macro.
	 *	You can get the message of the exception and print it by hand 
     *  or let the class do everything.
	 */
	class DLL_SPEC Exception : public std::exception
	{
	 public:
		/** \brief The constructor of the Exception class
		 *	\param msg The message/error of the exception
		 *	\param file The file in which the exception got thrown
		 *	\param line The line in the file where the exception got thrown
		 */
		Exception (const std::string &msg, const std::string &file, const ushort &line) 
                : mMessage (msg), mFile (file), mLine (line) { }

		/** \brief The destructor of the Exception class */
		virtual ~Exception (void) throw () { } 

		/** \brief Print the exception to stderr */
		inline void print (void) const { std::cerr << what () << "\n"; }
        
        /** \brief Returns the cause of the exception */
        virtual const char* what () const throw ()
        {
            return std::string (mFile + ":" + StringUtils::toString (mLine) +
                    ": " + mMessage).c_str ();
        }

        inline bool empty (void) const { return mMessage.empty (); }

	 protected:
		const std::string mMessage;		/**< The message */
		const std::string mFile;		/**< The filename */
		const ushort mLine;				/**< The line number */
	};

/** \brief A helper macro to ease the use of the exception class */
#define EXCEPTION(x) throw openSpeak::Exception(x, __FILE__, (ushort)__LINE__)

}

#endif
