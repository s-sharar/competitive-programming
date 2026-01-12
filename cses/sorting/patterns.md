# Sorting & Searching Patterns

## 1. Two Pointer Technique

### Description
Use two pointers (often `l` and `r`) that move through a sorted array based on conditions. Pointers typically converge from opposite ends or move in the same direction.

### Implementation
```cpp
sort(arr.begin(), arr.end());
int l = 0, r = n - 1;
while (l < r) {
    if (condition_too_big) r--;
    else if (condition_too_small) l++;
    else { /* found */ break; }
}
```

### When to Use
- **Finding pairs with a target sum** → sort, then converge pointers (`sumoftwovalues.cpp`)
- **Matching two sorted sequences** → sort both, advance pointers greedily (`apartments.cpp`)
- **Greedy pairing (min + max)** → pair smallest with largest when possible (`ferriswheel.cpp`)

### Problems
- `apartments.cpp` - Match applicants to apartments within tolerance
- `ferriswheel.cpp` - Pair lightest + heaviest if under weight limit
- `sumoftwovalues.cpp` - Find two values that sum to target

---

## 2. Sliding Window

### Description
Maintain a window `[l, r]` that expands by incrementing `r` and contracts by incrementing `l`. Track window state using a hashmap, counter, or running sum.

### Implementation
```cpp
int l = 0;
long long sum = 0;  // or use map for frequency
for (int r = 0; r < n; r++) {
    // Expand: add a[r] to window state
    sum += a[r];
    
    // Contract: shrink from left while invalid
    while (invalid_condition && l <= r) {
        sum -= a[l];
        l++;
    }
    
    // Update answer
    ans = max(ans, r - l + 1);
}
```

### When to Use
- **Longest/shortest subarray with property** → track window validity with map/set
- **Subarray sum equals X (positive values only)** → expand right, shrink left when sum > x
- **Longest subarray with all unique elements** → use hashmap to detect duplicates

### Problems
- `playlist.cpp` - Longest subarray with unique elements (use `unordered_map`)
- `subarraysums.cpp` - Count subarrays with sum = x (only works for positive values!)

---

## 3. Prefix Sum + HashMap

### Description
For subarray problems with negative numbers, use prefix sums. The sum of subarray `[i+1, j]` is `prefix[j] - prefix[i]`. Use a hashmap to count prefix sums seen so far.

### Implementation
```cpp
unordered_map<ll, ll> cnt;
cnt[0] = 1;  // empty prefix
ll pref = 0, ans = 0;

for (int i = 0; i < n; i++) {
    pref += a[i];
    // Looking for prefix[j] - prefix[i] = x → prefix[i] = prefix[j] - x
    ans += cnt[pref - x];
    cnt[pref]++;
}
```

### When to Use
- **Count subarrays with sum = x** (works with negative numbers!)
- **Count subarrays with sum divisible by k** → use `pref % k` as key
- Any subarray property expressible as `prefix[j] - prefix[i] = target`

### Problems
- `subarraysums2.cpp` - Count subarrays summing to x (handles negatives)

---

## 4. Event/Line Sweep

### Description
Convert intervals `[start, end]` into discrete events: `+1` at start, `-1` at end. Sort events by time, sweep through and track current count.

### Implementation
```cpp
vector<pair<int, int>> events;
for (auto [a, b] : intervals) {
    events.push_back({a, +1});  // arrival
    events.push_back({b, -1});  // departure
}
sort(events.begin(), events.end());

int cur = 0, maxCount = 0;
for (auto [time, delta] : events) {
    cur += delta;
    maxCount = max(maxCount, cur);
}
```

### When to Use
- **Maximum overlapping intervals** (peak customers, max concurrent events)
- **Count active intervals at any point**
- Any problem about interval overlaps without needing to track which intervals

### Problems
- `restaurantcustomers.cpp` - Find maximum concurrent customers

---

## 5. Greedy Interval Scheduling

### Description
For non-overlapping interval selection, sort by **end time** and greedily pick intervals that start after the previous one ends.

### Implementation
```cpp
// Sort by end time (earliest ending first)
sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
    return a.second < b.second;
});

int count = 0, lastEnd = INT_MIN;
for (auto [start, end] : intervals) {
    if (start >= lastEnd) {
        count++;
        lastEnd = end;
    }
}
```

