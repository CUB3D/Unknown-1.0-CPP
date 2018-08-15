#ifndef UNKNOWN_EVENT_MANAGER_H
#define UNKNOWN_EVENT_MANAGER_H

#include <functional>
#include <map>
#include <vector>
#include "Event.h"

namespace Unknown
{
    struct EventHandler
    {
        std::function<void(Event&)> callback;
        std::string name;
    };

    void registerEventHandler(EventType listenerType, std::string, std::function<void(Event&)> func);
    void removeEventHandler(EventType type, std::string name);
    void postEvent(EventType type, Event& event);
}
#endif
