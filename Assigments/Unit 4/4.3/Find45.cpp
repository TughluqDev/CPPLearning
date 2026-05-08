#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    }

    
}

int main(){
    int targetValue = 45;
    vector<int> sortedList = {34, 40, 45, 48, 53, 63, 87, 87, 88, 89};

    findValue(sortedList, targetValue);
}
