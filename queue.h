#include <iostream>
#include <string>
using namespace std;

const int MAX_BIKES = 10;


class BorrowNode {
public:
    string studentID;
    string name;
    int bikeID;
    BorrowNode* next;

    BorrowNode(string sid, string n, int bid);
};

BorrowNode::BorrowNode(string sid, string n, int bid) {
    studentID = sid;
    name = n;
    bikeID = bid;
    next = nullptr;
}

class Queue {
private:
    BorrowNode* head;

public:
    Queue() : head(nullptr) {}

    ~Queue() {
        while (head) {
            BorrowNode* t = head;
            head = head->next;
            delete t;
        }
    }

    bool isBikeBorrowed(int bikeID) {
        for (BorrowNode* cur = head; cur; cur = cur->next)
            if (cur->bikeID == bikeID) return true;
        return false;
    }

    void borrowBike(string sid, string name, int bikeID) {
        if (bikeID < 1 || bikeID > MAX_BIKES) { 
            cout << "ERROR: BikeID 1-10\n"; return; 
        }
        if (isBikeBorrowed(bikeID)) { 
            cout << "ERROR: Bike already borrowed.\n"; return; 
        }

        BorrowNode* node = new BorrowNode(sid, name, bikeID);
        node->next = head;  
        head = node;
        cout << "Borrow success!\n";
    }

    bool returnBike(int bikeID, string &sidOut, string &nameOut) {
        BorrowNode* cur = head;
        BorrowNode* prev = nullptr;

        while (cur) {
            if (cur->bikeID == bikeID) {
                sidOut = cur->studentID;
                nameOut = cur->name;

                if (!prev) head = cur->next;
                else prev->next = cur->next;

                delete cur;
                cout << "Return success!\n";
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void showBorrowed() {
        if (!head) { cout << "No bikes are borrowed now.\n"; return; }
        cout << "=== Borrowed Bikes ===\n";
        for (BorrowNode* cur = head; cur; cur = cur->next)
            cout << "BikeID: " << cur->bikeID << " | " << cur->studentID << " " << cur->name << "\n";
    }
};


struct WaitNode {
    string studentID, name;
    WaitNode* next;
    WaitNode(string sid, string n) : studentID(sid), name(n), next(nullptr) {}
};


class WaitingQueue {
private:
    WaitNode* front;
    WaitNode* rear;

public:
    WaitingQueue() : front(nullptr), rear(nullptr) {}

    ~WaitingQueue() {
        while (front) {
            WaitNode* t = front;
            front = front->next;
            delete t;
        }
        rear = nullptr;
    }

    void enqueue(string sid, string name) {         
        WaitNode* node = new WaitNode(sid, name);
        if (!rear) front = rear = node;
        else { rear->next = node; rear = node; }
    }

    bool dequeue(string &sidOut, string &nameOut) { 
        if (!front) return false;
        WaitNode* t = front;
        sidOut = t->studentID; nameOut = t->name;
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
        return true;
    }

    void show() {
        if (!front) { 
            cout << "(no waiting)\n"; 
            return; 
        }
        for (WaitNode* cur = front; cur; cur = cur->next)
            cout << cur->studentID << " " << cur->name << "\n";
    }
};

