#include <iostream>

using namespace std;

int main() {
    double originalDouble = 9.87;
    int convertedInt = originalDouble;  

    cout << "Original double: " << originalDouble << endl;
    cout << "Converted to int: " << convertedInt << endl;
    cout << "Data lost: " << (originalDouble - convertedInt) << endl;

    cout << endl;

    int largeInt = 123456789;
    double convertedDouble = largeInt;
    int backToInt = convertedDouble;

    cout << "Original int: " << largeInt << endl;
    cout << "Converted to double: " << convertedDouble << endl;
    cout << "Converted back to int: " << backToInt << endl;

    /*
      1. Large integers may lose precision when stored in doubles because doubles
         use floats.
      2. Silent data loss can introduce bugs that are hard to detect.
     */

    return 0;
}
