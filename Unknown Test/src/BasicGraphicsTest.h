//
// Created by cub3d on 03/12/18.
//

#ifndef PROJECT_BASICGRAPHICSTEST_H
#define PROJECT_BASICGRAPHICSTEST_H

#include <UK.h>

class BasicGraphicsTest : public UK::Scene {
public:
    UK::Map map;
    UK::Timer timer;

    BasicGraphicsTest();

    virtual void render() const override;
    virtual void update() override;

    void createBoard();
    int checkTile(int x, int y, UK::Map& map);
};


#endif //PROJECT_BASICGRAPHICSTEST_H
