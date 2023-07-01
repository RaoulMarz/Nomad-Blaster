#ifndef _THREADWRAPPER_H
#define _THREADWRAPPER_H

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "AliveConnectStruct.h"
#include "IpcSharedSegment.h"

class ThreadWrapper
{
public:
    int counter = 0;
    bool enableTimer = true;

    void operator()(std::string argumentsSerialStr,
                    AliveConnectStruct sessionIpcPipe, std::optional<IpcSharedSegment<std::string> *> optionalSharedSegmentIpc,
                    bool startImmediate,
                    std::function<void(std::string argumentsSerialStr,
                    AliveConnectStruct sessionIpcPipe, std::optional<IpcSharedSegment<std::string> *> optionalSharedSegmentIpc)> runCallback);
    bool TimerTickCall(const std::map<std::string, std::string> &argumentFieldValues, int &refCounter);
};


#endif
