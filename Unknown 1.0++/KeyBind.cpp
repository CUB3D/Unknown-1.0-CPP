//
// Created by cub3d on 10/07/2018.
//

#include "KeyBind.h"

Unknown::KeyBind::KeyBind(int keycode, const std::string& name) : keycode(keycode), currentState(InputState::RELEASED) {
    registerEventHandler(ET_KEYPRESS, name, [&] (Event& evt){this->handle(evt);});
}

Unknown::KeyBind::KeyBind(int keycode, const std::string& name, std::function<void(Event &evt)> event) : KeyBind(keycode, name) {
    this->callback = event;
}

void Unknown::KeyBind::handle(Event& evt) {
    if(evt.key.SDLCode == this->keycode) {
        this->currentState = evt.key.keyState;

        if(this->callback) {
            callback(evt);
        }
    }
}

bool Unknown::KeyBind::pressed() const {
    return this->currentState == InputState::PRESSED;
}
