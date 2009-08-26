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

#ifndef __OS_LOG_HPP__
#define __OS_LOG_HPP__

#include "Platform.hpp"
#include "Thread.hpp"
#include <string>
#include <fstream>

namespace openSpeak
{

	/** \class Log
     *	\brief Logs given output to stderr and to a file
	 *
	 *	The Log class logs every message given to a file and (if needed) to stdout.
	 */
	class DLL_SPEC Log
	{
	 public:
		/** \brief The level of the log msg */
		enum Level
		{
			LVL_DEBUG,
			LVL_INFO,
			LVL_ERROR,
			LVL_FATAL,
			LVL_SILENT
		};

	 public:
		/** \brief The constructor of the Log class
		 *	\param filename The file we should log to
		 *	\param minlvl Determines the minimum level to write to stdout
		 */
		Log (const std::string &filename, const Level &minlvl = LVL_INFO);

		/** \brief The destructor of the Log class */
		~Log (void);

		/** \brief Log a message into file/to console
		 *	\param msg The message we want to log
		 *	\param lvl The level of the message
		 */
		void logMsg (const std::string &msg, const Level &lvl = LVL_INFO);

	 protected:
		 /** \brief Get the logging level as a string
		  *  \param lvl The level to convert
		  *	 \return String with the level
		  */
		 std::string lvlToString (const Level &lvl, const bool &color = false) const;

		 std::ofstream  mFile;	    /**< The output file stream */
		 Level          mMinLvl;    /**< The minimum logging level to write to stdout */
         Mutex          mMutex;     /**< Mutex to protected the log from several 
                                    accesses at the same time */
	};

}

#endif
