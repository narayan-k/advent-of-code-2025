# Day 4 — Printing Department  
### Fully Documented Nim Solution

# Advent of Code 2025 — Day 4
# Language: Nim
#
# Problem Summary:
# ----------------
# We are given a 2D grid containing:
#   '@' — a roll of paper
#   '.' — empty space
#
# Forklifts can only access a roll if it has *fewer than four* rolls of paper
# in the eight adjacent directions (N, NE, E, SE, S, SW, W, NW).
#
# Part 1:
#   Count how many rolls are initially accessible.
#
# Part 2:
#   Repeatedly remove all currently accessible rolls.
#   Every removal may expose new accessible rolls.
#   Continue until no accessible rolls remain.
#
# Input is read from stdin, and the final answers for my puzzle input are:
#   Part 1: 1460 rolls accessible
#   Part 2: 9243 rolls removed after full cascading removal.
#
# This script solves both parts.


import std/[strutils, sequtils]

# ------------------------------------------------------------
# Load and prepare the grid
# ------------------------------------------------------------

# Read full input from standard input.
let input = readAll(stdin)

# Split input into lines and discard any empty lines.
# Each line is a string representing one row of the paper grid.
var grid = input.splitLines().filterIt(it.len > 0)

# Grid dimensions.
let h = grid.len       # number of rows
let w = grid[0].len    # number of columns

# Directions representing the 8 neighbors around a cell.
# (dy, dx) pairs:
let dirs = [
  (-1, -1), (-1, 0), (-1, 1),
  ( 0, -1),          ( 0, 1),
  ( 1, -1), ( 1, 0), ( 1, 1),
]

# ------------------------------------------------------------
# Helper: Count number of '@' neighbors around (y, x)
# ------------------------------------------------------------

proc neighbors(y, x: int): int =
  ## Counts how many adjacent cells around (y, x) contain '@'.
  ## Considers all 8 directions. Ensures bounds checking.
  var c = 0
  for (dy, dx) in dirs:
    let ny = y + dy
    let nx = x + dx
    # Ignore out-of-bounds coordinates
    if ny >= 0 and ny < h and nx >= 0 and nx < w:
      if grid[ny][nx] == '@':
        c.inc()
  return c

# ------------------------------------------------------------
# Part 1 — Count all initially accessible rolls
# ------------------------------------------------------------

var part1 = 0

# Scan every cell in the grid.
for y in 0..<h:
  for x in 0..<w:
    # A roll is accessible if it's '@' and it has < 4 neighbors.
    if grid[y][x] == '@' and neighbors(y, x) < 4:
      part1.inc()

# ------------------------------------------------------------
# Part 2 — Cascading removal of rolls
# ------------------------------------------------------------
#
# Process:
#   while true:
#     find all '@' with < 4 neighbors
#     if none found, stop
#     remove all found rolls
#
# Track total number of removed rolls.
# ------------------------------------------------------------

var removedTotal = 0

while true:
  # Collect all rolls that should be removed in this round.
  var toRemove: seq[(int, int)] = @[]

  for y in 0..<h:
    for x in 0..<w:
      if grid[y][x] == '@' and neighbors(y, x) < 4:
        toRemove.add((y, x))

  # If no rolls are accessible, stop the entire process.
  if toRemove.len == 0:
    break

  # Remove all accessible rolls simultaneously.
  # They become '.' (empty space).
  for (y, x) in toRemove:
    grid[y][x] = '.'

  # Add count of this wave of removals.
  removedTotal += toRemove.len

# ------------------------------------------------------------
# Output results
# ------------------------------------------------------------

echo "Part 1: ", part1
echo "Part 2: ", removedTotal
