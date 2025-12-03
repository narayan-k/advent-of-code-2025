use std::ops::RangeInclusive;

/// Advent of Code 2025 — Day 2
///
/// Input is stored in `input.txt` (in the same folder as main.rs).
/// It consists of comma-separated numeric ranges like:
///
///     11-22,95-115,998-1012,...
///
/// We must scan every ID in these ranges and detect which ones are "invalid"
/// according to two different definitions:
///
/// Part 1: An ID is invalid if it is exactly **two copies** of the same digit sequence (YY).
/// Example: 11, 55, 6464, 123123.
///
/// Part 2: An ID is invalid if it is **two or more copies** of the same digit sequence.
/// Example: 111, 121212, 123123123, 565656, etc.
///
/// The program outputs the sum of Part 1 invalid IDs and the sum of Part 2 invalid IDs.

const INPUT: &str = include_str!("input.txt");

fn main() {
    let input = INPUT.trim();
    let ranges = parse_ranges(input);

    let mut sum_part1: u64 = 0;
    let mut sum_part2: u64 = 0;

    for range in ranges {
        for id in range {
            if is_invalid_id_part1(id) {
                sum_part1 += id;
            }
            if is_invalid_id_part2(id) {
                sum_part2 += id;
            }
        }
    }

    println!("Sum of invalid IDs (Part 1) = {}", sum_part1);
    println!("Sum of invalid IDs (Part 2) = {}", sum_part2);
}

// ---------------------------------------------------------
// Parsing
// ---------------------------------------------------------

/// Parse ranges of the form "A-B,C-D,..." into a Vec<RangeInclusive<u64>>.
///
/// Example:
/// "11-22,95-115" → vec![11..=22, 95..=115]
fn parse_ranges(input: &str) -> Vec<RangeInclusive<u64>> {
    input
        .split(',')
        .filter(|s| !s.trim().is_empty())
        .map(|part| {
            let (start, end) = part.trim().split_once('-').expect("Invalid range format");
            let a = start.parse::<u64>().unwrap();
            let b = end.parse::<u64>().unwrap();
            a..=b
        })
        .collect()
}

// ---------------------------------------------------------
// Invalid ID checks (Part 1)
// ---------------------------------------------------------

/// Part 1 definition:
///
/// An ID is invalid only if:
/// - It has an even number of digits
/// - The first half is identical to the second half
///
/// Examples:
/// - 11 (1|1)
/// - 22 (2|2)
/// - 6464 (64|64)
/// - 123123 (123|123)
///
/// Rejects anything that isn't exactly YY.
fn is_invalid_id_part1(id: u64) -> bool {
    let s = id.to_string();
    let len = s.len();

    // Must be divisible into two equal parts
    if len % 2 != 0 {
        return false;
    }

    let half = len / 2;
    let first = &s[..half];
    let second = &s[half..];

    first == second
}

// ---------------------------------------------------------
// Invalid ID checks (Part 2)
// ---------------------------------------------------------

/// Part 2 definition:
///
/// An ID is invalid if it consists of **any block of digits** repeated
/// **two or more times**.
///
/// Examples:
/// - "11"          → "1" repeated twice
/// - "111"         → "1" repeated three times
/// - "565656"      → "56" repeated three times
/// - "1212121212"  → "12" repeated five times
/// - "123123123"   → "123" repeated three times
///
/// Approach:
/// Try every possible block size that divides the total length.
/// If repeating that block reconstructs the full string, it's invalid.
fn is_invalid_id_part2(id: u64) -> bool {
    let s = id.to_string();
    let len = s.len();

    // Try each possible block size (1 digit, 2 digits, ... up to half length)
    for block_size in 1..=len / 2 {
        // Length must be divisible by block_size
        if len % block_size != 0 {
            continue;
        }

        let repeats = len / block_size;

        // Must be at least two repeats
        if repeats < 2 {
            continue;
        }

        let block = &s[..block_size];

        // If repeating the block forms the ID, it's invalid
        if s == block.repeat(repeats) {
            return true;
        }
    }

    false
}
