//
// Created by cub3d on 15/11/18.
//

#ifndef UNKNOWN_DIRECTION_H
#define UNKNOWN_DIRECTION_H


namespace Unknown {
    class Direction {
    public:
        int x, y;

        Direction(int x, int y) : x(x), y(y) {}

        Direction operator-() {
            return Direction(-x, -y);
        }
    };

    extern Direction up;
    extern Direction down;
    extern Direction left;
    extern Direction right;
}

#define UK_UP ::Unknown::Direction(0, 1)
#define UK_DOWN ::Unknown::Direction(0, -1)
#define UK_LEFT ::Unknown::Direction(1, 0)
#define UK_RIGHT ::Unknown::Direction(-1, 0)


#endif //UNKNOWN_DIRECTION_H
