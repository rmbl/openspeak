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

#include "PluginInterfaceProvider.hpp"
#include "PluginMgr.hpp"
#include "Exception.hpp"
#include "NLS.hpp"

namespace openSpeak
{

    namespace Client
    {
        
        PluginInterfaceProvider::PluginInterfaceProvider (const std::string &type)
                : Type (type)
        {
            PluginMgr::getSingleton ()->registerIFaceProvider (this);
        }
        
        PluginInterfaceProvider::~PluginInterfaceProvider ()
        {
            while (!mIFaces.empty ())
            {
                delete *mIFaces.begin ();
                mIFaces.erase (mIFaces.begin ());
            }
        }
        
        void PluginInterfaceProvider::addClass (PluginInterface *plugin)
        {
            if (!plugin)
                EXCEPTION (_("Recieved a null pointer"));
            
            mIFaces.push_back (plugin);
        }
        
        void PluginInterfaceProvider::removeClass (PluginInterface *plugin)
        {
            if (!plugin)
                EXCEPTION (_("Recieved a null pointer"));
                
            for (InterfaceVector::iterator it = mIFaces.begin (); it != mIFaces.end ();
                    ++it)
            {
                if ((*it) == plugin)
                {
                    mIFaces.erase (it);
                    break;
                }
            }
        }
        
        StringVector PluginInterfaceProvider::getInterfaces ()
        {
            StringVector ret;
            for (InterfaceVector::const_iterator it = mIFaces.begin (); 
                    it != mIFaces.end (); ++it)
            {
                if (!(*it)->Name.empty ())
                    ret.push_back ((*it)->Name);
            }
            
            return ret;
        }
        
    }
    
}
