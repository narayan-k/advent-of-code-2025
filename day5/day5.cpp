/*
    Advent of Code – Day 5: Cafeteria
    ---------------------------------
    This program solves BOTH Part One and Part Two.

    INPUT FORMAT:
    - A list of fresh ingredient ID ranges (one per line), formatted as "A-B".
    - A blank line.
    - A list of available ingredient IDs (Part One only).

    PART ONE:
    Count how many of the available ingredient IDs fall within ANY fresh range.
    Ranges may overlap; IDs are fresh if they fall into at least one range.

    PART TWO:
    Ignore the available ingredient list.
    Count how many TOTAL ingredient IDs are covered by the fresh ranges.
    This is the total size of the union of all ranges.

    APPROACH:
      1. Read all ranges.
      2. Sort ranges.
      3. Merge overlapping or adjacent ranges.
         Example: [10,14], [12,18], [16,20] → merged into [10,20]
      4. PART ONE: For each ID, binary-search to see if it lies inside any merged range.
      5. PART TWO: Sum the size of all merged ranges:
            sum += (end - start + 1)

    This results in:
      - O(R log R) for sorting/merging ranges
      - O(I log R) for checking IDs
      - Very fast even for large puzzle inputs.

    COMPILING (macOS / Linux):
        g++ -std=c++17 -O2 day5.cpp -o day5

    RUN:
        ./day5 < input.txt
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<long long, long long>> ranges;  // stores raw ranges
    vector<long long> ids;                      // available IDs (Part 1 only)
    string line;

    // ---------------------------------------------------------------------
    // STEP 1: Read all ranges until a blank line.
    // ---------------------------------------------------------------------
    while (getline(cin, line)) {
        if (line.empty())
            break;  // blank line marks end of range list

        long long a, b;
        char dash;
        stringstream ss(line);
        ss >> a >> dash >> b;  // parse "A-B"

        ranges.push_back({a, b});
    }

    // ---------------------------------------------------------------------
    // STEP 2: Read all ingredient IDs (Part One only).
    // If Part Two only were needed, we would skip this section.
    // ---------------------------------------------------------------------
    while (getline(cin, line)) {
        if (line.empty())
            continue;  // ignore blank lines in second half
        ids.push_back(stoll(line));
    }

    // ---------------------------------------------------------------------
    // STEP 3: Sort ranges by start value, required for merging.
    // ---------------------------------------------------------------------
    sort(ranges.begin(), ranges.end());

    // ---------------------------------------------------------------------
    // STEP 4: Merge overlapping or adjacent ranges.
    //
    // After this, "merged" contains NON-OVERLAPPING intervals.
    // Example:
    //   Input:  [3,5], [10,14], [12,18], [16,20]
    //   Merged: [3,5], [10,20]
    // ---------------------------------------------------------------------
    vector<pair<long long, long long>> merged;

    for (auto &r : ranges) {
        // Case 1: merged list is empty OR no overlap with the last merged range
        if (merged.empty() || r.first > merged.back().second + 1) {
            merged.push_back(r);
        }
        // Case 2: there IS overlap → extend the last merged interval
        else {
            merged.back().second = max(merged.back().second, r.second);
        }
    }

    // ---------------------------------------------------------------------
    // STEP 5: PART ONE — Count how many available IDs are fresh.
    //
    // We use binary search over merged ranges because they are sorted
    // and non-overlapping.
    // ---------------------------------------------------------------------
    int freshPart1 = 0;

    for (long long id : ids) {
        int left = 0;
        int right = merged.size() - 1;
        bool fresh = false;

        while (left <= right) {
            int mid = (left + right) / 2;

            // If the ID is >= start of middle range
            if (merged[mid].first <= id) {
                // And ID <= end → ID is fresh
                if (id <= merged[mid].second) {
                    fresh = true;
                    break;
                }
                // Else search to the right
                left = mid + 1;
            }
            else {
                // ID < range start → search left half
                right = mid - 1;
            }
        }

        if (fresh)
            freshPart1++;
    }

    // ---------------------------------------------------------------------
    // STEP 6: PART TWO — Count how many total IDs are covered by the ranges.
    //
    // Since merged ranges are disjoint:
    //     total += (end - start + 1)
    //
    // Example:
    //   [3,5] → 3 values
    //   [10,20] → 11 values
    //   Total = 14
    // ---------------------------------------------------------------------
    long long freshPart2 = 0;

    for (auto &r : merged) {
        freshPart2 += (r.second - r.first + 1);
    }

    // ---------------------------------------------------------------------
    // STEP 7: Output results.
    // ---------------------------------------------------------------------
    cout << "Part 1: " << freshPart1 << "\n";
    cout << "Part 2: " << freshPart2 << "\n";

    return 0;
}
