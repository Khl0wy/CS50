#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Method
int points (string word);

//Constant
const int alpha[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//Main
int main (void) {

    //Get input
    string player1 = get_string ("Player 1: ");
    string player2 = get_string ("Player 2: ");

    //Check points
    if (points(player1) > points(player2)) {
        printf ("Player 1 wins!\n");
    }
    else if (points(player2) > points(player1)) {
        printf ("Player 2 wins!\n");
    }
    else {
        printf("Tie!\n");
    }

}

//Points System Method
int points (string word) {
    int sum = 0;
    for (int i = 0, n = strlen (word); i < n; i++) {

        //If it's an alphabet, change to lower case; else don't do anything
        if (isalpha (word[i])) {
            char lower_char = tolower (word[i]);

            //Get the index of the respective array
            int index = lower_char - 'a';
            sum += alpha[index];
        }
    }
    return sum;
}
