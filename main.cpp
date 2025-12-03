#include <iostream>
#include <string>
using namespace std;
#include "queue.h"
#include "linkedlist.h"


bool validID(string id) {
    if (id.length() != 7) 
        return false;
    for (int i = 0; i < 7; i++) {
        if (id[i] < '0' || id[i] > '9') 
        return false;
    }
    return true;
}

float getDistance(string s, string e) 
    {
    if (s == "A" && e == "B") return 1.2f; // ระยะทางของ A -> B นะ 1.2 km
    if (s == "B" && e == "A") return 1.2f; // B -> A นะ 1.2 km
    if (s == "A" && e == "C") return 2.5f; // A -> C นะ 2.5 km
    if (s == "C" && e == "A") return 2.5f; // C -> A นะ 2.5 km
    if (s == "B" && e == "C") return 1.6f; // B -> C นะ 1.6 km
    if (s == "C" && e == "B") return 1.6f; // C -> A นะ 1.6 km

    return -1.0f; // สำหรับ not found เพราะปกติจะ ไม่ติดลบ

    }

int main() {
    Queue borrowed;
    LinkedList trips;

    int choice = -1;

    while (choice != 0) {
        cout << "\n===== MENU =====\n";
        cout << "1) Borrow bike" << endl;
        cout << "2) Return bike" << endl;
        cout << "3) Show borrowed bikes" << endl;
        cout << "4) Show trip history" << endl;
        cout << "0) Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string sid, name;
            int bikeID;

            cout << "Student ID (7 digits): ";
            cin >> sid;

            if (!validID(sid)) {
                cout << "Student ID must be 7 digits. Try agin!" << endl;
                continue;
            }

            cout << "Name: ";
            cin >> name;

            while (true) {
                cout << "BikeID (1-10): ";
                cin >> bikeID;

                if (bikeID < 1 || bikeID > 10) {
                    cout << "ERROR: BikeID must be 1-10. Try again." << endl;
                    continue;
                }

                if (borrowed.isBikeBorrowed(bikeID)) {
                    cout << "This bike is already borrowed. Choose new one.\n";
                    borrowed.showBorrowed();
                    continue;
                }

                borrowed.borrowBike(sid, name, bikeID);
                break;
            }
        }
        else if (choice == 2) {
            borrowed.showBorrowed();

            int bikeID;
            cout << "Enter BikeID to return: ";
            cin >> bikeID;

            string sid, name;
            bool ok = borrowed.returnBike(bikeID, sid, name);

            if (!ok) 
            {
                cout << "ERROR: This BikeID is not currently borrowed.\n";
                continue;
            }

            string start, end;
            cout << "Start station (A/B/C): ";
            cin >> start;
            cout << "End station (A/B/C): ";
            cin >> end;

            float dist = getDistance(start, end);
            if (dist < 0) {
                cout << "Distance not found. Enter distance (km): ";
                cin >> dist;
            }

            trips.addTrip(sid, name, start, end, dist);
        }
        else if (choice == 3) {
            borrowed.showBorrowed();
        }
        else if (choice == 4) {
            trips.showTrips();
        }
    }

    return 0;
}