#ifndef __THREAD_REGISTER_H
#define __THREAD_REGISTER_H

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <thread>
#include "datetime.h"

struct ThreadRegisterStruct {
    std::string description;
    std::string action;
    std::thread::id threadID;
    jed_utils::datetime actionTime;
};

class ThreadRegister {
private:
    std::vector<ThreadRegisterStruct> storeThreadRegisterList;
public:
    void registerThread(std::string description, std::string action, std::thread *threadObj, jed_utils::datetime actionTime) {
        std::thread::id this_id = threadObj->get_id();
        storeThreadRegisterList.push_back(ThreadRegisterStruct{description, action, this_id, actionTime});
    }

    std::string to_string() const {
        std::stringstream ssInfo;
        for (ThreadRegisterStruct threadRecord : storeThreadRegisterList)
        {
            ssInfo << "description = " << threadRecord.description;
            ssInfo << "\taction = " << threadRecord.action;
            ssInfo << "\tthreadID = " << threadRecord.threadID;
            ssInfo << "\ttimestamp = " << threadRecord.actionTime << std::endl;
        }
        return ssInfo.str();
    }
};

#endif
