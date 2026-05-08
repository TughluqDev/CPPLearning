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

    for(int i : numberList){
        cout<< i << endl;
    }

    return numberList;
}

void findNum(int targetNum, vector<int> list){
    for (int i = 0; i < list.size(); i++){
        if (list[i] == targetNum){
            cout<<"Found at index: "<< i;
            return;
        }
    }
    cout<<"Not found";
}

int main(){
    int num = 343;
    vector<int> numberList = readFile();
    findNum(num, numberList);
}