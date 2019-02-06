//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_LOGVIEWER_H
#define PROJECT_LOGVIEWER_H

#include "ViewerBase.h"

class LogViewer : public ViewerBase<LogViewer> {
public:
    virtual void render();
};


#endif //PROJECT_LOGVIEWER_H
