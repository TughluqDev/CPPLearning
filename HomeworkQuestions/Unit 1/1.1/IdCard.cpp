#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string getString(string getinfo) {
    string input;
    cout << "Hello User, please enter your " << getinfo << ": ";
    getline(cin, input);
    return input;
}

int main() {
    string firstName;
    string lastName;
    string sectionInput;
    string seatInput;

    char section;
    int seatNumber;

    firstName = getString("first name");
    lastName = getString("last name");
    sectionInput = getString("seat section");
    seatInput = getString("seat number");
    float price = 83.00;

    section = sectionInput[0];       
    seatNumber = stoi(seatInput);    

    string fullName = firstName + " " + lastName;



    printf("|-----------------------------------|\n");  
    printf("| Name: %-25s   |\n", fullName.c_str());             
    printf("| Section: %-22c   |\n", section); 
    printf("| Seat: %-25d   |\n", seatNumber); 
    printf("| Price: $%-23.2f   |\n", price); 
    printf("|-----------------------------------|\n");

    return 0;
}
