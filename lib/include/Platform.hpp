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

#ifndef __OS_PLATFORM_H__
#define __OS_PLATFORM_H__

#if defined (__WIN32__) || defined (_WIN32) || defined (cygwin) || defined (mingw32)

#	define OS_PLATFORM_WIN32

#	define sockclose ::closesocket

/* Disable some deprecated warnings on Windows (Visual C++) */
#   ifdef _MSC_VER
#	    define _CRT_SECURE_NO_WARNINGS
#	    pragma warning (disable: 4100 4996 4276 4267 4099 4512 4127 4706 4251)
#   endif

/* Set dllimport/export correctly */
#if defined (OS_BUILD_DLL)
#   define DLL_SPEC __declspec (dllexport)
#else
#   define DLL_SPEC __declspec (dllimport)
#endif

/* Enable debug logging if DEBUG is set */
#	if (defined (DEBUG) || defined (_DEBUG)) && !defined (OS_DEBUG)
#		define OS_DEBUG
#	endif

#elif defined (__APPLE_CC__)

#	define OS_PLATFORM_APPLE
#	define OS_POSIX_COMPAT

#	define sockclose ::close
#	define SOCKET int

#elif defined (__linux__)

#	define OS_PLATFORM_LINUX
#	define OS_POSIX_COMPAT

#	define sockclose ::close
#	define SOCKET int

#else

#   error "Your platform and/or compiler is currently not supported!"

#endif

#ifndef DLL_SPEC
#   define DLL_SPEC
#endif

#include "Types.hpp"

#endif
