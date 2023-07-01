
/* 
 * File:   CalendarDate.h
 * Author: raoul
 *
 * Created on 24 April 2020, 7:01 PM
 */

#ifndef CALENDARDATE_H
#define CALENDARDATE_H

#include <string>
#include <ctime>

class CalendarDate {
public:
    CalendarDate();
    CalendarDate(const CalendarDate& orig);
    virtual ~CalendarDate();
    
    std::string toString();
    std::string toString(std::string format);
private:
    std::time_t timeval;// = std::time(nullptr);
};

#endif /* CALENDARDATE_H */

