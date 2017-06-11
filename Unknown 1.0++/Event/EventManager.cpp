#include "stdafx.h"

#include "EventManager.h"
#include <algorithm>

std::map<Unknown::EventType, std::vector<Unknown::EventHandler>> Unknown::eventHandlers;

void Unknown::registerEventHandler(EventType listenerType, std::string name, std::function<void(Event&)> func)
{
    auto iter = eventHandlers.find(listenerType);

    EventHandler eventHandler;
    eventHandler.name = name;
    eventHandler.callback = func;

    if(iter != eventHandlers.end())
    {
        iter->second.push_back(eventHandler);
    }
    else
    {
        iter->second = std::vector<Unknown::EventHandler>();

        iter->second.push_back(eventHandler);
    }

    eventHandlers[listenerType] = iter->second;
}

void Unknown::removeEventHandler(Unknown::EventType type, std::string name)
{
    std::vector<EventHandler>& handlers = eventHandlers[type];

    for(EventHandler a : handlers)
    {
        handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&name](EventHandler& handler){return handler.name == name;}));
    }
}

void Unknown::postEvent(Unknown::EventType type, Unknown::Event& event)
{
    std::vector<EventHandler>& handlers = eventHandlers[type];
    for(auto a : handlers)
    {
        a.callback(event);
    }
}
