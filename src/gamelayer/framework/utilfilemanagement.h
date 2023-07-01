/* 
 * File:   utilfilemanagement.h
 * Author: raoul
 *
 * Created on November 14, 2014, 2:19 PM
 */

#ifndef UTILFILEMANAGEMENT_H
#define	UTILFILEMANAGEMENT_H

#include <string>
#include <vector>

using namespace std;

class utilfilemanagement {
public:    
    static void deletefiles(vector<string>* fileList, int filecount);
    static void deletedir(char* directory, int Level);
    static void deletedir(const char* directory, int Level, unsigned long listLimit);
    static int randomise_file(string filename);
    static void secure_deletefiles(vector<string>* fileList, int filecount);
    static void secureremove(string &path, string &filter);
    static void copyfiles(vector<string>* fileList, const char *srcdir, const char *destdir, int filecount, bool omitSrcPath);
    static void copyfiles(vector<string>* fileList, const char *srcdir, const char *destdir, int filecount);
    static void copyfiles(vector<string>* fileList, vector<string>* cplist, const char *srcdir,
        const char *destdir, int filecount, bool omitSrcPath);
    static void copyfiles(vector<string>* fileList, vector<string>* cplist, const char *srcdir,
        const char *destdir, int filecount);
    static void removepathprefix(string pathStr, const char * prefixPath, string * replacePath);
    static void copyfiles_extra(vector<string>* fileList, vector<string>* cplist, const char *prefixdir,
        const char *srcdir, const char *destdir, int filecount, int offset, bool omitSrcPath);
    static vector<string>* getfilelistfromsource(char *path, int *count);
    static vector<string>* fastread(FILE * input, int *count);
    static void unixtodos(const char * fileName);
private:
    static int endswith(char *str, char cmpchar);
};

#endif	/* UTILFILEMANAGEMENT_H */

