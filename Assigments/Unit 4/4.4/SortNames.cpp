#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> sortNames(vector<string> names){
    for (int i = 0; i < names.size(); i++){

        for (int j = i+1; j < names.size(); j++){

            if (names[i] > names[j]){
                string temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }

        }

    }

    for (string i : names){
        cout << i;
    }

    return names;
}

void reverseSortNames(vector<string> names){
    for (int i = 0; i < names.size(); i++){

        for (int j = i+1; j < names.size(); j++){

            if (names[i] < names[j]){
                string temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }

        }

    }

    for (string i : names){
        cout << i;
    }

}

int main(){
    vector<string> names = {" nikita ", " tugluke ", " alhadi ", " yousef ", " josh ", " aayansh "};
    vector<string> normalSorted = sortNames(names);
    cout << endl;
    reverseSortNames(normalSorted);

}