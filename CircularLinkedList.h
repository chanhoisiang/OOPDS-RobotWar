#pragma once
#include "Robot.h"

struct Node {
    Robot* robot;
    Node* next;

    Node(Robot* r);
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    Node* current;
    int size;

public:
    CircularLinkedList();

    ~CircularLinkedList();

    void add(Robot* robot);

    void remove(Robot* robot);

    Node* getNext();

    int getSize();

    bool isEmpty();

    Node* getHead();

    Robot* check(int x, int y) const;
};
