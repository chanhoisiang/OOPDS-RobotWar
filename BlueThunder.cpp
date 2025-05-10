#include "BlueThunder.h"
#include "Madbot.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <iostream>
using namespace std;

BlueThunder::BlueThunder(string name, int x, int y) : Robot(name, x, y, 'B') {}

void BlueThunder::fire() {
    int targetX, targetY;
    bool validPosition = false;
    while (!validPosition){
        targetX = getX() + moveOpt[getfireSequence()][0];
        targetY = getY() + moveOpt[getfireSequence()][1];
        if(fieldptr->checkRobotisWithinRange(targetX, targetY)){
            validPosition = true;}
        else{
            {cout << name << " cannot fire to (" << targetX << "," << targetY << ") because it is out of bounds." <<endl;}
            setfireSequence();
        }
    }

    Robot* target = robotptr->check(targetX, targetY);
    if (target) {
        cout << "Position: (" << targetX << "," << targetY << ") has Robot " << target->getName() << ". Attack Successful." << endl;
        target->reduceLife();
        cout << target->getName() << "Lives: " << target->getLives() << endl;
        if (target->getLives() > 0) {
            simulatorptr->reentryQueue(target);
            simulatorptr->removeRobot(target);
        } else {
            simulatorptr->removeRobot(target);
        }
        incrementKills();
        cout << getName() << "Kills: " << getKills() << endl;

    } 
    else {
        cout << "Position: (" << targetX << "," << targetY << ") is empty. Attack Failed." << endl;
        }
    setfireSequence();
    
}

void BlueThunder::action() {

    fire();
}

Robot* BlueThunder::checkUpgrade() {
        if (kills >= 3) {
            return new Madbot(name, getX(), getY());
        }
        return this;
    }

BlueThunder::~BlueThunder() {
}
