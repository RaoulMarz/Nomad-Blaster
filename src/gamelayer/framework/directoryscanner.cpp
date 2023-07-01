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
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/regex.hpp>
#include <boost/filesystem/operations.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include "directoryscanner.h"

using namespace std;

bool directoryscanner::strmatch_regexp(const std::string& regx, const std::string& text) {
    boost::regex expression(regx);
    /*"^(template[[:space:]]*<[^;:{]+>[[:space:]]*)?"
    "(class|struct)[[:space:]]*"
    "(\\<\\w+\\>([[:blank:]]*\\([^)]*\\))?"
    "[[:space:]]*)*(\\<\\w*\\>)[[:space:]]*"
    "(<[^;:{]+>[[:space:]]*)?(\\{|:[^;\\{()]*\\{)");*/

    boost::cmatch what;

    if (regex_match(text.c_str(), what, expression)) {
        return true;
    }
    /*
   boost::regex e(regx);
   boost::smatch what;
  
   if(boost::regex_match(text, what, e, boost::match_extra))
   {
     **/
    /*
    unsigned i;
    std::cout << "** Match found **\n   Sub-Expressions:\n";
    for(i = 0; i < what.size(); ++i)
       std::cout << "      $" << i << " = \"" << what[i] << "\"\n";
     */
    ///   return TRUE;
    ///}
    return false;
}

directoryscanner::directoryscanner() {
    //lstFilesFound = new stringlist;
    sepchar = PATHSEPCHAR;
    sepstr = PATHSEP;
    absoluteflag = true;
}

directoryscanner::directoryscanner(bool showabsolutepath) {
    //lstFilesFound = new stringlist;
    sepchar = PATHSEPCHAR;
    sepstr = PATHSEP;
    absoluteflag = showabsolutepath;
}

directoryscanner::~directoryscanner() {
    //delete lstFilesFound;
}

int directoryscanner::endswith(const char *str, char cmpchar) {
    if (str == NULL)
        return 0;
    int slen = strlen(str);
    if (slen == 0)
        return 0;
    if (str[slen - 1] == cmpchar)
        return 1;
    else
        return 0;
}

void directoryscanner::printdir(const char *maindir, const char *dir, int currlevel, int level) {
    if (!lstFilesFound)
        lstFilesFound = std::make_optional<std::vector<std::string>>();
    if (currlevel == 1) {
        char* zeroitem = new char[2];
        memset(zeroitem, 0, 2);
        zeroitem[0] = ' ';
        zeroitem[1] = 0;
        ///lstFilesFound->add(zeroitem);
        lstFilesFound->push_back(zeroitem);
        delete [] zeroitem;
    }
    if (currlevel > level)
        return;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    int thislevel = currlevel + 1;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    int iextra = 0;
    int prlen = strlen(maindir);
    int dirlen = strlen(dir);
    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        iextra = 0;
        lstat(entry->d_name, &statbuf);
        int dlen = strlen(entry->d_name);
        if (S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if (strcmp(".", entry->d_name) == 0 ||
                    strcmp("..", entry->d_name) == 0)
                continue;
            //printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            int isize = prlen + dirlen + dlen + 4;
            char* newdir = new char[isize];
            memset(newdir, 0, isize);

            if ((absoluteflag == false) && (currlevel == 1)) {
                //strncpy(newdir, entry->d_name, dlen);
                //newdir[dlen] = 0;
                newdir[0] = 0;
            } else {
                //char* newdir = new char[prlen + dirlen + dlen + 4];
                //newdir = new char[prlen + dirlen + 4];

                if (prlen > 0) {
                    strncpy(newdir, maindir, prlen);
                    if (endswith(maindir, sepchar) == 0) {
                        strncat(newdir, sepstr, 1);
                        iextra = 1;
                    }
                    newdir[prlen + iextra] = 0;
                    strncat(newdir, dir, dirlen);
                    newdir[prlen + iextra + dirlen] = 0;
                } else {
                    strncpy(newdir, dir, dirlen);
                    newdir[dirlen] = 0;
                }

                strncat(newdir, sepstr, 1);
                newdir[prlen + dirlen + 1 + iextra] = 0;
            }
            printdir(newdir, entry->d_name, thislevel, level);
            delete [] newdir;
        } else {
            //printf("%*s%s\n",depth,"",entry->d_name);
            //see if the filename matches the filter if provided
            //printf("%*s%s/\n",depth,"",item);
            int isize = prlen + dirlen + dlen + 4;
            char* item = new char[isize];
            memset(item, 0, isize);
            if ((absoluteflag == false) && (currlevel == 1)) {
                strncpy(item, entry->d_name, dlen);
                item[dlen] = 0;
            } else {

                if (prlen > 0) {
                    strncpy(item, maindir, prlen);
                    //strcpy(item, maindir);
                    if (endswith(maindir, sepchar) == 0) {
                        strncat(item, sepstr, 1);
                        iextra = 1;
                    }
                    item[prlen + iextra] = 0;
                    strncat(item, dir, dirlen);
                } else {
                    strncpy(item, dir, dirlen);
                    item[dirlen] = 0;
                }
                //strncat(item, dir, dirlen);
                strncat(item, sepstr, 1);
                //memset(entry->d_name, 0, sizeof(entry->d_name) );
                strncat(item, entry->d_name, dlen);
                item[prlen + dirlen + dlen + 1 + iextra] = 0;
            }
            //printf("%d%s%s\n",currlevel,"  ",item);

            ///lstFilesFound->add(item);
            lstFilesFound->push_back(item);
            delete [] item;
        }
    }
    chdir("..");
    closedir(dp);
}

