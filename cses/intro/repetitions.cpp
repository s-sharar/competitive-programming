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

int main() {
    char prev_c = '\0';
    char c = '\0';
    int count = 0;
    int max_count = 0;
    while (cin >> c) {
        if (c == prev_c) {
            count++;
        } else {
            count = 1;
            prev_c = c;
        }
        max_count = max(count, max_count);
    }
    cout << max_count << endl;
    return 0;
}