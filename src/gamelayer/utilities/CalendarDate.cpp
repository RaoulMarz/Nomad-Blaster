
/* 
 * File:   CalendarDate.cpp
 * Author: raoul
 * 
 * Created on 24 April 2020, 7:01 PM
 */

#include <iomanip>
#include <ctime>
#include "CalendarDate.h"

CalendarDate::CalendarDate() {
    timeval = std::time(nullptr);
}

CalendarDate::CalendarDate(const CalendarDate& orig) {
    timeval = orig.timeval;
}

CalendarDate::~CalendarDate() {
}

std::string CalendarDate::toString() {
    std::string res = std::string(std::asctime(std::localtime(&timeval)));
    return res.substr(0, res.length() - 1);
}

std::string CalendarDate::toString(std::string format) {
    std::tm tm = *std::localtime(&timeval);
    //return std::put_time(&tm, format.c_str());
    std::string res;
    return res;
}

