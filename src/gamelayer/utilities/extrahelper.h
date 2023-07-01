#ifndef EXTRA_HELPER_H
#define EXTRA_HELPER_H

#include <algorithm>
#include <cctype>
#include <cstring>
#include <locale>
#include <map>
#include <list>
#include <optional>
#include <sstream>
//#include <experimental/filesystem>
#include <filesystem>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include "CommandArgumentsStructure.h"

static const char *PATHSEP = "/";
static const char PATHSEPCHAR = '/';

class ExtraHelper {
public:
  // static std::string printVector2(Vector2 vec, std::string tag = "");
  //  trim from start (in place)

  static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int ch) { return !std::isspace(ch); }));
  }

  // trim from end (in place)

  static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }

  // trim from both ends (in place)

  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  static inline std::string fillString(std::string source, int fillSize,
                                       char fillchar) {
    std::stringstream ss(source);
    int unfilled = fillSize - source.size();
    if (unfilled > 0) {
      for (int ic = 0; ic < unfilled; ic++)
        ss << fillchar;
    }
    return ss.str();
  }

  static inline std::string fillStringExtended(std::string source, int fillSize,
                                               std::string fillStr,
                                               bool prepend = false) {
    std::stringstream ss;
    int unfilled = (fillSize - source.size()) / fillStr.length();
    if (unfilled > 0) {
      if (prepend) {
        ss.str("");
        for (int ic = 0; ic < unfilled; ic++)
          ss << fillStr;
        ss << source;
      } else {
        ss << source;
        for (int ic = 0; ic < unfilled; ic++)
          ss << fillStr;
      }
    } else {
      ss << source;
    }
    return ss.str();
  }

  static inline std::string replaceCharacters(std::string source, char findChar, char replaceChar)
  {
    std::string res = source;
    std::replace( res.begin(), res.end(), findChar, replaceChar);
    return res;
  }

  static void strrangecopy2(const char *stSource, char *stDest, int destLen,
                            int iFrom, int iTo) {
    int idx = 0;
    memset(stDest, 0, destLen);
    if (iTo < destLen) {
      for (idx = iFrom; idx <= iTo; idx++) {
        stDest[idx - iFrom] = stSource[idx];
      }
    }
  }

  static std::string ucharToString(const unsigned char *ucharText) {
    std::string res = "";
    if (ucharText != nullptr) {
      int slen = strlen((const char *)ucharText);
      for (int is = 0; is < slen; is++) {
        res.push_back(ucharText[is]);
      }
    }
    return res;
  }

  static std::string ucharToString(const unsigned char *ucharText, int ustrLen) {
    std::string res = "";
    if (ustrLen <= 0)
      return res;
    if (ucharText != nullptr) {
      for (int is = 0; is < ustrLen; is++) {
        res.push_back(ucharText[is]);
      }
    }
    return res;
  }

  static inline bool StringEndsWith(std::string main, std::string sub) {
    bool res = false;
    if ((main.length() >= 1) && (sub.length() <= main.length())) {
      size_t findIdx = main.rfind(sub);
      if (findIdx != std::string::npos) {
        res = findIdx >= (main.length() - sub.length());
      }
    }
    return res;
  }

  static std::string stringBetween(std::string mainStr, std::string first, std::string last);

  static bool stringToBool(std::string evalStr) {
    bool op;
    std::transform(evalStr.begin(), evalStr.end(), evalStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::istringstream(evalStr) >> std::boolalpha >> op;
    return op;
  }

  static std::string boolToString(bool value) {
    std::string res = value ? "true" : "false";
    return res;
  }

  static std::vector<std::string> readFileAsVector(std::string dataFile);

  static std::string readFileAsString(std::string dataFile,
                                      bool newLineMethod = false);

  static bool writeTextFile(std::string dataFile, std::string text,
                            bool append = true);

  static std::string getWorkingPath();

  static std::string combineFilePath(std::string aPath, std::string aFile);
  static std::string combineFilePath(std::string aPath,
                                     std::string secondaryPath,
                                     std::string aFile);

  static std::string extractFullPath(std::string path) {
    std::string res = path;
    if (path.length() > 0) {
      /// FIX ///
      //boost::filesystem::path p(path);
      //const boost::filesystem::path dir = p.remove_filename();
      /// FIX ///
      //res = dir.filename().string();
    }
    return res;
  }

  static void extractFilename(const char *path, char *newfile, int strsize) {
    int idx = 1;
    int pathlen = strlen(path);
    memset(newfile, 0, strsize);
    bool bPathSep = false;
    for (idx = pathlen - 1; idx > 0; idx--) {
      if (path[idx] == PATHSEPCHAR) {
        bPathSep = false;
        strrangecopy2(path, newfile, strsize, idx + 1, pathlen);
        break;
      }
    }
    if (bPathSep == false)
      strrangecopy2(path, newfile, strsize, 0, pathlen);
  }

  static std::string extractFilenameStr(std::string path) {
    std::string newstring = path;
    if (path.length() > 0) {
      int idx = 1;
      int pathlen = path.length();
      for (idx = pathlen - 1; idx > 0; idx--) {
        if (path[idx] == PATHSEPCHAR) {
          newstring = path.substr(idx + 1, pathlen - idx - 1);
          break;
        }
      }
    }
    return newstring;
  }

  static const std::string generateCommandLineFromStringMap(
      std::map<std::string, std::string> &argumentFieldsMap) {
    std::string res = "";
    if (argumentFieldsMap.size() > 0) {
      std::stringstream ss;
      for (const auto &ele : argumentFieldsMap) {
        ss << " --" << ele.first << "=" << ele.second;
      }
      res = ss.str();
    }
    return res;
  }

  static const std::string generateCommandLineFromStringMap(
      std::map<std::string, std::string> &argumentFieldsMap,
      std::vector<std::string> &omitFlagValues) {
    std::string res = "";
    if (argumentFieldsMap.size() > 0) {
      std::stringstream ss;
      for (const auto &ele : argumentFieldsMap) {
        bool omitFound = false;
        if (omitFlagValues.size() > 0) {
          if (std::find(omitFlagValues.begin(), omitFlagValues.end(),
                        ele.first) != omitFlagValues.end())
            omitFound = true;
        }
        if (omitFound)
          ss << " --" << ele.first;
        else
          ss << " --" << ele.first << "=" << ele.second;
      }
      res = ss.str();
    }
    return res;
  }

  static void generateCommandLineVectorFromStringMap(
      std::map<std::string, std::string> &argumentFieldsMap,
      std::vector<std::string> &omitFlagValues,
      std::vector<std::string> &appArgumentsVector) {
    if (argumentFieldsMap.size() > 0) {
      std::stringstream ss;
      for (const auto &ele : argumentFieldsMap) {
        ss.clear();
        ss.str("");
        bool omitFound = false;
        if (omitFlagValues.size() > 0) {
          if (std::find(omitFlagValues.begin(), omitFlagValues.end(),
                        ele.first) != omitFlagValues.end())
            omitFound = true;
        }
        if (omitFound)
          ss << "--" << ele.first;
        else
          ss << "--" << ele.first << "=" << ele.second;
        appArgumentsVector.push_back(ss.str());
      }
    }
  }

  static std::string getArgumentDefaultValue(
      const std::map<std::string, std::string> &argumentFieldValues,
      std::string argumentToken, std::string defaultValue) {
    std::string res = defaultValue;
    if (argumentFieldValues.size() > 0) {
      if (argumentFieldValues.find(argumentToken) !=
          argumentFieldValues.end()) {
        res = argumentFieldValues.at(
            argumentToken); // argumentFieldValues[argumentToken];
      }
    }
    return res;
  }

  template <typename T>
  static std::string printDebugVector(std::string tag,
                                      std::vector<T> vectorList) {
    std::stringstream stringreader;
    for (T item : vectorList) {
      stringreader << item << std::endl;
    }
    return stringreader.str();
  }

  static void
  splitVectorWords(const std::string &text, const std::string &separators,
                   std::list<std::string, std::allocator<std::string>> &words,
                   bool includeBlank);
  static std::optional<std::vector<std::string>>
  splitWords(std::string myText, std::string separator = "",
             bool includeBlank = false);
  static std::vector<std::string> SplitTextOn(std::string mainStr,
                                              std::string split,
                                              bool includeSplit = false);

  static inline bool fileExists(std::string aFile) {
    struct stat buffer;
    return (stat(aFile.c_str(), &buffer) == 0);
  }

  static inline bool pathExists(std::string aPath) {
    struct stat buffer;
    if (stat(aPath.c_str(), &buffer) == 0)
      return S_ISDIR(buffer.st_mode);
    return false;
  }

  static inline void createPath(std::string aPath) {
    mkdir(aPath.c_str(), 0777);
    // fs::create_directories(aPath);
  }

  static void copyFile(std::string sourcePath, std::string destinationPath,
                       std::string fileName);

  static inline bool deleteFile(std::string aFile) {
    bool res = fileExists(aFile);
    if (res)
    {
      /// FIX ///
      std::filesystem::remove(aFile);
    }
    return res;
  }

  static inline std::string removeIfPathExists(std::string aPath,
                                               std::string subPath) {
    std::string res = aPath;
    size_t findIdx = aPath.rfind(subPath);
    if (findIdx != std::string::npos) {
      if (findIdx >= aPath.length() - subPath.length()) {
        res = aPath.substr(0, findIdx - 1);
      }
    }
    return res;
  }

  static inline std::string getCurrentWorkingDirectory() {
    std::string res = "";
    char buff[FILENAME_MAX]; // create string buffer to hold path
    getcwd(buff, FILENAME_MAX);
    res = buff;
    return res;
  }

  static std::optional<CommandArgumentsStructure>
  generateFundamentalCommandArguments(std::string appArgument,
                                      std::string argumentsText) {
    std::optional<CommandArgumentsStructure> result = std::nullopt;
    if (argumentsText.size() > 0) {
      std::string commandLine = appArgument + " " + argumentsText;
      // std::vector<std::string> argTokens = SplitTextOn(commandLine, " ");
      std::optional<std::vector<std::string>> argTokens =
          splitWords(commandLine);
      if (!argTokens)
        return result;
      int argCount = argTokens->size();
      result = std::make_optional<CommandArgumentsStructure>(
          CommandArgumentsStructure());
      result->argc = argCount;
      char **result_argv = new char *[argCount];
      for (int ia = 0; ia < argCount; ia++) {
        result_argv[ia] = new char[512];
        memset(result_argv[ia], 0, 512);
      }
      int ix = 0;
      for (std::string argItem : *argTokens) {
        trim(argItem);
        strncpy(result_argv[ix], argItem.c_str(), argItem.length());
        ix += 1;
      }
      result->argv = result_argv;
    }
    return result;
  }

  std::string printShortTimestamp();

  static int getIntValue(std::string parseText, std::string field);

  static std::vector<std::string> getVectorListValue(std::string parseText,
                                                     std::string field);

  static int
  getIndexMatchedString(const std::vector<std::string> &vectorStringValues,
                        std::string compare, int indexOffset = 0);

};

#endif
