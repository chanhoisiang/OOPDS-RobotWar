#pragma once
#include "Robot.h"

class TerminatorRoboCop : public SeeingRobot, public MovingRobot, public SteppingRobot, public ShootingRobot {
public:
    TerminatorRoboCop(string name, int x, int y);

    void look();
    void move();
    void step();
    void fire();
    void action();

    virtual Robot* checkUpgrade();
    virtual ~TerminatorRoboCop();
};
