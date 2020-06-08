//
// Created by cub3d on 15/11/18.
//

#ifndef UNKNOWN_RECT_H
#define UNKNOWN_RECT_H

#include <glm/glm.hpp>

namespace Unknown {
    template<typename T>
    class Rect {
    public:
        T x, y, w, h;
        Rect() : Rect(0, 0, 0, 0) {}
        Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

        Rect<int> operator *(int value) {
            return Rect<int>(x * value, y * value, w * value, h * value);
        }

        Rect<int> operator /(int value) {
            return Rect<int>(x / value, y / value, w / value, h / value);
        }

        template<typename R>
        bool contains(Rect<R> other) {
            return !(other.x + other.w < x || other.x > x + w || other.y + other.h < y || other.y > y + h);
        }

        glm::vec2 center() {
            return glm::vec2(x + w / 2.0, y + h / 2.0);
        }

        bool contains(glm::vec2 t) {
            bool X = t.x > x && t.x < x + w;
            bool Y = t.y > y && t.y < y + h;

            return X && Y;
        }

    };
}


#endif //UNKNOWN_RECT_H
