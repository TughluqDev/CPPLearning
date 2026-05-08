#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void readFile(string fileName){
    vector<int> numberList;
    string numFromFile;
    ifstream fileReader(fileName);
    
    while (getline(fileReader, numFromFile)) {
        numberList.push_back(stoi(numFromFile));
    }

    fileReader.close();

    for(int i : numberList){
        cout<< i << endl;
    }
}

int main(){
    string fileName;

    cout<<"Enter the file you would like to read: ";
    getline(cin,fileName);

    readFile(fileName);
}