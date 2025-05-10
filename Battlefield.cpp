#include "Battlefield.h"

Battlefield::Battlefield(int rows, int cols) : rows(rows), cols(cols) {
    field = new char*[cols];
    for (int i = 0; i < cols; ++i) {
        field[i] = new char[rows];
        for (int j = 0; j < rows; ++j) {
            field[i][j] = '-';
        }
    }
}

Battlefield::~Battlefield() {
    for (int i = 0; i < cols; ++i) {
        delete[] field[i];
    }
    delete[] field;
}

char Battlefield::getSymbolAt(int x, int y) const {
    return field[x][y];
}

int Battlefield::getRows() const {
    return rows;
}

int Battlefield::getCols() const {
    return cols;
}

bool Battlefield::checkRobotisWithinRange(int newX, int newY) const {
    return newX >= 0 && newX < rows && newY >= 0 && newY < cols;
}

bool Battlefield::occupied(int x, int y) const {
    return field[x][y] != '-';
}

void Battlefield::resetField() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j] = '-';
        }
    }
}

void Battlefield::placeRobot(Robot* robot) {
    int x = robot->getX();
    int y = robot->getY();
    field[x][y] = robot->getSymbol();
}

void Battlefield::display() const {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}
