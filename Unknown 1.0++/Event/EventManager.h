#ifndef UNKNOWN_EVENT_MANAGER_H
#define UNKNOWN_EVENT_MANAGER_H

#include <functional>
#include <map>
#include <vector>

#include "Event.h"

namespace Unknown
{
    enum EventType
    {
        ET_MOUSEBUTTON = 0,
        ET_KEYPRESS = 1,
        ET_WINDOW_RESIZE = 2
    };

    struct EventHandler
    {
        std::function<void(Event&)> callback;
        std::string name;
    };

    extern std::map<EventType, std::vector<EventHandler>> eventHandlers;

    void registerEventHandler(EventType listenerType, std::string, std::function<void(Event&)> func);
    void removeEventHandler(EventType type, std::string name);
    void postEvent(EventType type, Event& event);
}
#endif
