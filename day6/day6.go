package main

import (
    "bufio"
    "fmt"
    "os"
    "regexp"
    "strconv"
    "strings"
)

/*
    Advent of Code 2024 — Day 6
    ----------------------------

    The worksheet consists of many math problems placed horizontally.
    Each problem is a "block" of columns containing numbers stacked vertically,
    with a single operator (+ or *) in the bottom row.

    Problems are separated by *separator columns*, which are columns that contain
    ONLY spaces across *every* row, including the operator row.

    Part 1:
      - Each number inside a block is written horizontally.
      - A block may contain many horizontal numbers (one per row).
      - All numbers belonging to the block share overlapping column ranges.
      - Apply the operator to all collected numbers.

    Part 2:
      - Numbers are written vertically.
      - Each *column* in the block corresponds to one number.
      - Digits are stacked top-to-bottom, MSB at top.
      - Skip spaces; digits concatenate to form the number.
      - Evaluate numbers left→right inside the block.

    This program solves BOTH parts efficiently and clearly.
*/

type NumSpan struct {
    start int // inclusive column index where number begins
    end   int // exclusive column index where number ends
    value int // parsed integer value
}

func main() {

    // ============================================================
    // STEP 0 — Load all input lines and pad them to equal width
    // ============================================================
    var raw []string
    scanner := bufio.NewScanner(os.Stdin)
    for scanner.Scan() {
        raw = append(raw, scanner.Text())
    }

    // Compute maximum observed line width so we can pad all rows.
    maxW := 0
    for _, ln := range raw {
        if len(ln) > maxW {
            maxW = len(ln)
        }
    }

    // Pad all lines to same width for safe column indexing.
    lines := make([]string, len(raw))
    for i, ln := range raw {
        if len(ln) < maxW {
            ln += strings.Repeat(" ", maxW-len(ln))
        }
        lines[i] = ln
    }

    H := len(lines)     // number of rows
    W := maxW           // fixed width of each row after padding
    opRow := lines[H-1] // last row contains operators (+ or *)

    // ============================================================
    // STEP 1 — Determine separator columns
    // ============================================================
    /*
        A separator column is defined as:
        A column where EVERY row contains a space character ' '.

        Such columns separate problems. Any contiguous region of
        non-separator columns forms a "block" representing one problem.
    */
    separator := make([]bool, W)

    for col := 0; col < W; col++ {
        allSpace := true
        for row := 0; row < H; row++ {
            if lines[row][col] != ' ' {
                allSpace = false
                break
            }
        }
        separator[col] = allSpace
    }

    // ============================================================
    // STEP 2 — Group contiguous non-separator columns into blocks
    // ============================================================
    /*
        Example:
            Columns: 012345678901234
                      5973␣7497␣845␣23␣...
                    Separator columns: 4, 9, 13, ...
            → Blocks might be:
                [0,4), [5,9), [10,13), [14, ...]

        Each block corresponds to one distinct math problem.
    */
    var blocks [][2]int
    inBlock := false
    start := 0

    for col := 0; col < W; col++ {
        if !separator[col] && !inBlock {
            inBlock = true
            start = col
        }
        if separator[col] && inBlock {
            inBlock = false
            blocks = append(blocks, [2]int{start, col})
        }
    }
    if inBlock {
        blocks = append(blocks, [2]int{start, W})
    }

    // ============================================================
    // STEP 3 — Pre-extract horizontal numbers for Part 1
    // ============================================================
    /*
        For Part 1, numbers are written horizontally.
        We detect all digit spans in each row (except operator row),
        store their start/end column ranges, and parse their integer values.
    */
    re := regexp.MustCompile(`\d+`)
    allRows := make([][]NumSpan, H-1)

    for r := 0; r < H-1; r++ {
        matches := re.FindAllStringIndex(lines[r], -1)
        for _, m := range matches {
            val, _ := strconv.Atoi(lines[r][m[0]:m[1]])
            allRows[r] = append(allRows[r], NumSpan{
                start: m[0],
                end:   m[1],
                value: val,
            })
        }
    }

    // ============================================================
    // PART 1 — Solve using horizontal numbers
    // ============================================================
    grand1 := 0

    for _, blk := range blocks {
        left, right := blk[0], blk[1]

        // Find the block's operation symbol in the operator row.
        var op byte
        for c := left; c < right; c++ {
            if opRow[c] == '+' || opRow[c] == '*' {
                op = opRow[c]
                break
            }
        }

        // Collect horizontal numbers whose spans overlap the block.
        var nums []int
        for r := 0; r < H-1; r++ {
            for _, sp := range allRows[r] {
                if sp.start < right && sp.end > left {
                    nums = append(nums, sp.value)
                }
            }
        }

        if len(nums) == 0 {
            continue
        }

        // Evaluate the problem.
        res := nums[0]
        if op == '+' {
            for i := 1; i < len(nums); i++ {
                res += nums[i]
            }
        } else { // '*'
            for i := 1; i < len(nums); i++ {
                res *= nums[i]
            }
        }

        grand1 += res
    }

    // ============================================================
    // PART 2 — Solve using vertical cephalopod numbers
    // ============================================================
    /*
        In Part 2:

        - Each column inside a block corresponds to ONE number.
        - Numbers are read vertically top-to-bottom.
        - Digits (0–9) are collected; spaces are ignored.
        - Columns are processed left→right, forming number sequence.

        Example:

             C0 C1 C2
        R0:   3  5  6
        R1:   2  4
        R2:   1

        Column 0 → "321" → number 321
        Column 1 → "54"  → number 54
        Column 2 → "6"   → number 6
    */
    grand2 := 0

    for _, blk := range blocks {
        left, right := blk[0], blk[1]

        // Find block operator.
        var op byte
        for c := left; c < right; c++ {
            if opRow[c] == '+' || opRow[c] == '*' {
                op = opRow[c]
                break
            }
        }

        // Build numbers one column at a time.
        var nums []int

        for col := left; col < right; col++ {
            var digits strings.Builder

            for row := 0; row < H-1; row++ {
                ch := lines[row][col]
                if ch >= '0' && ch <= '9' {
                    digits.WriteByte(ch)
                }
            }

            if digits.Len() > 0 {
                val, _ := strconv.Atoi(digits.String())
                nums = append(nums, val)
            }
        }

        if len(nums) == 0 {
            continue
        }

        // Evaluate problem vertically.
        res := nums[0]
        if op == '+' {
            for i := 1; i < len(nums); i++ {
                res += nums[i]
            }
        } else {
            for i := 1; i < len(nums); i++ {
                res *= nums[i]
            }
        }

        grand2 += res
    }

    // ============================================================
    // OUTPUT RESULTS
    // ============================================================
    fmt.Println("Part 1:", grand1)
    fmt.Println("Part 2:", grand2)
}
