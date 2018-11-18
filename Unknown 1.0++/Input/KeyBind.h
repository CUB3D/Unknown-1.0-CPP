//
// Created by cub3d on 10/07/2018.
//

#ifndef UNKNOWN_GAME_KEYBIND_H
#define UNKNOWN_GAME_KEYBIND_H


#include <string>

#include "Event/EventManager.h"

namespace Unknown {
    class KeyBind {
    private:
        std::function<void(Event& evt)> callback;
    public:
        int keycode;
        InputState currentState;
        std::string name;

        KeyBind(int keycode, const std::string& name);

        KeyBind(int keycode, const std::string& name, std::function<void(Event& evt)> event);

        void handle(Event& evt);

        bool pressed() const;
    };
}

#endif //UNKNOWN_GAME_KEYBIND_H
