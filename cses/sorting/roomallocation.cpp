#include <bits/stdc++.h>
using namespace std;

struct Guest {
    int start, end, index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Guest> guests;
    guests.reserve(n);

    for (int i = 0; i < n; ++i) {
        int start, end;
        cin >> start >> end;
        guests.push_back({start, end, i});
    }

    sort(guests.begin(), guests.end(), [](const Guest &a, const Guest &b) {
        if (a.start != b.start) return a.start < b.start;
        return a.end < b.end;
    });

    // (end_time, room_number)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int roomsUsed = 0;
    vector<int> assignedRoom(n);

    for (const auto &g : guests) {
        if (!pq.empty() && pq.top().first < g.start) {
            auto [endTime, room] = pq.top(); // copy (NOT ref)
            pq.pop();
            assignedRoom[g.index] = room;
            pq.push({g.end, room});
        } else {
            ++roomsUsed;
            assignedRoom[g.index] = roomsUsed;
            pq.push({g.end, roomsUsed});
        }
    }

    cout << roomsUsed << "\n";
    for (int i = 0; i < n; ++i) {
        if (i) cout << " ";
        cout << assignedRoom[i];
    }
    cout << "\n";
}
