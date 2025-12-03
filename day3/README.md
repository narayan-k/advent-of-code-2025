# 🎄 Advent of Code 2025 — Day 3  
### Language: **C** 💾

Today’s puzzle was all about squeezing information out of digit sequences using pure C — manual buffers, ASCII arithmetic, and a classic greedy algorithm.  
Compared to JavaScript and Rust, C feels like programming with sharp tools… but dang is it fast.

---

## 🧩 Problem Summary

Each line of input is a string of digits.  
For every line, we compute two things:

---

## ⭐ Part 1 — Best Two-Digit Number (In Order)

Scan the string from **left to right** and build the *largest possible two-digit number* where:

- the first digit appears earlier in the string  
- the second digit appears later  
- digits must stay in order (no rearranging)

Examples:

- `"1234"` → best is `34`  
- `"9081726"` → best is `98`  
- `"456456"` → best is `66`  

We track which digits we've already seen (`seen[10]`), and each time we encounter a new digit `d`, we check if pairing it with a previously seen digit gives a better two-digit number.

---

## ⭐ Part 2 — Pick 12 Digits for the Largest Number

From each line, choose **exactly 12 digits** (preserving order) that make the largest possible 12-digit number.

This uses the classic **greedy monotonic stack**:

- Keep a stack of chosen digits  
- When a new digit `d` arrives:  
  - If it's larger than the top of the stack  
  - *And* we still have enough digits left to reach 12  
  - Pop the smaller digit  
- Push the new digit if we still need more  
- Convert final 12 characters into a `long long`

This gives the lexicographically largest possible result.

---

## 📝 What I Learned Today

### **1. C makes you think about memory all the time.**
Even with lines under 100 chars, you still must choose a buffer size (`MAX_LINE`), ensure null-termination, and avoid overruns. No automatic resizing. No safety nets.

### **2. `static char line[MAX_LINE]` is super important.**
It puts the buffer in **static storage** instead of the stack.  
Safer, and avoids blowing up the stack if you ever increase the size.

### **3. Parsing digits means doing ASCII math manually.**
In C:  
`'7'` is **not** 7 — it’s 55.  
So you subtract `'0'` everywhere:

```c
int d = s[i] - '0';
```

A tiny detail that languages like Python or Rust abstract away.

### **4. Using arrays as stacks is fast and satisfying.**
The monotonic stack isn't a fancy data structure — just:

```c
char stack[K];
int stack_size = 0;
```

Push and pop with simple index math. Zero allocations. Zero overhead.

### **5. You appreciate bounds checks when C doesn't give them to you.**
Out-of-bounds access in Python = error.  
In Rust = compiler stops you.  
In C = silent memory corruption.  
This forces you to be intentional with every loop and condition.
