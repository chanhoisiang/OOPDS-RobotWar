#pragma once
#include "Robot.h"
#include "Battlefield.h"
#include "CircularLinkedList.h"
#include "QueueList.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

class Simulator {
private:
    Battlefield* battlefield;
    CircularLinkedList* robots;
    QueueList* waitingRobots;
    int robotCount;
    int queueCount;
    int steps;
    ofstream runFile;
    void logToConsole(const std::string& message);
    void logToFile(const std::string& message);
    void logRobotActions(Robot* robot, const std::string& action);

public:
    Simulator(int rows, int cols, int steps);

    ~Simulator();

    void addRobot(Robot* robot);

    void reentryQueue(Robot* robot);

    void removeRobot(Robot* robot);

    void reenterRobots();

    void simulate();

    void record(const string& message);

    void recordBattlefield();
};
