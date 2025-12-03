#include <iostream>
#include <string>
#include <iomanip>
#include "node.h"
#define CO2_RATE 0.21
using namespace std;


class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* t = head;
            head = head->getNext();
            delete t;
        }
    }

    void addTrip(string sid, string name, string start, string end, float dist) {
        float co2 = dist * CO2_RATE;
        Node* node = new Node(sid, name, start, end, dist, co2);

        if (head == nullptr || sid < head->getStudentID()) {
            node->setNext(head);
            head = node;
            cout << "Trip recorded!\n";
            return;
        }

        Node* cur = head;
        while (cur->getNext() != nullptr &&
               cur->getNext()->getStudentID() <= sid) {
            cur = cur->getNext();
        }

        node->setNext(cur->getNext());
        cur->setNext(node);

        cout << "Trip recorded!\n";
    }

    void showTrips() {
        if (head == nullptr) {
            cout << "No trip history.\n";
            return;
        }

        cout << fixed << setprecision(2);
        cout << "=== Trip History (Sorted by StudentID) ===\n";

        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->getStudentID() << " " << cur->getName()
                 << " | " << cur->getStart() << "->" << cur->getEnd()
                 << " | " << cur->getDistance() << " km"
                 << " | " << cur->getCO2() << " kg CO2\n";
            cur = cur->getNext();
        }
    }
};
