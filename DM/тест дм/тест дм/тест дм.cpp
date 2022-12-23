
#include <iostream>
using namespace std;

int digits(int i) {
    int k = i / 1000 % 10;
    int p = i / 100 % 10;
    int c = i / 10 % 10;
    int t = i / 1 % 10;
    if ( i > 999 && i < 10000 && k == p && p == c && c == t && k == t) {
        cout << "---" << endl;
    }
    else if (i > 99 && i < 1000 && p == c && c == t && p == t) {
        cout << "---" << endl;
    }
    else if (i > 9 && i < 100 &&  c == t) {
        cout << "---" << endl;
    }
    else {
        cout << i << endl;
    }
    return i;
}

int main()
{
    int N;
    cin >> N;
    int found_number = 1;
    int n = 0;
    for (int i = 1; i < N; ++i) {
        if (!digits(i)) {
            ++n;
            if (n == N) {
                found_number = i;
                break;
            }
        }
    }
    cout << found_number << endl;
}

