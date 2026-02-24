#include<iostream>
#include<string>

using namespace std;

int main(){
    string input;
    string word;

    cout << "Please enter a word: ";
    getline(cin, input);
    word = input;

    if (word.length() == 5){
        cout << "Cool";
    } else {
        cout << "Bad";
    }

}