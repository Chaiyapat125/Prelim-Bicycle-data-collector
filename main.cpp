#include <iostream>
#include <string>
#include "linkedlist.h"

using namespace std;

int main() {
    LL bikeList;
    int choice;

    while (true) {
        cout << "\n===== Bicycle Data Collector =====\n";
        cout << "1. Add new bicycle rental\n";
        cout << "2. Show all rentals\n";
        cout << "3. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        if (!cin) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 1) {
            string name, start, end;
            float dist;

            cout << "Student name: ";
            cin >> ws;               
            getline(cin, name);

            cout << "Start station: ";
            getline(cin, start);

            cout << "End station: ";
            getline(cin, end);

            cout << "Distance (km): ";
            cin >> dist;

            bikeList.insert_node(name, start, end, dist);
            cout << "✅ Rental added!\n";
        }
        else if (choice == 2) {
            cout << "\nCurrent rental list:\n";
            bikeList.printList();
        }
        else if (choice == 3) {
            cout << "Bye!\n";
            break;
        }
        else {
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
