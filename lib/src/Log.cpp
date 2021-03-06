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

#include "Log.hpp"
#include "NLS.hpp"
#include <iostream>
#include <ctime>

namespace openSpeak
{
	
	Log::Log (const std::string &filename, const Level &minlvl) : mMinLvl (minlvl)
	{
		mFile.open (filename.c_str ());
	}

	Log::~Log ()
	{
		mFile.flush ();
		mFile.close ();
	}

	void Log::logMsg (const std::string &msg, const Level &lvl)
	{
        MutexLocker lock (mMutex);

	/* Get the current time */
		time_t rawtime;
		char buffer [80];
		struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);

		strftime (buffer, 80, "[%x %X]", timeinfo);

	/* Write it to the file */
		mFile << buffer << " [" << lvlToString (lvl) << "] " << msg << "\n";
		mFile.flush ();

	/* Write to stdout if wanted */
		if (lvl >= mMinLvl && lvl != LVL_SILENT)
			std::cout << " [" << lvlToString (lvl, true) << "] " << msg << "\n";
	}

	std::string Log::lvlToString (const Level &lvl, const bool &color) const
	{
		switch (lvl)
		{
			case LVL_DEBUG:
				return (color) ? _("\033[0;34m DEBUG \033[0m") : _(" DEBUG ");
			case LVL_INFO:
				return (color) ? _("\033[0;32m INFO  \033[0m") : _(" INFO  ");
			case LVL_ERROR:
				return (color) ? _("\033[1;31m ERROR \033[0m") : _(" ERROR ");
			case LVL_FATAL:
				return (color) ? _("\033[0;31m FATAL \033[0m") : _(" FATAL ");
			default:
				return _("DEFAULT");
		}
	}
}
