#include <iostream>
#include <string>
using namespace std;

const int MAX_BIKES = 10;

struct BorrowNode {
    string studentID;
    string name;
    int bikeID;
    BorrowNode* next;

    BorrowNode(string sid, string n, int bid) {
        studentID = sid;
        name = n;
        bikeID = bid;
        next = nullptr;
    }
};

class Queue {
private:
    BorrowNode* head;

public:
    Queue() {
        head = nullptr;
    }

    ~Queue() {
        while (head != nullptr) {
            BorrowNode* t = head;
            head = head->next;
            delete t;
        }
    }

    bool isBikeBorrowed(int bikeID) {
        BorrowNode* cur = head;
        while (cur != nullptr) {
            if (cur->bikeID == bikeID) return true;
            cur = cur->next;
        }
        return false;
    }

    void borrowBike(string sid, string name, int bikeID) {
        if (bikeID < 1 || bikeID > MAX_BIKES) 
        {
            cout << "ERROR: BikeID must be 1-" << MAX_BIKES << "\n";
            return;
        }

        if (isBikeBorrowed(bikeID)) {
            cout << "ERROR: Bike " << bikeID << " is already borrowed.\n";
            return;
        }

        BorrowNode* node = new BorrowNode(sid, name, bikeID);

        // insert at front (easy)
        node->next = head;
        head = node;

        cout << "Borrow success!\n";
    }

    // คืนด้วย BikeID เท่านั้นนะ
    bool returnBike(int bikeID, string &sidOut, string &nameOut) {
        BorrowNode* cur = head;
        BorrowNode* prev = nullptr;

        while (cur != nullptr) {
            if (cur->bikeID == bikeID) {
                sidOut = cur->studentID;
                nameOut = cur->name;

                if (prev == nullptr) head = cur->next;
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
        if (head == nullptr) {
            cout << "No bikes are borrowed now.\n";
            return;
        }

        cout << "=== Borrowed Bikes ===\n";
        BorrowNode* cur = head;
        while (cur != nullptr) {
            cout << "BikeID: " << cur->bikeID
                 << " | " << cur->studentID << " " << cur->name << "\n";
            cur = cur->next;
        }
    }
};