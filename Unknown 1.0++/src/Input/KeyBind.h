//
// Created by cub3d on 10/07/2018.
//

#ifndef UNKNOWN_GAME_KEYBIND_H
#define UNKNOWN_GAME_KEYBIND_H


#include <string>
#include <core/hook/Event.h>


namespace Unknown {
    class KeyBind {
    public:
        int keycode;
        bool currentState;
        std::string name;
        bool enabled;

        KeyBind(int keycode, const std::string& name);

        void handle(KeyPressEvent& evt);

        bool pressed() const;
    };
}

#endif //UNKNOWN_GAME_KEYBIND_H
