#pragma once
#include "Robot.h"

class Terminator : public MovingRobot, public SteppingRobot, public SeeingRobot {
public:
    Terminator(string name, int x, int y);

    void look();
    void move();
    void step();
    void action();
    virtual Robot* checkUpgrade();
    virtual ~Terminator();


};
