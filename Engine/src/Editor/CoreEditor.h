//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_COREEDITOR_H
#define PROJECT_COREEDITOR_H

#include <Singleton.h>

class CoreEditor : public Singleton<CoreEditor> {
    friend class Singleton<CoreEditor>;

    CoreEditor() = default;
public:

    virtual void render();
    virtual void update();
};


#endif //PROJECT_COREEDITOR_H
