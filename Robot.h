#pragma once
#include <string>
//#include "Battlefield.h"
//#include "CircularLinkedList.h"
//#include "QueueList.h"
//#include "Simulator.h"

using namespace std;

class Battlefield;
class CircularLinkedList;
class QueueList;
class Simulator;

class Robot {
private:
    int x, y; // Position on the battlefield

protected:
    string name;
    int lives;
    char symbol;
    int kills;
    bool alive;
    int fireSequence;
    const int moveOpt[8][2] = {
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}
    };
    Battlefield* fieldptr;
    CircularLinkedList* robotptr;
    QueueList* queueptr;
    Simulator* simulatorptr;

public:
    Robot() = default;
    Robot(string name, int x, int y, char symbol);

    virtual ~Robot();

    virtual void action() = 0;

    void connection(Battlefield* ptr);
    void connection(CircularLinkedList* ptr);
    void connection(QueueList* queue);
    void setSimulator(Simulator* ptr);

    int getfireSequence() const;
    void setfireSequence();
    bool isAlive() const;
    void reduceLife();
    int getKills() const;
    void setLives(int lives);
    void incrementKills();
    void revive();
    int getX() const;
    int getY() const;
    char getSymbol() const;
    int getLives() const;
    string getName() const;
    void setPosition(int newX, int newY);
    virtual Robot* checkUpgrade();
};

class MovingRobot : virtual public Robot {
public:
    virtual void move() = 0;
};

class ShootingRobot : virtual public Robot {
public:
    virtual void fire() = 0;
};

class SeeingRobot : virtual public Robot {
public:
    virtual void look() = 0;
};

class SteppingRobot : virtual public Robot {
public:
    virtual void step() = 0;
};
