#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class SimulationReader {
private:
    std::string filename;
    int rows;
    int cols;
    int steps;
    int robotCount;
    // Arrays to store robot data
    string* robotTypes;
    string* robotNames;
    int* robotXPositions;
    int* robotYPositions;

public:
    SimulationReader(const string& filename);
    ~SimulationReader();

    bool readConfigFile();

    int getRows() const;
    int getCols() const;
    int getSteps() const;
    int getRobotCount() const;

    string getRobotType(int index) const;
    string getRobotName(int index) const;
    int getRobotXPosition(int index) const;
    int getRobotYPosition(int index) const;
};

