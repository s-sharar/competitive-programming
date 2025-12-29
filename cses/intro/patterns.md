# Competitive Programming Patterns

## 1. Bitmask Subset Enumeration
**Used in:** `appledivision.cpp`

Iterate through all 2^n subsets of n elements using a bitmask. Each integer from 0 to 2^n-1 represents a subset.

```cpp
int subsetCount = 1 << n;  // 2^n
for (int mask = 0; mask < subsetCount; mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            // element i is in this subset
        }
    }
}
```

**When to use:** Partition problems, subset sum, when n ≤ 20.

---

## 2. Backtracking with Duplicate Skipping
**Used in:** `creatingstrings.cpp`

Generate all unique permutations by sorting first, then skipping duplicates during recursion.

```cpp
sort(s.begin(), s.end());
// In the recursive loop:
if (i > 0 && s[i] == s[i-1] && !used[i-1]) continue;
```

**Key insight:** Only use a duplicate character if the previous identical character was already used in the current path.

**When to use:** Permutations/combinations with repeated elements.

---

## 3. Binary Exponentiation (Modular Power)
**Used in:** `bitstrings.cpp`

Compute a^e mod m in O(log e) time.

```cpp
long long modpow(long long a, long long e, long long mod) {
    long long res = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}
```

**When to use:** Large exponents, counting problems with modular arithmetic.

---

## 4. Mathematical Invariant / Constraint Analysis
**Used in:** `coinpiles.cpp`

Derive necessary and sufficient conditions mathematically instead of simulating.

For coin piles: can we reduce (a, b) to (0, 0) by repeatedly taking 1 from one and 2 from the other?
- Total removed per move = 3, so (a + b) % 3 == 0
- Can't take 2 from a pile smaller than the other's half, so max ≤ 2 * min

**When to use:** Problems asking "is X possible?" — look for invariants.

---

## 5. Frequency Counting for Construction
**Used in:** `palindromereorder.cpp`

Count character frequencies to determine feasibility and construct the answer.

**Palindrome rule:** At most one character can have odd frequency.

```cpp
vector<int> cnt(26, 0);
for (char c : s) cnt[c - 'a']++;
// Check odd counts, then build left half + middle + reversed left
```

**When to use:** Anagram problems, palindrome construction, string rearrangement.

---

## 6. Pattern Recognition / Direct Formula
**Used in:** `numberspiral.cpp`

For grid/spiral/sequence problems, find a closed-form formula by analyzing the pattern.

**Approach:**
1. Write out small cases manually
2. Identify which variable dominates (row vs column)
3. Derive formula based on layer/diagonal position

**When to use:** Matrix traversal patterns, sequence position queries.

---

## 7. Linear Scan with Running State
**Used in:** `repetitions.cpp`

Track current streak while scanning, update global answer on each step.

```cpp
int count = 0, maxCount = 0;
char prev = '\0';
for (char c : s) {
    count = (c == prev) ? count + 1 : 1;
    maxCount = max(maxCount, count);
    prev = c;
}
```

**When to use:** Longest consecutive sequence, streak counting, running statistics.

