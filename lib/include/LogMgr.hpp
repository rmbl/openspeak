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

#ifndef __OS_LOG_MGR_HPP__
#define __OS_LOG_MGR_HPP__

#include "Log.hpp"
#include "Singleton.hpp"
#include <map>

namespace openSpeak
{

    /** \class LogMgr
     *  \brief Manages all available log files
     *
     * The LogMgr class manages all available log files including
     * their creation and destruction process. It also helps finding
     * specific logs or the default one.
     */
    class LogMgr : public openSpeak::Singleton<LogMgr>
    {
     private:
        /** \brief Map that will contain all logs and their corresponding names */
        typedef std::map<std::string, Log*> LogMap;

     public:
        /** \brief The constructor of the LogMgr class */
        LogMgr (void);

        /** \brief The constructor of the LogMgr class
         *  \param filename The filename of the default log
         *  \param minLvl The minimum logging level to write to stdout
         */
        LogMgr (const std::string &filename, const Log::Level &minLvl = Log::LVL_ERROR);

        /** \brief The constructor of the LogMgr class
         *  \param path The path where all logs should be saved
         *  \param filename The filename of the default log
         *  \param minLvl The minimum logging level to write to stdout
         */
        LogMgr (const std::string &path, const std::string &filename, 
                const Log::Level &minLvl = Log::LVL_ERROR);

        /** \brief The destructor of the LogMgr class */
        ~LogMgr (void);

        /** \brief Create a new log
         *  \param filename The filename of the new log
         *  \param minLvl The minimum logging level to write to stdout
         *  \param _default Make the log the default log?
         *  \return The new log
         */
        Log* createLog (const std::string &filename, 
                const Log::Level &minLvl = Log::LVL_ERROR, bool def = false);

        /** \brief Remove/Destroy a log
         *  \param filename The filename of the log to remove
         */
        void removeLog (const std::string &filename);

        /** \brief Get a specific log
         *  \param filename The filename of the log to get
         *  \return The log or 0 if the log couldn't be found
         */
        Log* getLog (const std::string &filename) const;

        /** \brief Get the default log
         *  \return The default log
         */
        inline Log* getDefaultLog (void) const { return mDefaultLog; }

     private:
        std::string shortFilename (const std::string &filename) const;

        LogMap		mLogs;          /**< The map with all logs in it */
        Log*		mDefaultLog;    /**< The default log */
        std::string mPath;			/**< The path where logs get saved */
    };

}

#endif
