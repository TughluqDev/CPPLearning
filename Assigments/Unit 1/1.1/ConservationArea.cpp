#include<iostream>
#include<string>

using namespace std;


string grabInfo(string value){
    string input;
    cout << "Please enter your " << value << ": ";
    getline(cin, input);

    return input;
}

int calculateProjectedPopulation(int startingamount, int yeardifference){
    return startingamount * (1 << yeardifference);
}

int main() {
    int currentYear = 2020;
    int targertYear;
    int startingPopulation;
    string animalType;
    int projectedPopulation;
    int yearsRequired;


    animalType = grabInfo("Animal Type");
    targertYear = stoi(grabInfo("Target Year"));
    startingPopulation = stoi(grabInfo("Starting Population"));
    yearsRequired = targertYear - currentYear;
    projectedPopulation = calculateProjectedPopulation(startingPopulation, yearsRequired);


    cout << "Animal Type: " << animalType << endl;
    cout << "Starting Amount: " << startingPopulation << endl;
    cout << "Current Year: " << currentYear << endl;
    cout << "Projected Year: " << targertYear << endl;
    cout << "Projected Population: " << projectedPopulation << endl;


}