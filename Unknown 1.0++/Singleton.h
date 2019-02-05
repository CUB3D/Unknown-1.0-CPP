//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_SINGLETON_H
#define PROJECT_SINGLETON_H

template<class T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
};

#endif //PROJECT_SINGLETON_H
