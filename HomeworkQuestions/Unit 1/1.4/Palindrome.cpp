#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(const string& str) {
    int left = 0; 
    int right = str.length() - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

int main() {
    string s1 = "madam";
    string s2 = "race car";

    cout << "\"" << s1 << "\" is palindrome: " << (isPalindrome(s1) ? "true" : "false") << std::endl;
    cout << "\"" << s2 << "\" is palindrome: " << (isPalindrome(s2) ? "true" : "false") << std::endl;

    return 0;
}
