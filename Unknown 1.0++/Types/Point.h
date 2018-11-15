//
// Created by cub3d on 15/11/18.
//

#ifndef UNKNOWN_POINT_H
#define UNKNOWN_POINT_H

namespace Unknown {
    template<typename T>
    class Point {
    public:
        T x;
        T y;

        Point() : Point(T(), T()) {}

        Point(T t1, T t2) {
            this->x = t1;
            this->y = t2;
        }
    };
}


#endif //UNKNOWN_POINT_H
