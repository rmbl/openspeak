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

#include "LogMgr.hpp"

namespace openSpeak
{

	LogMgr::LogMgr() : mDefaultLog(0), mPath("")
	{

	}

	LogMgr::LogMgr(const std::string &filename, const Log::Level &minLvl) : mPath("")
	{
		createLog(filename, minLvl, true);
	}

	LogMgr::LogMgr(const std::string &path, const std::string &filename, const Log::Level &minLvl) : mPath(path)
	{
		createLog(filename, minLvl, true);
	}

	LogMgr::~LogMgr()
	{
		while(!mLogs.empty())
		{
			delete mLogs.begin()->second;
			mLogs.erase(mLogs.begin());
		}
	}

	Log* LogMgr::createLog(const std::string &filename, const openSpeak::Log::Level &minLvl, bool _default)
	{
		Log *tmp = new Log(mPath + filename, minLvl);
		if (_default)
			mDefaultLog = tmp;
		mLogs.insert(std::make_pair(shortFilename(filename), tmp));
		return tmp;
	}

	void LogMgr::removeLog(const std::string &filename)
	{
		LogMap::iterator it = mLogs.find(filename);
		if (it == mLogs.end())
			return;
		
		if (mDefaultLog == it->second)
			mDefaultLog = 0;
		delete it->second;
		mLogs.erase(it);
	}

	Log* LogMgr::getLog(const std::string &filename) const
	{
		LogMap::const_iterator it = mLogs.find(filename);
		return (it != mLogs.end() ? it->second : 0);
	}

	std::string LogMgr::shortFilename(const std::string &filename) const
	{
        std::string::size_type index = filename.find_last_of('/');
        if (index == std::string::npos)
        {
            index = filename.find_last_of('\\');
            if (index == std::string::npos)
                return filename;
        }
		return filename.substr( (index == std::string::npos) ? 0 : index+1);
	}
}
