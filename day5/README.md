# 🎄 Advent of Code 2025 — Day 5  
### Language: **C++** 🧩

Today’s puzzle took a sharp turn from grids into interval arithmetic — wrangling ranges of ingredient IDs to figure out what’s “fresh” and what’s… decidedly *not* fresh.  

After yesterday’s breezy Nim experience, C++ felt like tuning a racecar: powerful, fast, but boy do you need to know where the switches are.  
(No `<bits/stdc++.h>` on macOS? Of course not. Why would life be easy?)

---

## 🧩 Problem Summary

The input consists of two sections:

1. **Fresh ID ranges** (`A-B`, inclusive)  
2. **A list of ingredient IDs**  

Freshness rules:

- An ingredient ID is **fresh** if it lies within *any* range.  
- Ranges may overlap, nest, or completely absorb each other.  
- Part One uses the list of IDs.  
- Part Two ignores that list and asks:  
  **How many total IDs are covered by all fresh ranges?**

This turns the puzzle into a classic **merge-intervals problem** with a sprinkle of **binary search**.

---

## ⭐ Part 1 — Which Available Ingredients Are Fresh?

Process:

1. Parse all ranges.  
2. Sort and merge them into a clean, non-overlapping set.  
   Example:  
   10-14, 12-18, 16-20 → 10-20
3. For each ingredient ID, binary-search the merged ranges.  
4. Count how many IDs land inside any interval.

This avoids checking every range for every ID, which would be too slow for AoC-sized inputs.

---

## ⭐ Part 2 — How Many IDs Are Fresh in Total?

Now the ID list is irrelevant.  
We simply compute:

    For each merged range [L, R]:
        size = R - L + 1
    Sum all sizes.

If the merged ranges are:

    [3,5]  → 3 IDs
    [10,20] → 11 IDs
    Total = 14

Nice, neat, and mathematically satisfying.

---

# 🛠️ How I Solved It in C++

This puzzle was a great reminder that C++ is both a scalpel *and* a chainsaw.

### 1. Range merging is the heart of the solution.
Sorting and merging intervals is such a common pattern, and C++’s `sort` makes it painless.

### 2. Binary search is ideal for checking membership.
Once you have sorted, disjoint ranges, checking if an ID fits becomes fast and elegant.

### 3. Watch out for platform quirks.
On macOS, `<bits/stdc++.h>` doesn’t exist — so I listed headers manually.  
Once compiled, though, C++ absolutely *flies* on this problem.

### 4. C++ shines when you need low-level control but high performance.
No GC surprises, no hidden allocations — just vectors, loops, and the metal.

---

# 🧠 What I Learned Today

### 1. Interval problems become trivial once you merge ranges.
Everything after that is just light bookkeeping.

### 2. Binary search brings real performance wins.
Checking thousands of IDs becomes instant.

### 3. C++ std::vector is a Swiss army knife.
Clear, predictable, and efficient.

### 4. Always test your merging logic.
One off-by-one error and suddenly your range counts are wildly wrong.

### 5. Avoid `<bits/stdc++.h>` if you want portability.
It's convenient… until it isn’t.

