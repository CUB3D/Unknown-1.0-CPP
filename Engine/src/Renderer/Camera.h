//
// Created by cub3d on 16/07/2018.
//

#ifndef UNKNOWN_GAME_CAMERA_H
#define UNKNOWN_GAME_CAMERA_H

#include <Types/Direction.h>
#include <Types/Rect.h>

namespace Unknown
{
    class Camera
    {
    public:
        double speed = 1;
        Rect<double> area;

        Camera(int width, int height);
        void move(Direction d);
        void setPosition(double x, double y, double width, double height);

        virtual Rect<double> getBounds() const;
        virtual void render();
    };
}

#endif //UNKNOWN_GAME_CAMERA_H
