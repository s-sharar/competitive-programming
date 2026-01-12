# Dynamic Programming Patterns

## 1. Linear DP (1D State)

### Description
DP where state depends only on previous states in a single dimension (usually index or value).

### When to Use
- Counting ways to reach a target (dice rolls, coin combinations)
- Finding min/max steps to reach a value
- Problems with a clear "stage" progression

### Implementation
```cpp
dp[0] = base_case;
for (int i = 1; i <= n; i++) {
    for (each transition t) {
        dp[i] = combine(dp[i], dp[i - t]);
    }
}
```

### Examples in Directory
- `dicecombinations.cpp` - Count ways to get sum n with dice (1-6)
- `coincombinations.cpp` - Count ways to make amount with coins (order matters, unlimited use)
- `minimizingcoins.cpp` - Min coins to reach amount
- `removingdigits.cpp` - Min steps to reduce n to 0 by subtracting its digits

---

## 2. 0/1 Knapsack

### Description
Each item can be used at most once. Classic "choose or skip" pattern.

### When to Use
- Select subset of items with capacity/weight constraint
- Maximize value or count combinations under constraints
- Each item has a binary decision (take or leave)

### Implementation
```cpp
// 1D space-optimized: iterate capacity BACKWARDS to avoid using same item twice
for (int i = 0; i < n; i++) {
    for (int c = capacity; c >= weight[i]; c--) {
        dp[c] = max(dp[c], dp[c - weight[i]] + value[i]);
    }
}
```

### Key Insight
**Backward iteration** ensures each item is used at most once in the optimized 1D version.

### Examples in Directory
- `bookshop.cpp` - Maximize pages with budget constraint
- `moneysums.cpp` - Find all achievable sums using each coin once
- `twosets2.cpp` - Count ways to partition {1..n} into two equal-sum sets

---

## 3. Unbounded Knapsack

### Description
Each item can be used unlimited times.

### When to Use
- Coin change problems with unlimited coins
- Minimizing/maximizing with repeatable choices
- Rod cutting, infinite supply problems

### Implementation
```cpp
// 1D: iterate capacity FORWARDS to allow reusing items
dp[0] = base;
for (int s = 1; s <= amount; s++) {
    for (int coin : coins) {
        if (s >= coin) dp[s] = combine(dp[s], dp[s - coin]);
    }
}
```

### Key Insight
**Forward iteration** allows reusing the same item multiple times.

### Examples in Directory
- `minimizingcoins.cpp` - Min coins to make amount
- `coincombinations.cpp` - Count ways (order matters)

---

## 4. Bounded Knapsack (Combinations without Order)

### Description
Count distinct combinations (not permutations) where each item can be used multiple times but order doesn't matter.

### When to Use
- "How many ways to form amount X" where {1,2} and {2,1} count as same
- Counting unordered selections

### Implementation
```cpp
// Iterate ITEMS in outer loop, SUMS in inner loop
dp[0] = 1;
for (int coin : coins) {
    for (int s = coin; s <= amount; s++) {
        dp[s] += dp[s - coin];
    }
}
```

### Key Insight
Iterating items first, then sums, ensures each combination is counted once (not permutations).

