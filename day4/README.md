# 🎄 Advent of Code 2025 — Day 4  
### Language: **Nim** 🟠

Today’s puzzle dove into grid geometry and cascading visibility — peeling away layers of rolls of paper until nothing remains accessible.  
After fighting with Zig for a bit, I switched to **Nim**, and honestly? It was a breath of fresh air. Nim feels like Python wearing a jetpack: clean syntax, powerful standard library, native performance.

---

## 🧩 Problem Summary

The input is a **2D grid** of characters:

- `'@'` = a roll of paper  
- `'.'` = empty space  

A “forklift” can remove a roll of paper if it has **fewer than 4 neighboring rolls** (considering all 8 directions).

This turns the problem into a mix of **cellular automata**, **flood peeling**, and **adjacency counting**.

---

## ⭐ Part 1 — Count Initially Accessible Rolls

A roll is **accessible** if it has **< 4 adjacent `@` neighbors**.

Adjacency includes:

```
8 neighbors:
NW  N  NE
W   x   E
SW  S  SE
```

So Part 1 is simply:

- Scan the grid  
- Count rolls with fewer than 4 neighbors  

No recursion or iteration needed yet — just geometry.

---

## ⭐ Part 2 — Remove Accessible Rolls, Revealing More

This is where the puzzle becomes dynamic.

Process:

```
repeat:
    find all rolls with < 4 neighbors
    remove them (replace '@' with '.')
    accumulate count
until no more rolls can be removed
```

Each removal step may expose new rolls on the interior.  
Think of it like peeling an onion — layer after layer of newly exposed surfaces.

The final answer is the **total number removed across all rounds**, not just the first one.

---

# 🛠️ How I Solved It in Nim

Nim makes this type of problem *really* pleasant:

### **1. Reading input is one line:**
```nim
let grid = readAll(stdin).splitLines()
```

### **2. Strings are mutable sequences of chars.**
Easy to treat each line as a row.

### **3. Adjacency loops are lightweight and expressive.**
```nim
for (dy, dx) in dirs:
  if grid[ny][nx] == '@':
    adj.inc()
```

### **4. Nim's performance is C-like without manual memory plumbing.**
No mallocs, no pointer juggling — just clean logic.

---

# 🧠 What I Learned Today

### **1. Grid problems become easy when your language handles strings and indexing cleanly.**  
Nim’s safety around bounds and its flexible string type make it ideal for puzzle grids.

### **2. Simulations are simpler when you just mutate the grid.**  
Instead of tracking “layers” or performing BFS, you can directly modify the grid and re-check neighbors.

### **3. Nim's loops feel like Python but run like C.**  
This puzzle leaned on tight nested loops; Nim handled it effortlessly.

### **4. Adjacency rules reward clarity.**  
Keeping the 8 directions in a static array makes the intent obvious and avoids off-by-one headaches.

### **5. Repeated peeling algorithms are satisfying.**  
Watching the onion layers disappear iteration by iteration feels almost like running a Conway’s Game of Life in reverse.

