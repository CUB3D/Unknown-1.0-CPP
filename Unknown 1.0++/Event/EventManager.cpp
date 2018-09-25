#include "../stdafx.h"

#include "EventManager.h"
#include <algorithm>
#include <iostream>
#include "../Unknown.h"

void Unknown::registerEventHandler(EventType listenerType, std::string name, std::function<void(Event&)> func)
{
    auto& eventHandlers = getUnknown().eventHandlers;

    auto iter = eventHandlers.find(listenerType);

    EventHandler eventHandler;
    eventHandler.name = name;
    eventHandler.callback = func;

    if(iter != eventHandlers.end()) {
        iter->second.push_back(eventHandler);
        eventHandlers[listenerType] = iter->second;
    } else {
        std::vector<EventHandler> newVec;
        newVec.push_back(eventHandler);
        eventHandlers[listenerType] = newVec;
    }
}

void Unknown::removeEventHandler(EventType type, std::string name)
{
    auto& eventHandlers = getUnknown().eventHandlers;
    std::vector<EventHandler>& handlers = eventHandlers[type];

    for(EventHandler& a : handlers) {
        handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&name](EventHandler& handler){return handler.name == name;}));
    }
}

void Unknown::postEvent(EventType type, Event& event)
{
    auto& eventHandlers = getUnknown().eventHandlers;
    std::vector<EventHandler>& handlers = eventHandlers[type];

    for(auto& a : handlers) {
        a.callback(event);
    }
}
