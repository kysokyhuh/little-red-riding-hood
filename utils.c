#include <stdio.h>
#include "headers/utils.h"

void waitForEnter(void) {
    printf("   Press ENTER to continue…");
    while (getchar() != '\n')
        ;  // consume until newline
}

void printStats(int moves, int senses, int rotates,
                int fx, int fy, int fm,
                int bx, int by, int bm,
                int wx, int wy, int wm)
{
    // Top‐line summary
    printf("Stats: Moves=%-3d  Senses=%c   Rotates=%-3d\n",
           moves,
           (senses == '\n' ? 'n' : senses), // safe-print
           rotates);

    // Helper macro to print one pickup line
    #define P_LINE(label, X, Y, M) \
        printf("   %-9s: (%2d,%2d) @ move %-3d\n", label, X, Y, M)

    if (fx >= 0)   P_LINE("Flower",    fx+1, fy+1, fm);
    else           printf("   %-9s: not yet picked\n", "Flower");

    if (bx >= 0)   P_LINE("Bread",     bx+1, by+1, bm);
    else           printf("   %-9s: not yet picked\n", "Bread");

    if (wx >= 0)   P_LINE("Woodsman",  wx+1, wy+1, wm);
    else           printf("   %-9s: not yet picked\n", "Woodsman");

    #undef P_LINE

    putchar('\n');
}

void displayResult(int bread, int flower, int hasWoodsman) {
    puts("GAME OVER");
    if (bread && flower && hasWoodsman) {
        puts("  You reached Granny fully prepared. YOU WIN!");
    } else {
        puts("  LRRH did not meet all requirements. YOU LOSE.");
        if (!bread)       puts("   - Missing: Bread");
        if (!flower)      puts("   - Missing: Flower");
        if (!hasWoodsman) puts("   - Missing: Woodsman");
    }
    putchar('\n');
}
