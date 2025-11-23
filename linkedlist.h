#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include "node.h"
using namespace std;

typedef Node* nodePtr;

class LL {

private:
    nodePtr hol;
    int size;

public:
    LL();
    void insert_node(string, string, string, float);
    void printList();
    ~LL();
};


LL::LL() {
    hol = nullptr;
    size = 0;
}

void LL::insert_node(string name, string start, string end, float dist) {


    float co2 = dist * 0.21f;

    if (hol == nullptr) {
        hol = new Node(name, start, end, dist, co2);
    }
    else {
        nodePtr t = hol;
        while (t->getNext() != nullptr) {
            t = t->getNext();
        }
        t->setNext(new Node(name, start, end, dist, co2));
    }
    size++;
}

void LL::printList() {
    nodePtr t = hol;

    if (t == nullptr) {
        cout << "Empty List" << endl;
        return;
    }

    while (t != nullptr) {
        cout << "[" << t->getStudentName()
             << " | " << t->getStartStation()
             << " -> " << t->getEndStation()
             << " | " << t->getDistance() << " km"
             << " | " << t->getCO2saved() << " kg CO2]";
        t = t->getNext();
    }
}

LL::~LL() {
    nodePtr current = hol;
    while (current != nullptr) {
        nodePtr next = current->getNext();
        delete current;
        current = next;
    }
    hol = nullptr;
    size = 0;
}

#endif
