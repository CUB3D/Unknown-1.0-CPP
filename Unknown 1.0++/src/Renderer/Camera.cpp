//
// Created by cub3d on 16/07/2018.
//

#include "Camera.h"

void Unknown::Camera::setPosition(double x, double y, double width, double height) {
    this->area = Rect<double>(x, y, width, height);
}

void Unknown::Camera::move(Unknown::Direction d) {
    this->area.x += d.x * speed;
    this->area.y += d.y * speed;
}

Unknown::Rect<double> Unknown::Camera::getBounds() const {
    return this->area;
}

Unknown::Camera::Camera(int width, int height) {
    this->setPosition(0, 0, width, height);
}

void Unknown::Camera::render() {
}
