#pragma once
#include "Robot.h"
#include "Simulator.h"
#include <iostream>



class Battlefield {
private:
    int rows, cols; // M x N
    char** field;

public:
    Battlefield(int rows, int cols);
    ~Battlefield();

    int getRows() const;
    int getCols() const;

    bool checkRobotisWithinRange(int newX, int newY) const;
    bool occupied(int x, int y) const;
    void resetField();
    void placeRobot(Robot* robot);
    void display() const;
    char getSymbolAt(int x, int y) const;

};
