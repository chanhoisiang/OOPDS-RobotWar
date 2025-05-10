#pragma once
#include "Robot.h"

struct QueueNode {
    Robot* robot;
    QueueNode* next;

    QueueNode(Robot* robot);
};

class QueueList {
private:
    QueueNode* front;
    QueueNode* back;

public:
    QueueList();

    ~QueueList();

    bool isEmpty() const;

    void enqueue(Robot* robot);

    Robot* dequeue();

    Robot* peek() const;

    QueueNode* getFront() const;
};