### Examples in Directory
- `coincombinations2.cpp` - Count combinations (order doesn't matter)

---

## 5. 2D Grid DP

### Description
DP on 2D grid where state depends on adjacent cells (usually up/left).

### When to Use
- Path counting in grids
- Minimum cost paths
- Grid traversal with obstacles

### Implementation
```cpp
dp[0][0] = start_value;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (blocked[i][j]) { dp[i][j] = 0; continue; }
        if (i > 0) dp[i][j] += dp[i-1][j];
        if (j > 0) dp[i][j] += dp[i][j-1];
    }
}
```

### Examples in Directory
- `gridpaths.cpp` - Count paths from (0,0) to (n-1,n-1) avoiding obstacles

---

## 6. Two-String DP (LCS / Edit Distance)

### Description
DP on two sequences where state is `dp[i][j]` representing some property of prefixes `a[0..i-1]` and `b[0..j-1]`.

### When to Use
- Longest Common Subsequence (LCS)
- Edit Distance (Levenshtein)
- String alignment problems

### Implementation
```cpp
// LCS
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
}

// Edit Distance
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
        else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    }
}
```

### Space Optimization
Use two 1D arrays (prev/curr) instead of 2D to reduce O(nm) space to O(m).

### Examples in Directory
- `longestcommonsubsequence.cpp` - Find LCS of two arrays
- `editdistance.cpp` - Min operations to transform string a to b

---

## 7. Interval DP

### Description
DP over contiguous subarrays/intervals where `dp[l][r]` represents optimal value for range [l, r].

### When to Use
- Problems involving splitting/merging ranges
- Game theory on arrays (picking from ends)
- Optimal parenthesization, matrix chain multiplication

### Implementation
```cpp
// Process by increasing interval length
for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        if (len == 1) { dp[l][r] = base; continue; }
        // Try all split points or endpoint choices
        for (int k = l; k < r; k++) {
            dp[l][r] = optimize(dp[l][r], dp[l][k] + dp[k+1][r] + cost);
        }
    }
}
```

### Examples in Directory
- `rectanglecutting.cpp` - Min cuts to partition rectangle into squares
- `removalgame.cpp` - Maximize score picking from array ends (game theory)

---

## 8. Bitmask DP

### Description
State is a bitmask representing subset of elements. Each bit indicates whether an element is included.

### When to Use
- Problems with n ≤ 20 elements (2^n states)
- Subset enumeration
- TSP-like problems, assignment problems

### Implementation
```cpp
// dp[mask] = optimal value for subset represented by mask
dp[0] = base;
for (int mask = 1; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            int prev_mask = mask ^ (1 << i);
            dp[mask] = optimize(dp[mask], transition(dp[prev_mask], i));
        }
    }
}
```

### Examples in Directory
- `elevatorrides.cpp` - Min elevator rides to transport n people (n ≤ 20), `dp[mask] = {rides, last_weight}`

---

## 9. Linear DP with Multiple States

### Description
Track multiple state variables at each position (e.g., different configurations or conditions).

### When to Use
- When answer at position depends on "which state" you're in
- Tower/block building with different configurations
- State machine DP (on/off, split/merged, etc.)

### Implementation
```cpp
// Example: two states at each position
state1[1] = init1; state2[1] = init2;
for (int i = 2; i <= n; i++) {
    state1[i] = f(state1[i-1], state2[i-1]);
    state2[i] = g(state1[i-1], state2[i-1]);
}
answer = state1[n] + state2[n];
```

### Examples in Directory
- `countingtowers.cpp` - Count tower configurations with split/merged states
- `arraydescriptions.cpp` - `dp[i][v]` = ways to fill array where position i has value v

---

## 10. LIS with Binary Search (Patience Sort)

### Description
Find Longest Increasing Subsequence in O(n log n) using binary search on "tails" array.

### When to Use
- LIS problems with n up to 10^5 or 10^6
- When O(n²) is too slow

### Implementation
```cpp
vector<int> tails;  // tails[i] = smallest ending element of LIS of length i+1
for (int x : arr) {
    auto it = lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}
int lis_length = tails.size();
```

### Key Insight
- `lower_bound` for strictly increasing LIS
- `upper_bound` for non-decreasing LIS

### Examples in Directory
- `lis.cpp` - Longest Increasing Subsequence in O(n log n)

---

## 11. DP with Binary Search (Interval Scheduling)

### Description
Sort intervals by end time, use binary search to find compatible previous intervals.

### When to Use
- Weighted interval scheduling (maximize profit from non-overlapping intervals)
- Job scheduling with deadlines

### Implementation
```cpp
sort(intervals.begin(), intervals.end(), by_end_time);
vector<ll> ends, dp(n+1, 0);
for (int i = 0; i < n; i++) ends[i] = intervals[i].end;

for (int i = 1; i <= n; i++) {
    // Find last interval that ends before current starts
    int j = upper_bound(ends.begin(), ends.end(), intervals[i-1].start - 1) - ends.begin();
    dp[i] = max(dp[i-1], intervals[i-1].profit + dp[j]);
}
```

### Examples in Directory
- `projects.cpp` - Maximize reward from non-overlapping projects

---

## 12. DP with Data Structures (Segment Tree / Monotonic Stack)

### Description
Use auxiliary data structures to speed up DP transitions from O(n²) to O(n log n).

### When to Use
- Range queries needed for transitions (min/max/sum in range)
- LIS variants with additional constraints
- When naive DP is too slow

### Implementation
```cpp
// Use segment tree for range max queries
SegTree seg(n);
for (int i : sorted_order) {
    int best = seg.query(valid_range_for_i);
    dp[i] = 1 + best;
    seg.update(i, dp[i]);
}
```

### Examples in Directory
- `mountainrange.cpp` - Find longest "visible" subsequence using monotonic stack + segment tree

---

## 13. Space Optimization with Rolling Arrays

### Description
When DP only depends on previous row/state, use two arrays instead of full table.

### When to Use
- 2D DP where `dp[i]` only depends on `dp[i-1]`
- Reduce O(nm) space to O(m)

### Implementation
```cpp
vector<int> prev(m+1), curr(m+1);
// Initialize prev
for (int i = 1; i <= n; i++) {
    // Compute curr from prev
    for (int j = 1; j <= m; j++) {
        curr[j] = f(prev[...], curr[...]);
    }
    swap(prev, curr);
}
// Answer is in prev
```

### Examples in Directory
- `editdistance.cpp` - Space-optimized edit distance
- `arraydescriptions.cpp` - Space-optimized state transitions

---

## Quick Reference Table

| Pattern | Time | Space | Key Signal |
|---------|------|-------|------------|
| Linear DP | O(n×k) | O(n) or O(1) | Sequential decisions |
| 0/1 Knapsack | O(nW) | O(W) | Each item once, capacity limit |
| Unbounded Knapsack | O(nW) | O(W) | Items reusable, capacity limit |
| Grid DP | O(nm) | O(nm) or O(m) | 2D grid traversal |
| Two-String DP | O(nm) | O(m) | Compare/align two sequences |
| Interval DP | O(n³) | O(n²) | Subarray/range optimization |
| Bitmask DP | O(2^n × n) | O(2^n) | Small n (≤20), subset selection |
| LIS + Binary Search | O(n log n) | O(n) | Longest increasing subsequence |
| DP + Segment Tree | O(n log n) | O(n) | Range queries in transitions |
