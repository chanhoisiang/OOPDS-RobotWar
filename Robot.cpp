#include "Robot.h"

Robot::Robot(string name, int x, int y, char symbol)
    : name(name), x(x), y(y), symbol(symbol), kills(0), lives(3), fireSequence(0),
      fieldptr(nullptr), robotptr(nullptr), queueptr(nullptr), simulatorptr(nullptr) {}

Robot::~Robot() {}

void Robot::connection(Battlefield* ptr) { fieldptr = ptr; }
void Robot::connection(CircularLinkedList* ptr) { robotptr = ptr; }
void Robot::connection(QueueList* queue) { queueptr = queue; }
void Robot::setSimulator(Simulator* ptr) { simulatorptr = ptr; }

bool Robot::isAlive() const { return lives > 0; }

void Robot::reduceLife() {
    lives--;
    if (lives <= 0) {
        alive = false;
    }
}

int Robot::getKills() const { return kills; }
void Robot::setLives(int lives) {
    this->lives = lives;
}



void Robot::incrementKills() { kills++; }

void Robot::revive() {
    if (alive && lives > 0) {
        alive = true;
    }
}

void Robot::setfireSequence() {fireSequence = (fireSequence + 1) % 8;}

int Robot::getfireSequence() const {return fireSequence; }


int Robot::getX() const { return x; }

int Robot::getY() const { return y; }

char Robot::getSymbol() const { return symbol; }

int Robot::getLives() const { return lives; }

string Robot::getName() const { return name; }

void Robot::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

Robot* Robot::checkUpgrade() {
   return this;
}
