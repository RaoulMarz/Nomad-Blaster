/***************************************************************************
 *   Copyright (C) 2006 by Raoul Marais   *
 *   raoul@linux   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DIRECTORYSCANNER_H
#define DIRECTORYSCANNER_H

#include <string>
#include <vector>
#include <optional>
//#include "stringlist.h"
#include "extrahelper.h"

/**
@author Raoul Marais
*/
class directoryscanner
{
private:
        std::string searchdir;
        std::string regexp;
        std::string prefix;
        std::string extension;
        //stringlist *lstFilesFound;
        char sepchar;
        const char *sepstr;
        bool absoluteflag;
        std::optional<std::vector<std::string>> lstFilesFound = std::nullopt;

        int endswith(const char *str, char cmpchar);
        bool strmatch_regexp(const std::string& regx, const std::string& text);
public:
        directoryscanner();
        directoryscanner(bool showabsolutepath);

        ~directoryscanner();

        void printdir(const char *maindir, const char *dir, int currlevel, int level);
        void printdir(const char *maindir, const char *dir, int currlevel, int level, unsigned long listLimit);
        void printdir(const char *maindir, const char *dir, int currlevel, int level, const std::string& regexpr);
        void removeFilesExclude(std::string dir, std::string filter, std::string excludeFile, int level);
        void setpath(std::string dir);
        void setfilter(std::string _regexp);
        void setfilter(std::string _prefix, std::string _extension);
        //void getresults(stringlist result);
        //stringlist* results();
        std::optional<std::vector<std::string>> results();
};

#endif
