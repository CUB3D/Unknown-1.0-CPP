//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_HOOKREGISTRY_H
#define UNKNOWN_HOOKREGISTRY_H

#include "Singleton.h"
#include <vector>

template<class T>
class HookRegistry: public Singleton<HookRegistry<T>> {
public:
    std::vector<std::function<void()>> callbacks;

    void add(const std::function<void()>& hook) {
        callbacks.push_back(hook);
    }

    void invoke() {
        for(auto&& callback : callbacks) {
            callback();
        }
    }
};

#endif //UNKNOWN_HOOKREGISTRY_H
