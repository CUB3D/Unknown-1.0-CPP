//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_VIEWERBASE_H
#define PROJECT_VIEWERBASE_H

#include <Singleton.h>
#include <Imgui/imgui.h>

template<class T>
class ViewerBase : public Singleton<T> {
public:
    bool enabled;

    virtual void render() {

    }

    virtual void update() {

    }
};


#endif //PROJECT_VIEWERBASE_H
