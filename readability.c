#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    //Get input text
    string sentence = get_string ("Text: ");

    //Initiate the varaiables
    int length = strlen (sentence);
    int letters = 0;
    int words = 0;
    int sentences = 0;

    //Check for each letter, word and sentence)
    for (int i = 0; i < length; i++) {

        //Number of alphabetical characters
        if (isalpha(sentence[i])) {
            letters++;
        }

        //Number of words
        if (sentence[i] == ' ') {
            words++;
        }

        //Number of sentences
        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'){
            sentences++;
        }
    }

    //If the text isn't an empty text, will add 1 word by default as word count is through spaces and the last word doesn't come with a space
     if (length > 0) {
        words++;
    }

    //Calculate the average number of letters per 100 words in the text (L), and the average number of sentences per 100 words in the text (S).
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;

    //Calculate the index (rounding the index)
    int index = round (0.0588 * L - 0.296 * S - 15.8);

    //Print the output based on the index
    if (index < 1) {
        printf ("Before Grade 1\n");
    }
    else if (index >= 16) {
        printf ("Grade 16+\n");
    }
    else {
        printf ("Grade %i\n", index);
    }
}
