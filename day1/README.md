# 🎄 Advent of Code 2025 — Day 1  
### Language: **JavaScript** 🟨

Day 1 kicks things off with a spinning dial, some modular arithmetic, and my first reminder that JavaScript *will* betray you if you let negative numbers near `%`.  
The goal: follow a list of rotations like `R12` and `L5` and figure out how often the dial lands on **0**.

---

## 🧩 Problem Summary

You're given a list of instructions:

```
R12
L3
R80
...
```

Where:

- `R` = rotate right  
- `L` = rotate left  
- Number = how many clicks  
- Dial goes from **0 → 99**, wrapping around  
- Starting point = **50**

Two parts:

### ⭐ Part 1  
Rotate the full distance at once and count how many times the **final position** ends on **0**.

### ⭐ Part 2  
Simulate **every single click**, and count every time the dial points at **0** during the movement — even if the final position isn’t 0.

Basically:
- Part 1: “Did we *end* on 0?”  
- Part 2: “Did we *pass* 0?”  

---

## 📝 What I Learned Today

- JavaScript `%` with negatives is a trap (`-1 % 100 === -1`).  
- You must wrap manually when rotating left.  
- Breaking a movement into individual “clicks” is oddly satisfying.  
- Day 1 is always deceptively simple — the real pain is coming. 🎁🔥
