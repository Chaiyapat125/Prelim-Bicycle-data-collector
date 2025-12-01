#include <string>
using namespace std;

class Node {
private:
    string studentID, name;
    string startStation, endStation;
    float distance, co2Saved;
    Node* next;

public:
    Node(string sid, string n, string s, string e, float dist, float co2) 
    {
        studentID = sid;
        name = n;
        startStation = s;
        endStation = e;
        distance = dist;
        co2Saved = co2;
        next = nullptr;
    }

    void setNext(Node* n) { next = n; }
    Node* getNext() { return next; }

    string getStudentID() { return studentID; }
    string getName() { return name; }
    string getStart() { return startStation; }
    string getEnd() { return endStation; }
    float getDistance() { return distance; }
    float getCO2() { return co2Saved; }
};

