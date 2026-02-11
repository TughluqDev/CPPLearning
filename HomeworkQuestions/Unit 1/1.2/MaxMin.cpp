#include <iostream>
#include <climits>

using namespace std;

int main() {
    cout << "1. Int" << endl;
    cout << "   Min: " << INT_MIN << endl;
    cout << "   Max: " << INT_MAX << endl;

    cout << "2. Unsigned Int" << endl;
    cout << "   Min: " << 0 << endl;
    cout << "   Max: " << UINT_MAX << endl;

    cout << "3. Short" << endl;
    cout << "   Min: " << SHRT_MIN << endl;
    cout << "   Max: " << SHRT_MAX << endl;

    cout << "4. Unsigned Short" << endl;
    cout << "   Min: " << 0 << endl;
    cout << "   Max: " << USHRT_MAX << endl;

    cout << "5. Long" << endl;
    cout << "   Min: " << LONG_MIN << endl;
    cout << "   Max: " << LONG_MAX << endl;

    cout << "6. Unsigned Long" << endl;
    cout << "   Min: " << 0 << endl;
    cout << "   Max: " << ULONG_MAX << endl;

    return 0;
}
