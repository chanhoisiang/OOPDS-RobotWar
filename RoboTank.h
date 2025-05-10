#pragma once
#include "Robot.h"

class RoboTank : public ShootingRobot, public SeeingRobot {
public:
    RoboTank(string name, int x, int y);

    void look();
    void fire();
    void action();

    virtual Robot* checkUpgrade();
    virtual ~RoboTank();
};
