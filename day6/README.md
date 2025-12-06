# 🎄 Advent of Code 2025 — Day 6  
### Language: **Go** 🐹

Today’s puzzle took a left turn straight into a garbage compactor — both narratively *and* conceptually. What looked like a simple column of numbers turned out to be a tricksy optical illusion of horizontally stacked mini-problems where spacing (yes, literal spaces) determined everything.

And then Part Two?  
**Cephalopod math. Vertical. Right-to-left-but-also-left-to-right. Sure. Why not.**

Welcome to Day 6. 😅

---

## 🧩 Problem Summary

The input is essentially a giant *spreadsheet laid on its side*:

- Each **problem** is a *vertical block* of columns.
- Inside each block:
  - Part 1: numbers are written **horizontally**.
  - Part 2: numbers are written **vertically** (one digit per row).
- The bottom row contains the **operator** (`+` or `*`) for that problem.
- A problem ends when you hit a column that is **all spaces** — that column is a separator.

Your job:  
1. Identify each problem block.  
2. Parse the numbers inside it.  
3. Apply the operator.  
4. Add all results together.  
5. Also: repeat everything with a completely different number system in Part 2. 🙃

---

## ⭐ Part 1 — Horizontal Numbers, Vertical Blocks

For Part One, each problem works like this:

```
5973
6499
4319
8513
*
```

Numbers are “normal” — read left-to-right per row.

The challenges:

### 🔹 1. Lines are not the same width  
Lots of ragged spacing → so everything must be padded before indexing.

### 🔹 2. Problems are separated by **empty columns**  
A column full of `' '` means “new problem starts after this”.

### 🔹 3. Numbers can overlap block boundaries  
A number belongs to a block if its digit span overlaps the block’s column range.

Once numbers per block are collected, apply the operator and accumulate the grand total.

---

## ⭐ Part 2 — Cephalopod Math (Vertical Numbers!)

This is where the puzzle takes a wonderfully chaotic turn.

Inside each block:

- **Each column is actually one number**
- Digits appear **top to bottom**  
- Spaces are ignored  
- Columns are read **left → right** to form the number sequence  
- The operator stays the same

Example:

```
C0 C1 C2
1  2  3
4  5
6
*
```

Becomes:

- Column 0 → `"146"`  
- Column 1 → `"25"`  
- Column 2 → `"3"`  
→ Evaluate: `146 * 25 * 3`

This reinterpretation completely changes all answers — and makes Part Two feel like solving a *second puzzle on top of the first*.

---

# 🛠️ How I Solved It in Go

Today’s puzzle was an amazing crash course in Go’s strengths (and quirks).

### 🔧 1. Preprocessing: Pad all lines  
Go panics hilariously fast when you try to index past the end of a string.  
Padding prevents 90% of bugs.

### 🔧 2. Separator detection  
A column is a separator if *every row*, including the operator row, is `' '`.

This gave clean, reliable block boundaries like:

```
[0,4), [5,9), [10,14), ...
```

### 🔧 3. Part 1: Regex-extract horizontal numbers  
Go’s `regexp` library is fast enough here.  
Just scan each row (except the operator row) and collect digit spans.

### 🔧 4. Part 2: Build numbers vertically  
This was the fun part:

```go
var digits strings.Builder
for row := 0; row < H-1; row++ {
    ch := lines[row][col]
    if isDigit(ch) {
        digits.WriteByte(ch)
    }
}
```

Each column → one number.  
Columns → ordered sequence.  
Operator → applied straight through.

### 🔧 5. Evaluate blocks  
Go’s straightforward loops make the math tidy and predictable.

---

# 🧠 What I Learned Today

### 1. Parsing by *columns* is surprisingly hard  
Especially when whitespace carries structural meaning.

### 2. Go indexing requires discipline  
Off-by-one?  
Panics.  
Ragged lines?  
Panics.  
Under-caffeinated developer?  
Also panics.

Padding everything was the simplest and best solution.

### 3. Two number systems, one input  
This puzzle forced me to treat the same text layout through completely different semantic lenses — a neat exercise in data reinterpretation.

### 4. Go is fantastic for systematic text processing  
Buffers, slices, and builders make it really satisfying once the structure is right.

### 5. Debug output is your friend  
The journey to the final solution involved… a lot of panicking columns, overlapping spans, misaligned operators, and cephalopod-based misunderstandings.  
Instrumenting the parser saved the day.

