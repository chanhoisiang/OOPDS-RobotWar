#include "QueueList.h"

QueueNode::QueueNode(Robot* robot) : robot(robot), next(nullptr) {}

QueueList::QueueList() : front(nullptr), back(nullptr) {}

QueueList::~QueueList() {
    while (front != nullptr) {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
    back = nullptr;
}

bool QueueList::isEmpty() const {
    return front == nullptr;
}

void QueueList::enqueue(Robot* robot) {
    QueueNode* newNode = new QueueNode(robot);
    if (isEmpty()) {
        front = back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
}

Robot* QueueList::dequeue() {
    if (isEmpty()) {
        return nullptr;
    }
    QueueNode* temp = front;
    front = front->next;
    Robot* robot = temp->robot;
    delete temp;
    return robot;
}

Robot* QueueList::peek() const {
    if (isEmpty()) {
        return nullptr;
    }
    return front->robot;
}

QueueNode* QueueList::getFront() const
{ return front;}

