#include "RoboCop.h"
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

RoboCop::RoboCop(string name, int x, int y) : Robot(name, x, y, 'R') {}

RoboCop::~RoboCop() {
}

void RoboCop::look() {
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
        else{
        cout << "(" << positionX << "," << positionY << ") is out of bounds." << endl;
}   }
}

void RoboCop::move() {
    cout << name << " from " << getX() << "," << getY();
    int newX, newY, random;
    bool validPosition = false;
    while (!validPosition) {
        random = rand() % 8;
        newX = getX() + moveOpt[random][0];
        newY = getY() + moveOpt[random][1];
        if (fieldptr->checkRobotisWithinRange(newX, newY)) {
            Robot* target = robotptr->check(newX, newY);
            if (target) {
                validPosition = false;
            } else {
                validPosition = true;
            }
        }
    }
    setPosition(newX, newY);
    cout << " moved to (" << newX << "," << newY << ").\n";
}

void RoboCop::fire() {
        int targetX, targetY, sum;
        do {
            targetX = (rand() % 5);
            targetY = (rand() % 5);
            sum = targetX + targetY;
            cout << targetX <<  targetY << sum <<endl;
        } while (!fieldptr->checkRobotisWithinRange(targetX, targetY) || (targetX == getX() && targetY == getY()) || (sum >= 10));

        cout << targetX << " " << targetY;
        Robot* target = robotptr->check(targetX, targetY);
        if (target != nullptr) {
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

void RoboCop::action() {
    //cout << "Executing action for " << name << endl;

    look();
    move();
    fire();
    fire();
    fire();

}


Robot* RoboCop::checkUpgrade() {
        if (kills >= 3) {
            return new TerminatorRoboCop(name, getX(), getY());
        }
        return this;
    }