#include "Simulator.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "RoboTank.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "UltimateRobot.h"
#include "SimulationReader.h"
#include <iostream>
#include <fstream>
using namespace std;

Simulator::Simulator(int rows, int cols, int steps) : steps(steps) {
    srand(time(0));
    battlefield = new Battlefield(rows, cols);
    robots = new CircularLinkedList();
    waitingRobots = new QueueList();

    runFile.open("data.txt");
    if (!runFile.is_open())
    {cerr << "Error opening log file!" << endl;}
}

Simulator::~Simulator() {
    delete battlefield;
    delete robots;
    delete waitingRobots;
    if (runFile.is_open()) {
        runFile.close();
    }
}

void Simulator::record(const string& message) {
    // Log action to file
    if (runFile.is_open()) {
        runFile << message << endl;
    }
}

void Simulator::addRobot(Robot* robot) {
    robot->connection(battlefield);
    robot->connection(robots);
    robot->connection(waitingRobots);
    robot->setSimulator(this);
    robots->add(robot);
}

void Simulator::reentryQueue(Robot* robot) {
    waitingRobots->enqueue(robot);
}

void Simulator::removeRobot(Robot* robot) {
    robots->remove(robot);
}

void Simulator::reenterRobots() {
    bool validPosition = false;
    if (!(waitingRobots->isEmpty())){
        while (!validPosition){
            int positionX = rand() % battlefield->getRows();
            int positionY = rand() % battlefield->getCols();
            cout << positionX << " "<<positionY << endl;
            Robot* target = robots->check(positionX, positionY);
            if (target!= nullptr) {
                validPosition = false;
            } else {
                Robot* robot = waitingRobots->dequeue();
                robot->setPosition(positionX, positionY);
                cout << robot->getName() << " is added to " << positionX << "," << positionY << endl;
                addRobot(robot);
                battlefield->placeRobot(robot);
                validPosition = true;
            }
        
        }
    }
}

void Simulator::simulate() {

    Node* temp1 = robots->getHead();
        do {
            if (temp1->robot->isAlive()) {
                battlefield->placeRobot(temp1->robot);
            }
            temp1 = temp1->next;
        } while (temp1 != robots->getHead());
    cout << "The initial battlefield: " << endl;
    battlefield->display();

    Node* current = robots->getHead();
    for (int step = 0; step < steps; ++step) {
        reenterRobots();

        battlefield->resetField();

        cout << "Now is " << current->robot->getName() << " turns" << endl;

        if (current->robot->isAlive()) {
            current->robot->action();
            Robot* upgradedRobot = current->robot->checkUpgrade();
            if (upgradedRobot != current->robot) {
                cout << current->robot->getName() << "upgrade successfully" << endl;
        
                upgradedRobot->setLives(current->robot->getLives());
                upgradedRobot->setPosition(current->robot->getX(), current->robot->getY());

                removeRobot(current->robot);
                addRobot(upgradedRobot);
            } else {
                battlefield->placeRobot(current->robot);
            }

        }

        Node* temp = robots->getHead();
        do {
            if (temp->robot->isAlive()) {
                battlefield->placeRobot(temp->robot);
            }
            temp = temp->next;
        } while (temp != robots->getHead());

        battlefield->display();
        current = current->next;
        

        cout << "Step " << step + 1 << " completed." << endl << endl;
    }
}
