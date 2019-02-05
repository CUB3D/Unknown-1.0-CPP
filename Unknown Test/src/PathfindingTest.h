//
// Created by cub3d on 28/11/18.
//

#ifndef PROJECT_PATHFINDINGTEST_H
#define PROJECT_PATHFINDINGTEST_H

#include <UK.h>

class PathfindingTest : public UK::Scene {
public:
    UK::Map m;

    PathfindingTest();

    virtual void render() const override;
    virtual void update() override;
};


#endif //PROJECT_PATHFINDINGTEST_H
