#pragma once
#include "Robot.h"

class Madbot : public ShootingRobot, public SeeingRobot {
public:
    Madbot(string name, int x, int y);

    void fire();
    void action();
    void look();

    virtual Robot* checkUpgrade();
    virtual ~Madbot();
};
