#include <utility>

//
// Created by cub3d on 10/07/2018.
//

#include "KeyBind.h"
#include <rttr/registration.h>
#include "core/hook/HookRegistry.h"
#include "core/hook/Event.h"

Unknown::KeyBind::KeyBind(int keycode, const std::string& name) : keycode(keycode), currentState(false), name(name), enabled(true) {
    HookRegistry<KeyPressEvent>::getInstance().add([&] (KeyPressEvent evt){this->handle(evt);});
}

void Unknown::KeyBind::handle(KeyPressEvent& evt) {
    if(evt.SDLCode == this->keycode) {
        this->currentState = evt.pressed;
    }
}

bool Unknown::KeyBind::pressed() const {
    return this->currentState;
}

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<KeyBind>("KeyBind")
            .constructor<int, const std::string>()
            .property("Keycode", &KeyBind::keycode)
            .property("CurrentState", &KeyBind::currentState)
            .property("Name", &KeyBind::name);
};
