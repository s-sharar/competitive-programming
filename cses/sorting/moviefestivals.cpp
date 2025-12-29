#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<pair<int, int>> vpi;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vpi movies;
    for (int i = 0; i < n; ++i) {
        int start, end;
        cin >> start >> end;
        movies.push_back({start, end});
    }

    sort(movies.begin(), movies.end(), [] (const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    int maxMovies = 1;
    if (movies.empty()) {
        cout << 0 << endl;
        return 0;
    }
    int lastEnd = movies[0].second;
    for (int i = 1; i < n; ++i) {
        const auto &[start, end] = movies[i];
        if (start >= lastEnd) {
            maxMovies++;
            lastEnd = end;
        }
    }
    cout << maxMovies << endl;

}
