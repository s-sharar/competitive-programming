Yeah. There are a few **DP patterns** here that show up everywhere. Remember these and half of CSES becomes mechanical.

## Pattern 1: “DP by position + last value” (state = where you are + what you ended with)

When constraints only link neighbors (like `|a[i]-a[i-1]| <= 1`), the past only matters through the **last value**.

* State: `dp[i][v]` = ways up to index `i` ending with value `v`
* Transition: only from “neighboring v’s”:

  * `dp[i][v] += dp[i-1][v-1] + dp[i-1][v] + dp[i-1][v+1]`

**Memory trick:** keep only previous row → `prev[v]`, `cur[v]`.

## Pattern 2: “Mask out illegal states”

If `a[i]` is fixed to `k`, then:

* compute only `cur[k]`
* everything else stays `0`

This is a general trick: **restrict states instead of branching logic all over**.

## Pattern 3: “Pad the DP array to avoid bounds checks”

We used size `m+2` so `prev[v-1]` and `prev[v+1]` are always safe.
The padding values are 0, which matches “out of range = no ways”.

Super common in grid/path/count DPs.

## Pattern 4: Mod arithmetic precedence

Always do:

```cpp
cur[v] = ( (ll)a + b + c ) % MOD;
```

Not `a + b + c % MOD`.

## Pattern 5: “Don’t worry about the future” (DP filters later)

Even if right-side fixed values exist, forward DP is still correct because impossible prefixes get zeroed when you hit a constraint.

## Pattern 6: Transition graph view

This problem is literally:

* nodes = `(i, v)`
* edges from `(i-1, v-1/v/v+1)` → `(i, v)`
  Counting paths in a DAG.

That perspective helps you invent the DP quickly.

---

### Mental template to memorize

When you see:

* array length `n`
* values in `1..m`
* some entries unknown (0)
* constraint depends on neighbors

Think:

> `dp[value]` for current position
> `cur[v] = sum(prev[allowed previous values])`
> apply fixed-value masking
> swap rows

If you want, tell me the next problem you’re doing and I’ll name the exact pattern it reduces to (same way).
