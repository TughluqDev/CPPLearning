#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;
    char handedness;
    unsigned short age;
    string phoneNumber;

    
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your handedness (L/R/A): ";
    cin >> handedness;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your phone number: ";
    getline(cin, phoneNumber);

    cout << "Name: " << name << endl;
    cout << "Handedness: " << handedness << endl;
    cout << "Age: " << age << endl;
    cout << "Phone: " << phoneNumber << endl;

    return 0;
}
