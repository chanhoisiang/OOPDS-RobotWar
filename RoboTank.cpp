#include "RoboTank.h"
#include "UltimateRobot.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <iostream>
using namespace std;

RoboTank::RoboTank(string name, int x, int y) : Robot(name, x, y, 'K') {}

void RoboTank::look(){
    int positionX, positionY;
    for (int i = 0; i < 8; i++) {
        positionX = getX() + moveOpt[i][0];
        positionY = getY() + moveOpt[i][1];

        if (fieldptr->checkRobotisWithinRange(positionX, positionY)) {
            Robot* target = robotptr->check(positionX, positionY);
            if (target) {
                cout << "Position: (" << positionX << "," << positionY << ") contains robot " << target->getName() << endl;
        }
        }
        else
        {cout << "(" << positionX << "," << positionY << ") is out of bounds." << endl;
    }
    }
}

void RoboTank::fire() {
    int targetX, targetY;
        do {
            targetX = getX() + (rand() % fieldptr->getRows());
            targetY = getY() + (rand() % fieldptr->getCols());
        } while (!fieldptr->checkRobotisWithinRange(targetX, targetY) || (targetX == getX() && targetY == getY()));

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

        } else {
            cout << "Position: (" << targetX << "," << targetY << ") is empty. Attack Failed." << endl;
        }
}   

void RoboTank::action() {
    look();
    fire();
}

Robot* RoboTank::checkUpgrade() {
        if (kills >= 3) {
            return new UltimateRobot(name, getX(), getY());
        }
        return this;
    }

RoboTank::~RoboTank() {
}
