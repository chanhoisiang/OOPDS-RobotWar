#pragma once
#include "Robot.h"

class RoboCop : public MovingRobot, public ShootingRobot, public SeeingRobot {

public:
    RoboCop(string name, int x, int y);

    void look();
    void move();
    void fire();
    void action();
    virtual Robot* checkUpgrade();

    virtual ~RoboCop();


};
