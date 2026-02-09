#include<iostream>
#include<string>

using namespace std;


int main (){
    string input;
    float height;
    float homeDistanceFromSchool;
    float conversionFactor = 2.54;

    cout << "Please Enter Your Height In CM: \n";
    getline(cin, input);
    height = stof(input) / conversionFactor;

    cout << "Please Enter How Far Your Home Is From The School: \n";
    getline(cin,input);
    homeDistanceFromSchool = stof(input) / conversionFactor;

    cout << "After Intense Calculations...\n";
    cout << "Your Height In Inches is: \n"  << height;
    cout << "Your Home Distance From School In Inches Is: \n" << homeDistanceFromSchool;
}