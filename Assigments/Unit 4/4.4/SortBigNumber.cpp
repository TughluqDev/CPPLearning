#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

vector<int> readFile(){
    vector<int> unsortedList;
    int numberFromList;
    ifstream fileReader("numbers.txt");

    while (fileReader >> numberFromList){
        unsortedList.push_back(numberFromList);
    }

    return unsortedList;
}

void sortList(vector<int> list){
    ofstream filewrite("sortednumbers.txt"); 

    for (int i = 0; i < list.size(); i++){

        for (int j = i+1; j < list.size(); j++){
            
            if (list[i] > list[j]){
                int temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }

        }

    }

    for (int i : list){
        filewrite << i << endl;
    }

    filewrite.close();
}

int main(){
    vector<int> unsortedList = readFile();
    sortList(unsortedList);
}