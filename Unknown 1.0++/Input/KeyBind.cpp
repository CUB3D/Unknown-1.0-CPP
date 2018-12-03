#include <utility>

//
// Created by cub3d on 10/07/2018.
//

#include "KeyBind.h"
#include <rttr/registration.h>

Unknown::KeyBind::KeyBind(int keycode, const std::string& name) : keycode(keycode), currentState(InputState::RELEASED), name(name), enabled(true) {
    registerEventHandler(ET_KEYPRESS, name, [&] (Event& evt){this->handle(evt);});
}

Unknown::KeyBind::KeyBind(int keycode, const std::string& name, std::function<void(Event &evt)> event) : KeyBind(keycode, name) {
    this->callback = std::move(event);
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
    return this->currentState == InputState::PRESSED && enabled;
}

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<KeyBind>("KeyBind")
            .constructor<int, const std::string>()
            .property("Keycode", &KeyBind::keycode)
            .property("CurrentState", &KeyBind::currentState)
            .property("Name", &KeyBind::name);
};
