#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cctype>
#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cwchar>

using namespace std;
typedef long long ll;

int main() {
    ll n, y, x;
    cin >> n;
    while (n--) {
        cin >> y >> x;
        if (y > x) {
            if (y % 2 == 0) {
                cout << y * y - x + 1 << endl;
            } else {
                cout << (y - 1) * (y - 1) + x << endl;
            }
        } else if (x % 2 == 1) {
            cout << x * x - (y - 1) << endl;
        } else {
            cout << (x - 1) * (x - 1) + y << endl;
        }
    }

}