void directoryscanner::printdir(const char *maindir, const char *dir, int currlevel, int level, unsigned long listLimit) {
    if (!lstFilesFound)
        lstFilesFound = std::make_optional<std::vector<std::string>>();
    unsigned long trackCount = 0L;
    if (currlevel == 1) {
        char* zeroitem = new char[2];
        memset(zeroitem, 0, 2);
        zeroitem[0] = ' ';
        zeroitem[1] = 0;
        ///lstFilesFound->add(zeroitem);
        lstFilesFound->push_back(zeroitem);
        //delete [] zeroitem;
    }
    if (currlevel > level)
        return;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    int thislevel = currlevel + 1;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    int iextra = 0;
    int prlen = strlen(maindir);
    int dirlen = strlen(dir);
    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        trackCount++;
        if (trackCount > listLimit)
            break;
        iextra = 0;
        lstat(entry->d_name, &statbuf);
        int dlen = strlen(entry->d_name);
        if (S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if (strcmp(".", entry->d_name) == 0 ||
                    strcmp("..", entry->d_name) == 0)
                continue;
            //printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */
            int isize = prlen + dirlen + dlen + 4;
            char* newdir = new char[isize];
            memset(newdir, 0, isize);

            if ((absoluteflag == false) && (currlevel == 1)) {
                //strncpy(newdir, entry->d_name, dlen);
                //newdir[dlen] = 0;
                newdir[0] = 0;
            } else {
                if (prlen > 0) {
                    strncpy(newdir, maindir, prlen);
                    if (endswith(maindir, sepchar) == 0) {
                        strncat(newdir, sepstr, 1);
                        iextra = 1;
                    }
                    newdir[prlen + iextra] = 0;
                    strncat(newdir, dir, dirlen);
                    newdir[prlen + iextra + dirlen] = 0;
                } else {
                    strncpy(newdir, dir, dirlen);
                    newdir[dirlen] = 0;
                }

                strncat(newdir, sepstr, 1);
                newdir[prlen + dirlen + 1 + iextra] = 0;
            }
            //strncat(newdir, entry->d_name, dlen);
            //newdir[prlen + dirlen + dlen + 2] = 0;
            //usleep(50000);
            printdir(newdir, entry->d_name, thislevel, level);
            delete [] newdir;
        } else {
            //printf("%*s%s\n",depth,"",entry->d_name);
            //see if the filename matches the filter if provided
            //printf("%*s%s/\n",depth,"",item);
            int isize = prlen + dirlen + dlen + 4;
            /*
            if ( (currlevel == 1) && (strcmp(entry->d_name, "ChangeLog") == 0) ) {
                    printf("%s", entry->d_name);
            }
            if ( (currlevel == 1) && (strcmp(entry->d_name, "Makefile") == 0) ) {
                    printf("%s", entry->d_name);
            }
             */
            char* item = new char[isize];
            memset(item, 0, isize);
            if ((absoluteflag == false) && (currlevel == 1)) {
                strncpy(item, entry->d_name, dlen);
                item[dlen] = 0;
            } else {

                if (prlen > 0) {
                    strncpy(item, maindir, prlen);
                    if (endswith(maindir, sepchar) == 0) {
                        strncat(item, sepstr, 1);
                        iextra = 1;
                    }
                    item[prlen + iextra] = 0;
                    strncat(item, dir, dirlen);
                } else {
                    strncpy(item, dir, dirlen);
                    item[dirlen] = 0;
                }
                //strncat(item, dir, dirlen);
                strncat(item, sepstr, 1);
                //memset(entry->d_name, 0, sizeof(entry->d_name) );
                strncat(item, entry->d_name, dlen);
                item[prlen + dirlen + dlen + 1 + iextra] = 0;
            }
            //printf("%d%s%s\n",currlevel,"  ",item);

            ///lstFilesFound->add(item);
            lstFilesFound->push_back(item);
            delete [] item;
        }
    }
    chdir("..");
    closedir(dp);
}

