#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int machine, product;
    cin >> machine >> product;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, ::greater<pair<ll, ll>>> pq;
    ll x;
    for (int i = 0; i < machine; ++i) {
        cin >> x;
        pq.push({x, x});
    }

    int time = 0;
    while (product > 0) {
        const auto [curr, increment] = pq.top();
        pq.pop();
        product--;
        time = curr;
        pq.push({curr + increment, increment});
    }

    cout << time << endl;

}
