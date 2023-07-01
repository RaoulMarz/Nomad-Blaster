#include <sstream>
#include <fstream>
#include "extrahelper.h"

static const std::string FileSystemSeparator = "/";

/*
std::string ExtraHelper::printVector2(Vector2 vec, std::string tag) {
    std::stringstream ss;
    ss << tag << vec.x << "," << vec.y << std::endl;
    return ss.str();
}*/

std::string ExtraHelper::getWorkingPath()
{
    char workDirChars[2048];
    memset(workDirChars, 0, 2048);
    getcwd(workDirChars, 2047);
    return workDirChars;
}

std::string ExtraHelper::combineFilePath(std::string aPath, std::string aFile)
{
    return aPath + FileSystemSeparator + aFile;
}

std::string ExtraHelper::combineFilePath(std::string aPath, std::string secondaryPath, std::string aFile)
{
    return aPath + FileSystemSeparator + secondaryPath + FileSystemSeparator + aFile;
}

/* Taken from http://www2.roguewave.com/support/docs/sourcepro/edition9-update1/html/stdlibug/13-3.html*/
void ExtraHelper::splitVectorWords(const std::string& text, const std::string& separators,
            std::list<std::string, std::allocator<std::string> >& words, bool includeBlank) {

    size_t n     = text.length ();
    size_t start = text.find_first_not_of (separators);

    while (start < n) {
        size_t stop = text.find_first_of (separators, start);
        if (stop >= n)
            stop = n;
        std::string subtoken = "";
        if (stop > start)
            subtoken = text.substr(start, stop - start);
        words.push_back(subtoken);
        if (includeBlank) {
            start = stop + 1;
        } else
            start = text.find_first_not_of (separators, stop + 1);
    }
}

std::optional<std::vector<std::string>> ExtraHelper::splitWords(std::string myText, std::string separator, bool includeBlank) {
    std::optional<std::vector<std::string>> res = std::nullopt;
    std::string whitespaceChars = "\t\r\n ";
    std::string separatorfield;
    std::list<std::string, std::allocator<std::string> > words;
    if (separator.length() <= 0)
        separatorfield = whitespaceChars;
    else
        separatorfield = separator;
    splitVectorWords(myText, separatorfield, words, includeBlank);
    std::list<std::string, std::allocator<std::string> >::iterator wptr;
    if (words.begin () != words.end ()) {
        res = std::make_optional<std::vector<std::string>>(std::vector<std::string>());
        for (wptr = words.begin (); wptr != words.end (); ++wptr) {
            res->push_back(*wptr);
        }
    }
    return res;
}

std::vector<std::string> ExtraHelper::SplitTextOn(std::string mainStr, std::string split, bool includeSplit)
{
    std::vector<std::string> res;
    if ((mainStr.length() > 0) && (mainStr.length() > split.length()))
    {
        std::string workStr = mainStr;
        std::size_t found = 0;
        while ((found >= 0) && (found < workStr.length()))
        {
            found = workStr.find(split);
            if ((found >= 0) && (found < workStr.length()))
            {
                std::string foundStr = workStr.substr(0, found);
                workStr = workStr.substr(found + split.length());
                res.push_back(foundStr);
            }
        }
        if (workStr.length() > 0)
            res.push_back(workStr);
    }
    return res;
}

std::string ExtraHelper::stringBetween(std::string mainStr, std::string first, std::string last) {
    if ( (mainStr.length() > 0) && (first.length() > 0) && (first.length() <= mainStr.length()) ) {
        std::string xlast = first;
        if (last.length() > 0)
            xlast = last;
        int slen = mainStr.length();
        int ipos = mainStr.find(first);
        int ipos2 = -1;
        int firstlen = first.length();
        std::string workStr;
        if (ipos >= 0) {
            workStr = mainStr.substr(ipos + firstlen, slen - ipos - firstlen);
            ipos2 = workStr.find(xlast);
        }
        if (ipos2 >= 0) {
            workStr = workStr.substr(0, ipos2);
            return workStr;
        }
        else
            return mainStr;
    } else
        return mainStr;
}


std::vector<std::string> ExtraHelper::readFileAsVector(std::string dataFile)
{
    std::vector<std::string> res;
    std::string line;
    std::ifstream infile((const char *)dataFile.c_str(), std::ifstream::in);
    while (getline(infile, line, '\n'))
    {
        res.push_back(line);
    }
    return res;
}

std::string ExtraHelper::readFileAsString(std::string dataFile, bool newLineMethod)
{
    std::string line;
    std::stringstream ss;
    std::ifstream infile((const char *)dataFile.c_str(), std::ifstream::in);
    if (newLineMethod)
    {
        while (getline(infile, line, '\n'))
        {
            ss << line << std::endl;
        }
    }
    else
    {
        ss << infile.rdbuf();
    }
    return ss.str();
}

bool ExtraHelper::writeTextFile(std::string dataFile, std::string text, bool append)
{
    bool res = false;
    std::ofstream outFile;
    if (append)
        outFile.open(dataFile, std::ios_base::app);
    else
        outFile.open(dataFile, std::ios_base::out);
    outFile << text;
    outFile.close();
    res = true;
    return res;
}

void ExtraHelper::copyFile(std::string sourcePath, std::string destinationPath, std::string fileName)
{
    std::ifstream src(sourcePath, std::ios::binary);
    std::string destCopyPath = combineFilePath(destinationPath, fileName);
    std::ofstream dst(destCopyPath, std::ios::binary);
    dst << src.rdbuf();
}

std::string ExtraHelper::printShortTimestamp()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[128];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d%m%Y#%H%M%S", timeinfo);
    return buffer;
}

int ExtraHelper::getIntValue(std::string parseText, std::string field)
{
    int res = 0;
    auto index = parseText.find(field);
    if ((index >= 0) && (index < parseText.length()))
    {
        std::string valueTail = parseText.substr(index + field.length() + 1);
        ExtraHelper::trim(valueTail);
        if (valueTail.length() > 1)
        {
            res = std::stoi(valueTail);
        }
    }
    return res;
}

std::vector<std::string> ExtraHelper::getVectorListValue(std::string parseText, std::string field)
{
    std::vector<std::string> res;
    if ((parseText.length() > 1) && (parseText.length() > field.length()))
    {
        auto index = parseText.find(field);
        if ((index >= 0) && (index < parseText.length()))
        {
            std::string valueTail = parseText.substr(index + field.length());
            ExtraHelper::trim(valueTail);
            res = ExtraHelper::SplitTextOn(valueTail, ",", false);
        }
    }
    return res;
}

int ExtraHelper::getIndexMatchedString(const std::vector<std::string> &vectorStringValues, std::string compare, int indexOffset)
{
    int res = indexOffset - 1;
    int index = indexOffset;
    for (std::string strValue : vectorStringValues)
    {
        if (compare.find(strValue) >= 0)
        {
            res = index;
            break;
        }
        res += 1;
    }
    return res;
}
