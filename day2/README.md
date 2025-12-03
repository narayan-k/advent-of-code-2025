# 🎄 Advent of Code 2025 — Day 2  
### Language: **Rust** 🦀

Today’s puzzle dives deep into **pattern detection**, **number theory**, and my ongoing war with Rust's borrow checker (which I’m convinced is gaining sentience).

The input:  
A long list of **numeric ID ranges**, like:

```
11-22,95-115,998-1012,...
```

The goal: scan **every ID in every range** and determine which ones are “invalid” by two increasingly cursed definitions.

---

## 🧩 Problem Summary

You’re given comma-separated ranges like:

```
11-22,95-115
```

Which means:  
Check **every ID** in those ranges:

```
11,12,13,...,22,95,96,...,115
```

You must detect “invalid IDs” based on repeating digit patterns.

---

## ⭐ Part 1  
An ID is invalid if it is **exactly two copies** of the same digit sequence:

Examples:

- `11` → "1" + "1"
- `55`
- `6464` → "64" + "64"
- `123123` → "123" + "123"

Rules:

- Must have an **even number** of digits  
- First half must equal second half  
- Nothing fancy — only **exactly two copies** (YY)

Think of it as:  
> “Is this number a perfect double?”

---

## ⭐ Part 2  
Now things get unhinged.  
An ID is invalid if it is **two or more repeats** of *any* digit block.

Examples:

- `"11"` → "1" repeated twice  
- `"111"` → "1" repeated three times  
- `"565656"` → "56" repeated three times  
- `"123123123"` → "123" repeated three times  
- `"1212121212"` → "12" repeated five times  

If it’s **block repeated block repeated block...**, it's invalid.

You try:

- Block size 1  
- Block size 2  
- Block size 3  
- … up to half the digit length  

If repeating that block reconstructs the whole number?  
❌ Invalid.

---

## 📝 What I Learned Today

- Rust’s string slicing rules are strict, but that’s probably for my own safety.  
- Pattern detection becomes way easier when you transform everything into strings.  
- Repeating strings in Rust with `.repeat()` is strangely satisfying.  
- Rust is incredible for writing fast scanners over numeric ranges. 