#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "Simulator.h"
#include <iostream>
using namespace std;

Terminator::Terminator(string name, int x, int y) : Robot(name, x, y, 'T') {}

Terminator::~Terminator() {
}

void Terminator::look() {
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


void Terminator::move() {
    
}

void Terminator::step() {
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

    // If no target found in immediate vicinity, move randomly within bounds
    if (!found) {
        do {
            random = rand() % 8;
            newX = getX() + moveOpt[random][0];
            newY = getY() + moveOpt[random][1];
        } while (!fieldptr->checkRobotisWithinRange(newX, newY));

        cout << name << " moves to (" << newX << "," << newY << ")" << endl;
        setPosition(newX, newY);
    }
}


void Terminator::action() {
    look();
    step();
}

Robot* Terminator::checkUpgrade() {
        if (kills >= 3) {
            return new TerminatorRoboCop(name, getX(), getY());
        }
        return this;
    }
