#include <cs50.h>
#include <stdio.h>

// Methods
int get_int_length(long cred_num);
int get_first_two(long cred_num);
int get_first(long cred_num);
int calculate(long cred_num);

int main(void)
{
    long cred_num = get_long("Enter you credit card number: ");

    // Check if the credit card number is valid
    if (calculate(cred_num) % 10 != 0)
    {
        printf("INVALID\n");
    }
    // AMEX
    else if (get_int_length(cred_num) == 15 &&
             (get_first_two(cred_num) == 34 || get_first_two(cred_num) == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARD
    else if (get_int_length(cred_num) == 16 && get_first_two(cred_num) >= 51 &&
             get_first_two(cred_num) <= 55)
    {
        printf("MASTERCARD\n");
    }
    // VISA
    else if ((get_int_length(cred_num) == 16 || get_int_length(cred_num) == 13) &&
             get_first(cred_num) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Get Length Function
int get_int_length(long cred_num)
{
    // Handle negative numbers
    if (cred_num < 0)
    {
        return 0;
    }

    // 0 has a length of 1 digit
    if (cred_num == 0)
    {
        return 1;
    }

    int length = 0;
    while (cred_num > 0)
    {
        length++; // Number of integers in the number
        cred_num /= 10; // Reduce the number of integers by 1 after each addition
    }
    return length;
}

// Get Position Function
int get_first_two(long cred_num)
{
    // Will always just be 2 digits
    while (cred_num >= 100)
    {
        // Reduce the number of integers by 1 until 2 digits left
        cred_num /= 10;
    }
    return cred_num;
}

int get_first(long cred_num)
{
    // Will always just be 1 digit
    while (cred_num >= 10)
    {
        // Reduce the number of integers by 1 until 1 digit left
        cred_num /= 10;
    }
    return cred_num;
}

int calculate(long cred_num)
{

    int total_last = 0;
    int total_sec = 0;
    int final_sum = 0;

    while (cred_num > 0)
    {
        // Get the last digit and total it up
        int last_digit = cred_num % 10;
        total_last += last_digit;

        // Remove the last digit
        cred_num /= 10;

        // Check whether after removing the last digit, is a 0 or not
        if (cred_num > 0)
        {

            // Get the second last digit and multiply it by 2
            int sec_digit = cred_num % 10;
            int multi = sec_digit * 2;

            // If the result is 2 digits, add those digits
            if (multi >= 10)
            {
                multi = (multi / 10) + (multi % 10);
            }

            total_sec += multi;

            // Remove the second to last digit
            cred_num /= 10;
        }
    }
    final_sum = total_sec + total_last;
    return final_sum;
}