### When to Use
- **Maximum number of non-overlapping intervals** → sort by end time
- **Activity selection / job scheduling** without weights
- Movie festivals, meetings, etc.

### Problems
- `moviefestivals.cpp` - Select maximum non-overlapping movies

---

## 6. Priority Queue for Interval Assignment

### Description
For assigning resources (rooms, machines) to intervals, sort by start time and use a min-heap tracking when each resource becomes free.

### Implementation
```cpp
sort(guests.begin(), guests.end(), [](auto &a, auto &b) {
    return a.start < b.start;
});

// Min-heap: (end_time, resource_id)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
int resourceCount = 0;

for (auto &g : guests) {
    if (!pq.empty() && pq.top().first < g.start) {
        // Reuse freed resource
        auto [endTime, room] = pq.top();
        pq.pop();
        assign(g, room);
        pq.push({g.end, room});
    } else {
        // Need new resource
        resourceCount++;
        assign(g, resourceCount);
        pq.push({g.end, resourceCount});
    }
}
```

### When to Use
- **Minimum resources to serve all intervals** (room allocation, parallel jobs)
- **Assign specific resource IDs** to intervals

### Problems
- `roomallocation.cpp` - Assign minimum rooms to guests with check-in/check-out times

---

## 7. Binary Search on Answer

### Description
When asked "find minimum X such that condition(X) is true", binary search on X. Need a monotonic predicate: if `valid(x)` is true, then `valid(x+1)` is also true (or vice versa).

### Implementation
```cpp
auto canAchieve = [&](long long x) -> bool {
    // Return true if x is sufficient
};

long long lo = 0, hi = 1;
while (!canAchieve(hi)) hi *= 2;  // Find upper bound

while (lo + 1 < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (canAchieve(mid)) hi = mid;
    else lo = mid;
}
cout << hi << "\n";
```

### When to Use
- **Minimize/maximize some value** where feasibility is monotonic
- "What's the minimum time to produce X items?"
- "What's the maximum value we can achieve given constraints?"

### Problems
- `factorymachines.cpp` - Minimum time to produce t products with n machines

---

## 8. Multiset for Dynamic Ordered Operations

### Description
Use `multiset` (or `set`) when you need O(log n) insertion, deletion, and ordered queries (predecessor/successor).

### Implementation
```cpp
multiset<int> ms;
ms.insert(x);

// Find largest value <= x
auto it = ms.upper_bound(x);  // first > x
if (it != ms.begin()) {
    --it;  // now <= x
    int val = *it;
    ms.erase(it);  // remove one occurrence
}

// Find smallest value > x
auto it = ms.upper_bound(x);
if (it != ms.end()) {
    int val = *it;
}
```

### When to Use
- **Online queries** requiring ordered access (find closest, find predecessor)
- **Dynamic LIS-like problems** → track tops of piles
- **Ticket matching** → find best available ticket ≤ budget

### Problems
- `concerttickets.cpp` - Find and remove largest ticket ≤ customer's max price
- `towers.cpp` - Greedy tower stacking (like LIS with multiset)

---

## 9. Set + Multiset for Gap/Segment Tracking

### Description
Maintain a set of positions and a multiset of gaps between adjacent positions. When inserting a new position, remove the old gap and insert two new gaps.

### Implementation
```cpp
set<int> positions;
multiset<int> gaps;
positions.insert(0);
positions.insert(x);  // boundaries
gaps.insert(x);

void addPosition(int p) {
    auto it = positions.upper_bound(p);
    auto prevIt = prev(it);
    
    // Remove old gap
    gaps.erase(gaps.find(*it - *prevIt));
    
    // Add two new gaps
    gaps.insert(p - *prevIt);
    gaps.insert(*it - p);
    
    positions.insert(p);
    
    // Max gap is *gaps.rbegin()
}
```

### When to Use
- **Track maximum/minimum gap** between points dynamically
- Inserting points on a line and querying largest segment

### Problems
- `trafficlights.cpp` - After each light insertion, report longest passage without lights

---

## 10. Monotonic Stack

### Description
Use a stack to find the nearest smaller/larger element for each position. Process elements and maintain stack invariant (e.g., increasing or decreasing order).

