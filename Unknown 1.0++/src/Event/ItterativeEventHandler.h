//
// Created by cub3d on 10/07/2018.
//

#ifndef UNKNOWN_GAME_ITTERATIVEEVENTHANDLER_H
#define UNKNOWN_GAME_ITTERATIVEEVENTHANDLER_H

#include <Unknown.h>
#include <vector>
#include <functional>

namespace Unknown
{
    template <typename T, typename A>
    void registerItterativeEventHandler(HookType type, std::vector<T, A>& vec, std::function<void(T& t)> callback) {
        registerHook([&vec, callback] {
            for(auto& x : vec) {
                if(callback) {
                    callback(x);
                }
            }
        }, type);
    };
}


#endif //UNKNOWN_GAME_ITTERATIVEEVENTHANDLER_H
