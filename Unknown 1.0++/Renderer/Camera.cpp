//
// Created by cub3d on 16/07/2018.
//

#include "Camera.h"

Unknown::Camera::Camera() = default;

Unknown::Rect<int> Unknown::Camera::getTileBounds() const {
    return tileArea;
}

void Unknown::Camera::setPosition(double x, double y, double width, double height) {
    this->area = Rect<double>(x, y, width, height);
    this->tileArea = Rect<int>(x / tileSize, y / tileSize, width / tileSize, height / tileSize);
}

void Unknown::Camera::move(Unknown::Direction d) {
    this->area.x += d.x * speed;
    this->area.y += d.y * speed;

    this->tileArea.x = this->area.x / tileSize;
    this->tileArea.y = this->area.y / tileSize;
}
