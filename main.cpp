#include <iostream>
#include <string>
using namespace std;
#include "queue.h"
#include "linkedlist.h"

bool validID(string id) {
    if (id.length() != 7) return false;
    for (char c : id) if (c < '0' || c > '9') return false;
    return true;
}

float getDistance(string s, string e) {
    if (s == "A" && e == "B") return 1.2f; // ระยะทางของ A -> B นะ 1.2 km
    if (s == "B" && e == "A") return 1.2f; // B -> A นะ 1.2 km
    if (s == "A" && e == "C") return 2.5f; // A -> C นะ 2.5 km
    if (s == "C" && e == "A") return 2.5f; // C -> A นะ 2.5 km
    if (s == "B" && e == "C") return 1.6f; // B -> C นะ 1.6 km
    if (s == "C" && e == "B") return 1.6f; // C -> A นะ 1.6 km

    return -1.0f; // สำหรับ not found เพราะปกติจะ ไม่ติดลบ
}

void doBorrow(Queue &borrowed, WaitingQueue &waiting) {
    string sid, name;
    int bikeID;

    cout << "Student ID (7 digits): ";
    cin >> sid;
    if (!validID(sid)) {
        cout << "Invalid ID!\n";
        return;
    }

    cout << "Name: ";
    cin >> name;

    cout << "BikeID (1-10): ";
    cin >> bikeID;
    if (bikeID < 1 || bikeID > 10) {
        cout << "ERROR: BikeID must be 1-10.\n";
        return;
    }

    if (borrowed.isBikeBorrowed(bikeID)) {
        char ans;
        cout << "This bike is already borrowed.\n";
        cout << "Join waiting queue? (y/n): ";
        cin >> ans;

        if (ans == 'y' || ans == 'Y') {
            waiting.enqueue(sid, name);   // FIFO enqueue
            cout << "Added to waiting queue.\n";
        }
        return;
    }

    borrowed.borrowBike(sid, name, bikeID);
}

void doReturn(Queue &borrowed, LinkedList &trips, WaitingQueue &waiting) {
    int bikeID;
    borrowed.showBorrowed();
    cout << "Enter BikeID to return: ";
    cin >> bikeID;

    string sid, name;
    if (!borrowed.returnBike(bikeID, sid, name)) {
        cout << "ERROR: This BikeID is not currently borrowed.\n";
        return;
    }

    string start, end;
    cout << "Start station (A/B/C): ";
    cin >> start;
    cout << "End station (A/B/C): ";
    cin >> end;

    float dist = getDistance(start, end);
    if (dist < 0) {
        cout << "Distance not found. E1nter distance (km): ";
        cin >> dist;
    }

    trips.addTrip(sid, name, start, end, dist);
    string nextSid, nextName;
    if (waiting.dequeue(nextSid, nextName)) {
        borrowed.borrowBike(nextSid, nextName, bikeID);
        cout << "Next waiting student got Bike " << bikeID << ":\n";
        cout << nextSid << " " << nextName << "\n";
    }
}

int main() {
    Queue borrowed;
    LinkedList trips;
    WaitingQueue waiting;

    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1) Borrow bike\n";
        cout << "2) Return bike\n";
        cout << "3) Show borrowed bikes\n";
        cout << "4) Show trip history\n";
        cout << "5) Show waiting queue\n";
        cout << "0) Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) doBorrow(borrowed, waiting);
        else if (choice == 2) doReturn(borrowed, trips, waiting);
        else if (choice == 3) borrowed.showBorrowed();
        else if (choice == 4) trips.showTrips();
        else if (choice == 5) waiting.show();

    } while (choice != 0);

    return 0;
}
