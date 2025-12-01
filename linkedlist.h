#include <iostream>
#include <string>
#include <iomanip>
#include "node.h"
using namespace std;

class LinkedList {
private:
    Node* head;
    const float RATE = 0.21f; // C02 rate
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
        float co2 = dist * RATE;

        Node* node = new Node(sid, name, start, end, dist, co2);

        node->setNext(head);
        head = node;

        cout << "Trip recorded!\n";
    }

    void showTrips() {
        if (head == nullptr) {
            cout << "No trip history.\n";
            return;
        }

        cout << fixed << setprecision(2);
        cout << "=== Trip History ===\n";

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

