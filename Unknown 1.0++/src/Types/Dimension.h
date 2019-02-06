//
// Created by cub3d on 15/11/18.
//

#ifndef UNKNOWN_DIMENSION_H
#define UNKNOWN_DIMENSION_H


namespace Unknown {
    template<class T>
    class Dimension {
    public:
        T width;
        T height;

        Dimension() : Dimension(T(), T()) {}

        Dimension(T t1, T t2) : width(t1), height(t2) {}
    };
}


#endif //UNKNOWN_DIMENSION_H