void directoryscanner::printdir(const char *maindir, const char *dir, int currlevel, int level, const std::string& regexpr) {
    if (currlevel > level)
        return;
    if (!lstFilesFound)
        lstFilesFound = std::make_optional<std::vector<std::string>>();
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    std::string newRegExp = regexpr;

    int thislevel = currlevel + 1;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }

    int iextra = 0;
    int prlen = strlen(maindir);
    int dirlen = strlen(dir);
    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        iextra = 0;
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if (strcmp(".", entry->d_name) == 0 ||
                    strcmp("..", entry->d_name) == 0)
                continue;
            //cout << "DIR : " << entry->d_name << endl;
            //printf("%*s%s/\n",depth,"",entry->d_name);
            /* Recurse at a new indent level */

            int dlen = strlen(entry->d_name);
            //char* newdir = new char[prlen + dirlen + dlen + 4];
            char* newdir = new char[prlen + dirlen + 4];
            memset(newdir, 0, prlen + dirlen + 4);

            if (prlen > 0) {
                strncpy(newdir, maindir, prlen);
                if (endswith(maindir, sepchar) == 0) {
                    strncat(newdir, sepstr, 1);
                    iextra = 1;
                }
                newdir[prlen + iextra] = 0;
                strncat(newdir, dir, dirlen);
                newdir[prlen + iextra + dirlen] = 0;
            } else {
                strncpy(newdir, dir, dirlen);
                newdir[dirlen] = 0;
            }

            strncat(newdir, sepstr, 1);
            newdir[prlen + dirlen + 1 + iextra] = 0;

            printdir(newdir, entry->d_name, thislevel, level, regexpr);
            delete [] newdir;
        } else {
            //see if the filename matches the filter if provided
            //printf("%*s%s/\n",depth,"",item);
            //cout << "FILE : " << entry->d_name << endl;

            int dlen = strlen(entry->d_name);
            char* item = new char[prlen + dirlen + dlen + 4];
            memset(item, 0, prlen + dirlen + dlen + 4);

            if (prlen > 0) {
                strncpy(item, maindir, prlen);
                if (endswith(maindir, sepchar) == 0) {
                    strncat(item, sepstr, 1);
                    iextra = 1;
                }
                item[prlen + iextra] = 0;
                strncat(item, dir, dirlen);
            } else {
                strncpy(item, dir, dirlen);
                item[dirlen] = 0;
            }
            strncat(item, sepstr, 1);
            //memset(entry->d_name, 0, sizeof(entry->d_name) );
            strncat(item, entry->d_name, dlen);
            item[prlen + dirlen + dlen + 1 + iextra] = 0;

            if (strmatch_regexp(regexpr, /*item*/entry->d_name) == true) //If this file matches the regular expression
                lstFilesFound->push_back(std::string(item));
            delete [] item;
        }
    }
    chdir("..");
    closedir(dp);
}

void directoryscanner::removeFilesExclude(std::string dir, std::string filter, std::string excludeFile, int level) {
    printdir("", dir.c_str(), 1, level);
    std::optional<std::vector<std::string>> foundFilesList = results();
    if (foundFilesList)
    {
      for (std::string fileItem : *foundFilesList)
      {
          if (ExtraHelper::StringEndsWith(fileItem, excludeFile))
              continue;
          if (ExtraHelper::StringEndsWith(fileItem, filter))
          {
            ExtraHelper::deleteFile(fileItem);
          }
      }
    }
}

void directoryscanner::setfilter(string _regexp) {
    regexp = _regexp;
}

void directoryscanner::setfilter(string _prefix, string _extension) {
    prefix = _prefix;
    extension = _extension;
}

std::optional<std::vector<std::string>> directoryscanner::results() {
    //std::optional<std::vector<std::string>> res = std::nullopt;
    return lstFilesFound;
}

/*
void directoryscanner::getresults(stringlist result) {
    result = *lstFilesFound;
}

stringlist* directoryscanner::results() {
    stringlist* res = NULL;
    if ((lstFilesFound != NULL) && (lstFilesFound->count() > 0)) {
        res = new stringlist();
        lstFilesFound->clone(res);
    }
    return res;
}
*/
