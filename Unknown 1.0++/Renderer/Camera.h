//
// Created by cub3d on 16/07/2018.
//

#ifndef UNKNOWN_GAME_CAMERA_H
#define UNKNOWN_GAME_CAMERA_H

#include "../Map.h"
#include "../Utils.h"

namespace Unknown
{
    class Camera
    {
        Rect<int> tileArea;
        Rect<double> area;
        double speed = 1;
        int tileSize = 1;

    public:
        Camera();
        void move(Direction d);
        void setPosition(double x, double y, double width, double height);

        virtual Rect<int> getTileBounds() const;
    };
}

#endif //UNKNOWN_GAME_CAMERA_H
