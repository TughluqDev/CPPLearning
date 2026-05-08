#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

vector<char> readFile(){
    vector<char> charList;
    int numFromFile;
    ifstream fileReader("secret.txt");
    
    while (fileReader >> numFromFile) {
        charList.push_back(static_cast<char>(numFromFile));
    }

    fileReader.close();

    for(char i : charList){
        cout<< i;
    }

    return charList;
}

void findNum(char targetChar, vector<char> list){
    for (char i = 0; i < list.size(); i++){
        if (list[i] == targetChar){
            cout<<endl << "Letter " << targetChar <<" found at index: "<< int(i) << endl;
            return;
        }
    }
    cout<<"Not found";
}

char findMaxChar(vector<char> list){
    char maxChar = list[0];

    for (char i = 0; i < list.size(); i++){
        if (list[i] > maxChar){
            maxChar = list[i];
        }
    }

    return maxChar;
}

int main(){
    char word = 'p';
    vector<char> wordList = readFile();
    char maxChar = findMaxChar(wordList);

    findNum(word, wordList);
    cout << "The maximum character in this list is: " << maxChar << " or " << int(maxChar);
}