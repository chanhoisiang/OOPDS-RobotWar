#include "UltimateRobot.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <iostream>
using namespace std;

UltimateRobot::UltimateRobot(string name, int x, int y) : Robot(name, x, y, 'U') {}

UltimateRobot::~UltimateRobot() {
}

void UltimateRobot::look() {
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
            cout <<"(" << positionX << "," << positionY << ") is out of bounds." << endl;
        }
    }
}

void UltimateRobot::move() {
    
}

void UltimateRobot::step() {
    int newX, newY, random;
    bool found = false;

    // Attempt to find and attack nearby robots
    for (int i = 0; i < 8; i++) {
        newX = getX() + moveOpt[i][0];
        newY = getY() + moveOpt[i][1];

        if (fieldptr->checkRobotisWithinRange(newX, newY)) {
            Robot* target = robotptr->check(newX, newY);
            if (target) {
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
                found = true;
                setPosition(newX, newY);
                break; // Exit loop since a target is found and attacked
            }
        }
    }
}

void UltimateRobot::fire() {
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

void UltimateRobot::action() {
    look();
    step();
    fire();
    fire();
    fire();
    
}
