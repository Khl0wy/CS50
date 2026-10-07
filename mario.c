#include <stdio.h>
#include <cs50.h>

int main (void) {

    int times;

    do {
        times = get_int ("Number of vertical bricks to form the pyramid (1-8): ");
    }
    while (times < 1 || times > 8);

    // Spaces > # > 2 Spaces > # [All runs as the column, multiple for loops under the row for loops = taking turns to print out the fixed output]
    // Number of rows
    for (int i = 0; i < times; i++) {
        // Number of spaces in a row
        for (int j = times; j > i+1; j--) {
            printf (" ");
        }
        // Prints the first pyramid
        for (int j = 0; j <= i; j++) {
            printf ("#");
        }
        // Print 2 spaces after finishing the first pyramid
            printf ("  ");
        // Print the second pyramid
        for (int j = 0; j <= i; j++) {
            printf ("#");
        }
        // Move to next row after completing the previous row
        printf ("\n");
    }
}
