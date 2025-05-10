#include "SimulationReader.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;

SimulationReader::SimulationReader(const std::string& filename)
    : filename(filename), rows(0), cols(0), steps(0), robotCount(0),
      robotTypes(nullptr), robotNames(nullptr),
      robotXPositions(nullptr), robotYPositions(nullptr) {}

SimulationReader::~SimulationReader() {
    // Deallocate memory for arrays
    delete[] robotTypes;
    delete[] robotNames;
    delete[] robotXPositions;
    delete[] robotYPositions;
}

bool SimulationReader::readConfigFile() {
    ifstream configFile(filename);
    if (!configFile.is_open()) {
        cerr << "Error: Failed to open configuration file " << filename << std::endl;
        return false;
    }

    // Read dimensions, steps, and robot count
    string line;
    int robotIndex = 0;
    while (getline(configFile, line)) {
        istringstream iss(line);
        string key;
        if (iss >> key) {
            if (key == "M") {
                iss >> key >> key >> key;
                iss >> rows >> cols;
            } else if (key == "steps:") {
                iss >> steps;
            } else if (key == "robots:") {
                iss >> robotCount;
                // Allocate memory for arrays based on robot count
                robotTypes = new string[robotCount];
                robotNames = new string[robotCount];
                robotXPositions = new int[robotCount];
                robotYPositions = new int[robotCount];
            } else {
                if (robotIndex < robotCount)
                {
                    string type, name;
                    string temp1, temp2;
                    int x, y;
                    type = key;
                    iss >> name >> temp1 >> temp2;
                    if (temp1 == "random" || temp2 == "random")
                    {
                        x = rand() % rows;
                        y = rand() % cols; 
                    }
                    else
                    {
                        x = stoi(temp1);
                        y = stoi(temp2);
                    }

                    // Store robot data in arrays
                    robotTypes[robotIndex] = type;
                    robotNames[robotIndex] = name;
                    robotXPositions[robotIndex] = x;
                    robotYPositions[robotIndex] = y;
                    robotIndex++;
                }
            }
        }
    }

    configFile.close();
    return true;
}

int SimulationReader::getRows() const { return rows; }
int SimulationReader::getCols() const { return cols; }
int SimulationReader::getSteps() const { return steps; }
int SimulationReader::getRobotCount() const { return robotCount; }

std::string SimulationReader::getRobotType(int index) const { return robotTypes[index]; }
std::string SimulationReader::getRobotName(int index) const { return robotNames[index]; }
int SimulationReader::getRobotXPosition(int index) const { return robotXPositions[index]; }
int SimulationReader::getRobotYPosition(int index) const { return robotYPositions[index]; }
