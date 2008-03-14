//
// C++ Interface: PluginCreator
//
// Description: 
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PLUGIN_CREATOR_H
#define PLUGIN_CREATOR_H

class PluginCreator {
    public: 
        virtual ~PluginCreator() { }
    protected:
        virtual void writeSource () = 0;
        bool compile (QString);
        bool link (QString);
};

#endif
