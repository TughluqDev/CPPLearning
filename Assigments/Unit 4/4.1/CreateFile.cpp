#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void createFile(string fileName){
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;

    ofstream fileWriter(fileName);

    cout<<"Please enter your first num: ";
    cin>>num1;

    cout<<"Please enter your second num: ";
    cin>>num2;

    cout<<"Please enter your third num: ";
    cin>>num3;

    cout<<"Please enter your fourth num: ";
    cin>>num4;

    cout<<"Please enter your fith num: ";
    cin>>num5;

    fileWriter<<num1 <<endl << num2 << endl << num3 << endl  << num4 << endl  << num5;
    fileWriter.close();


}

int main(){
    string fileName;

    cout << "Please enter the name of the file you would like to create: ";
    getline(cin,fileName);

    createFile(fileName);


}