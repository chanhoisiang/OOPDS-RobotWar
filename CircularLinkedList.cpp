#include "CircularLinkedList.h"

Node::Node(Robot* r) : robot(r), next(nullptr) {}

CircularLinkedList::CircularLinkedList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

CircularLinkedList::~CircularLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
        if (current == head) {
            break;
        }
    }
    head = nullptr;
    tail = nullptr;
}

void CircularLinkedList::add(Robot* robot) {
    Node* newNode = new Node(robot);
    if (!head) {
        head = newNode;
        tail = newNode;
        tail->next = head;
    } else {
        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    }
    size++;
}

void CircularLinkedList::remove(Robot* robot) {
    if (head == nullptr || robot == nullptr) return;

    Node* current = head;
    Node* previous = nullptr;

    while (current->robot != robot) {
        previous = current;
        current = current->next;
    }

    if (current == head) {
        head = current->next;
        tail->next = head;
    } else if (current == tail) {
        previous->next = head;
        tail = previous;
    } else {
        previous->next = current->next;
    }

    delete current;
    size--;
}

Node* CircularLinkedList::getNext() {
    if (!current) {
        current = head;
    } else {
        current = current->next;
    }

    return current;
}

int CircularLinkedList::getSize() {
    return size;
}

bool CircularLinkedList::isEmpty() {
    return size == 0;
}

Node* CircularLinkedList::getHead() {
    return head;
}

Robot* CircularLinkedList::check(int x, int y) const {
    if (head == nullptr) {
        return nullptr;
    }

    Node* current = head;

    do {
        if (current->robot->getX() == x && current->robot->getY() == y) {
            return current->robot;
        }
        current = current->next;
    } while (current != head);

    return nullptr;
}
