import { readFileSync } from "fs";

const input = readFileSync("input.txt", "utf8").trim();


/**
 * Advent of Code 2025 — Day 1
 *
 * Part 1:
 *   - You rotate a dial starting at position 50.
 *   - Each instruction is `Lx` (left) or `Rx` (right).
 *   - Rotations are circular on a dial numbered 0–99.
 *   - Count the number of times the dial *ends a rotation* on 0.
 *
 * Part 2:
 *   - Same instructions, but now count *every individual click*
 *     that lands on 0, not just the final position of each rotation.
 */

// ------------------------------------------------------------
// Part 1: Count times the dial *ends* on 0
// ------------------------------------------------------------

/**
 * Simulate the dial following the input instructions.
 *
 * @param {string} input - Raw puzzle input, one rotation per line.
 * @returns {number} How many times the dial ends on zero.
 */
function solve(input) {
    const lines = input.split(/\r?\n/);
    let position = 50;  // Dial starts here
    let countZero = 0;

    for (const line of lines) {
        const dir = line[0];              // 'L' or 'R'
        const dist = parseInt(line.slice(1), 10); // rotation distance

        // Apply rotation in bulk
        if (dir === "R") {
            position = (position + dist) % 100;
        } else {
            position = (position - dist) % 100;
            if (position < 0) position += 100;
        }

        // Count only final positions landing on 0
        if (position === 0) countZero++;
    }

    return countZero;
}

console.log("Password (Part 1):", solve(input));


// ------------------------------------------------------------
// Part 2: Count *every click* that lands on 0
// ------------------------------------------------------------

/**
 * Simulates the dial one click at a time.
 *
 * For each instruction:
 *   - Rotate by dist steps, clicking the dial each time.
 *   - Count every time a click lands on 0,
 *     even if the rotation doesn't end on zero.
 *
 * @param {string} input - Puzzle input
 * @returns {number} How many times the dial points at zero during all clicks
 */
function solvePartTwo(input) {
    const lines = input.split(/\r?\n/);

    let position = 50;  // Starting point
    let countZero = 0;

    for (const line of lines) {
        const dir = line[0];
        const dist = parseInt(line.slice(1), 10);

        // One-click-at-a-time simulation
        for (let i = 0; i < dist; i++) {
            if (dir === "R") {
                position = (position + 1) % 100;
            } else {
                position = (position - 1 + 100) % 100;
            }

            // Count every click landing on 0
            if (position === 0) countZero++;
        }
    }

    return countZero;
}

console.log("Password (Part 2):", solvePartTwo(input));


// ------------------------------------------------------------
// End of File
// ------------------------------------------------------------
