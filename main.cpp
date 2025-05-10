#include "SimulationReader.h"
#include "Simulator.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "RoboTank.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "UltimateRobot.h"
#include <iostream>
using namespace std;

int main() {
    srand(int(time(0))); // Seed the random number generator

    SimulationReader configReader("mainfile.txt");

    if (!configReader.readConfigFile()) {
        cerr << "Error reading configuration file!" << endl;
        return 1;
    }

    int rows = configReader.getRows();
    int cols = configReader.getCols();
    int steps = configReader.getSteps();
    int robotCount = configReader.getRobotCount();
    
    Simulator simulator(rows, cols, steps);


    //std::cout << "Rows: " << rows << ", Cols: " << cols << ", Steps: " << steps << ", Robot Count: " << robotCount << std::endl;

    // Access robot data
    for (int i = 0; i < robotCount; ++i) {
        string type = configReader.getRobotType(i);
        string name = configReader.getRobotName(i);
        int x = configReader.getRobotXPosition(i);
        int y = configReader.getRobotYPosition(i);
        if (type == "RoboCop")
        { simulator.addRobot(new RoboCop(name, x, y));}
        else if (type == "Terminator")
        {simulator.addRobot(new Terminator(name, x, y));}
        else if (type == "TerminatorRoboCop")
        {simulator.addRobot(new TerminatorRoboCop(name, x, y));}
        else if (type == "BlueThunder")
        {simulator.addRobot(new BlueThunder(name, x, y));}
        else if (type == "Madbot")
        {simulator.addRobot(new Madbot(name, x, y));}
        else if (type == "RoboTank")
        {simulator.addRobot(new RoboTank(name, x, y));}
        else if (type == "UltimateRobot")
        {simulator.addRobot(new UltimateRobot(name, x, y));}
        
    }

    simulator.simulate();
    return 0;
}
