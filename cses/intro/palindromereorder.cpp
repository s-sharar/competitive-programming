#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<long long> cnt(26, 0);
    for (char ch : s) cnt[ch - 'A']++;

    int odd = 0;
    int oddIdx = -1;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2) {
            odd++;
            oddIdx = i;
        }
    }

    if (odd > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    string left;
    left.reserve(s.size() / 2);

    for (int i = 0; i < 26; i++) {
        left.append(cnt[i] / 2, char('A' + i));
    }

    string mid = "";
    if (oddIdx != -1) mid.append(1, char('A' + oddIdx));

    string right = left;
    reverse(right.begin(), right.end());

    cout << left << mid << right << "\n";
}
