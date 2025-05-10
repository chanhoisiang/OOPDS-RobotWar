#include "Madbot.h"
#include "RoboTank.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <iostream>
using namespace std;

Madbot::Madbot(string name, int x, int y) : Robot(name, x, y, 'M') {}

void Madbot::look()
{
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
        {
            cout << "(" << positionX << "," << positionY << ") is out of bounds." << endl;
        }
    }
}

void Madbot::fire() {
    int newX, newY, random;
    bool validPosition = false;
    while (!validPosition) {
        random = rand() % 8;
        newX = getX() + moveOpt[random][0];
        newY = getY() + moveOpt[random][1];
        if (fieldptr->checkRobotisWithinRange(newX, newY)) {
            Robot* target = robotptr->check(newX, newY);
            if (target) {
                //Step
                cout << "Position: (" << newX << "," << newY << ") has Robot " << target->getName() << ". Attack Successful." << endl;
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
                validPosition = true;
            } else
            {
                cout << "Position: (" << newX << "," << newY << ") is empty. Attack Failed." << endl;
                validPosition = true;
            }
        }
    }
}

void Madbot::action() {
    look();
    fire();
}

Robot* Madbot::checkUpgrade() {
        if (kills >= 3) {
            return new RoboTank(name, getX(), getY());
        }
        return this;
    }

Madbot::~Madbot() {
}