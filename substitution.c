#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//Method
string crypto (string plaintext, string substitution);

//Command-line argument
int main (int argc, string argv[]) {
    //Check if input more than one word; argc = 1 (The name of the file ./substitution), argc = 2 (The file name and the user input)
    if (argc != 2) {
        printf ("Usage: ./substituition key\n");
        return 1;
    }

    //Check if the word contains exactly 26 characters
    if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check double characters and aplhabetical characters
    for (int i = 0; i < 26; i++) { //Run through all 26 characters
        //Check whether it's an alphabetical character
        if (!isalpha(argv[1][i])) { //argv[0] - first position is always the file name; argv[1] is the user input
                                    //the second[] is because argv[1] is a string and I'm trying to
                                    //get the position of each character in the string (An array in an array)
            printf("Key must contain only alphabetical characters.\n");
            return 1;
        }
            //Check for duplication
            for (int j = i + 1; j < 26; j++) { //Always checking the next alphabet, that's why j = i + 1
                if (tolower(argv[1][i]) == tolower(argv[1][j])) { //Standardise everything to lower case for easier comparison
                    printf("Key must not contain duplicate characters.\n");
                    return 1;
            }
        }
    }

    //If everything is correct, then execute
    string plaintext = get_string ("plaintext: ");
      printf ("ciphertext: %s\n", crypto(plaintext, argv[1])); //Passes in the user's plaintext and the substitution
      return 0;
}

string crypto (string plaintext, string substitution) {
    string cipher = plaintext;
    int index;

    //Run through each character in the plaintext
    for (int i = 0; i < strlen(plaintext); i++) {
        //Check if it's an alphabet
        if (isalpha(plaintext[i])) {
            //Check if it's an uppercase alphabet for plaintext
            if (isupper(plaintext[i])) {
                index = plaintext[i] - 'A'; //Get the index/position of the substitution
                cipher[i] = toupper(substitution[index]); //Since the character of the plaintext is an uppercase, will capitalise it
            }
            else {
                //Lowercase alphabet for plaintext
                index = plaintext[i] - 'a'; //Get the index/position of the substitution
                cipher[i] = tolower(substitution[index]); //Since the character of the plaintext is a lowercase, will capitalise
            }
        }
        //Just straight copy, if it's not an alphabet
        else {
            cipher[i] = plaintext[i];
        }
    }

    return cipher;
}
