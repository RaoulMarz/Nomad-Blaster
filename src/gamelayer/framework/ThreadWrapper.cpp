#include "ThreadWrapper.h"

void ThreadWrapper::operator()(std::string argumentsSerialStr,
     AliveConnectStruct sessionIpcPipe, std::optional<IpcSharedSegment<std::string> *> optionalSharedSegmentIpc, bool startImmediate,
     std::function<void(std::string argumentsSerialStr,
     AliveConnectStruct sessionIpcPipe, std::optional<IpcSharedSegment<std::string> *> optionalSharedSegmentIpc)> runCallback                                                                                                                                                   )
{
    counter = 0;

    if (startImmediate)
    {
        runCallback(argumentsSerialStr, sessionIpcPipe, optionalSharedSegmentIpc);
    }
    else
    {
        for (int i = 0; i < 10; i++)
            std::cout << "Thread using function"
                         " object as callable\n";
    }
}

bool ThreadWrapper::TimerTickCall(const std::map<std::string, std::string> &argumentFieldValues, int &refCounter)
{
    refCounter += 1;
    //std::string displayTimerText = Glib::ustring::format(std::fixed, std::setprecision(1), (double)refCounter / 10);
    //std::cout << "Timer counter = " << displayTimerText << std::endl;
    return enableTimer;
}
