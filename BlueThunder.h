#pragma once
#include "Robot.h"

class BlueThunder : public ShootingRobot  {
public:
    BlueThunder(string name, int x, int y);
    

    void fire();
    void action();

    virtual Robot* checkUpgrade();
    virtual ~BlueThunder();
};
