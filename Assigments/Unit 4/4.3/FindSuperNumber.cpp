#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

vector<int> readFile(){
    vector<int> numberList;
    string numFromFile;
    ifstream fileReader("numbers.txt");
    
    while (getline(fileReader, numFromFile)) {
        numberList.push_back(stoi(numFromFile));
    }

    fileReader.close();

    return numberList;
}

void findValue(vector<int> sortedList, int targetValue){
    int highValue = sortedList.size() -1;
    int lowValue = 0;
    int middleValue;

    while (highValue >= lowValue) {
        int middleValue = (highValue + lowValue) / 2;

        if (sortedList[middleValue] ==  targetValue){
            cout << sortedList[middleValue] << " was found at index " << middleValue;
            break;
        } 

        else if (sortedList[middleValue] < targetValue){
            lowValue = middleValue + 1;
        }

        else if (sortedList[middleValue] > targetValue){
            highValue = middleValue - 1;
        }

        if (highValue < lowValue){
            cout << targetValue << " is not located in this list";
        }
    }

    
}

int main(){
    int targetNumber = 2;
    vector<int> sortedList = readFile();

    findValue(sortedList, targetNumber);
}