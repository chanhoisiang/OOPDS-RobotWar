#pragma once
#include "Robot.h"

class UltimateRobot : public SeeingRobot, public MovingRobot, public SteppingRobot, public ShootingRobot {
public:
    UltimateRobot(string name, int x, int y);

    void look();
    void move();
    void step();
    void fire();
    void action();

    virtual ~UltimateRobot();

};