### Implementation
```cpp
// Find nearest smaller element to the LEFT for each position
stack<pair<int, int>> st;  // (value, index)
vector<int> result(n);

for (int i = 0; i < n; i++) {
    while (!st.empty() && st.top().first >= a[i]) {
        st.pop();
    }
    result[i] = st.empty() ? 0 : st.top().second + 1;
    st.push({a[i], i});
}
```

### When to Use
- **Nearest smaller/larger element** to left or right
- **Histogram problems** (largest rectangle, stock span)
- **Next greater element** variants

### Problems
- `nearestsmallervalues.cpp` - For each element, find index of nearest smaller element to the left

---

## 11. Kadane's Algorithm (Maximum Subarray Sum)

### Description
Dynamic programming to find maximum subarray sum. For each position, decide whether to extend the previous subarray or start fresh.

### Implementation
```cpp
long long best = LLONG_MIN;
long long cur = 0;

for (int i = 0; i < n; i++) {
    cur = max(a[i], cur + a[i]);  // extend or restart
    best = max(best, cur);
}
```

### When to Use
- **Maximum sum contiguous subarray**
- Can extend to track start/end indices if needed

### Problems
- `maximumsubarraysum.cpp` - Classic maximum subarray sum

---

## 12. Median Minimizes L1 Distance

### Description
To minimize sum of absolute differences to a target value, choose the **median**. The median minimizes ∑|x_i - target|.

### Implementation
```cpp
sort(a.begin(), a.end());
long long median = a[n / 2];

long long cost = 0;
for (int i = 0; i < n; i++) {
    cost += abs(a[i] - median);
}
```

### When to Use
- **Make all elements equal** with minimum total cost (cost = |difference|)
- Meeting point problems in 1D

### Problems
- `sticklengths.cpp` - Minimum cost to make all sticks equal length

---

## 13. Greedy Coin/Reachability

### Description
Process sorted coins. Track the maximum sum reachable with coins seen so far. If next coin > reach + 1, there's a gap.

### Implementation
```cpp
sort(a.begin(), a.end());
long long reach = 0;

for (long long x : a) {
    if (x > reach + 1) break;  // can't make reach + 1
    reach += x;
}

cout << reach + 1 << "\n";  // first sum we can't make
```

### When to Use
- **Find smallest sum that cannot be formed**
- Coin coverage problems

### Problems
- `missingcoinsum.cpp` - Find minimum sum that cannot be created with given coins

---

## 14. Position/Inverse Mapping

### Description
Map values to their positions (or vice versa) to answer queries about relative ordering without sorting repeatedly.

### Implementation
```cpp
vector<int> pos(n + 1);  // pos[value] = index
for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    pos[x] = i;
}

// Count inversions: how many pairs (x, x+1) have pos[x] > pos[x+1]
int rounds = 1;
for (int x = 2; x <= n; x++) {
    if (pos[x] < pos[x - 1]) rounds++;
}
```

### When to Use
- **Counting rounds to collect 1..n in order**
- **Tracking inversions** between consecutive values
- Quick lookup of where a value appears

### Problems
- `collectingnumbers.cpp` - Count rounds to collect 1 to n in order
- `collectingcoinnumbers2.cpp` - Handle swaps with incremental updates

---

## Summary Table

| Pattern | Time Complexity | Key Insight |
|---------|-----------------|-------------|
| Two Pointer | O(n) after O(n log n) sort | Sorted order enables linear scan |
| Sliding Window | O(n) | Expand/contract to maintain validity |
| Prefix Sum + HashMap | O(n) | subarray[i,j] = prefix[j] - prefix[i] |
| Event Sweep | O(n log n) | Convert intervals to discrete events |
| Greedy Interval (end sort) | O(n log n) | Earliest end time maximizes choices |
| Priority Queue Assignment | O(n log n) | Min-heap tracks next available resource |
| Binary Search on Answer | O(n log X) | Monotonic predicate enables binary search |
| Multiset | O(log n) per op | Dynamic ordered set with duplicates |
| Set + Multiset Gaps | O(log n) per op | Track gaps between adjacent elements |
| Monotonic Stack | O(n) | Stack maintains sorted order invariant |
| Kadane's Algorithm | O(n) | DP: extend or restart subarray |
| Median for L1 | O(n log n) | Median minimizes sum of absolute differences |
| Greedy Reachability | O(n log n) | Track reachable range, detect gaps |
| Position Mapping | O(n) | Value → index for O(1) lookup |
