#include <iostream>
#include <string>

using namespace std;

int main(){
    string input;
    int age;
    float height;


    cout << "Please enter your age";
    getline(cin, input);
    age = stoi(input);

    cout << "Please enter your height";
    getline(cin, input);
    height = stof(input);

    system("CLS");  

    cout << "Your Age Is: " << age;
    cout << "Your Height Is: " << height;
}


