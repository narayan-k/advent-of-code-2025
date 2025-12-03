#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000   // allow long lines
#define K 12               // number of digits to pick for part 2

/*
 * PART 1:
 * Choose the best two-digit number where digits must appear in order.
 */
int part1_process_line(const char *s) {
    int seen[10] = {0};
    int best = -1;

    for (int i = 0; s[i]; i++) {
        int d = s[i] - '0';
        if (d < 0 || d > 9) continue;

        for (int a = 9; a >= 0; a--) {
            if (seen[a]) {
                int val = a * 10 + d;
                if (val > best) best = val;
                break;
            }
        }
        seen[d] = 1;
    }
    return best;
}

/*
 * PART 2:
 * Select exactly K digits in left-to-right order to create
 * the lexicographically largest K-digit number.
 *
 * Standard greedy monotonic stack algorithm:
 *   - Keep dropping earlier digits if the new digit is larger,
 *     but only if we still have enough remaining digits to fill K.
 */
long long part2_process_line(const char *s) {
    int n = strlen(s);
    int to_pick = K;
    int stack_size = 0;
    char stack[K];

    for (int i = 0; i < n; i++) {
        char d = s[i];
        if (d < '0' || d > '9') continue;

        // While stack not empty and new digit is bigger than last kept digit,
        // AND we still have enough digits left to fill 12:
        while (stack_size > 0 &&
               d > stack[stack_size - 1] &&
               (n - i - 1) >= (to_pick - stack_size))
        {
            stack_size--;
        }

        // If we still need digits, push this one
        if (stack_size < to_pick) {
            stack[stack_size++] = d;
        }
    }

    // Convert 12-digit result into a long long
    long long result = 0;
    for (int i = 0; i < K; i++) {
        result = result * 10 + (stack[i] - '0');
    }
    return result;
}

int main(void) {
    static char line[MAX_LINE];
    long long total_part1 = 0;
    long long total_part2 = 0;

    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = '\0';

        // Skip empty lines
        if (line[0] == '\0')
            continue;

        // Compute both part results for this line
        int p1 = part1_process_line(line);
        long long p2 = part2_process_line(line);

        total_part1 += p1;
        total_part2 += p2;
    }

    printf("Part 1 total: %lld\n", total_part1);
    printf("Part 2 total: %lld\n", total_part2);
    return 0;
}
