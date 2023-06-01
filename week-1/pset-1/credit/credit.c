#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function to perform the Luhn algorithm on the given credit card number
bool luhn(long num);

// Function to check the type of credit card based on the number
void checkCard(long num);

int main(void)
{
    // Prompt user for the credit card number
    long num = get_long("Number: ");

    // Perform Luhn algorithm and check the card type
    if (luhn(num))
    {
        checkCard(num);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Luhn algorithm implementation
bool luhn(long num)
{
    int length = 0;
    long temp = num;
    long digit;
    int count = 0;
    char numStr1[20]; // String to hold doubled digits
    char numStr2[20]; // String to hold remaining digits
    int index1 = 0;
    int index2 = 0;

    // Calculate the length of the number
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    temp = num; // Reset temp to the original number

    // Process each digit of the number
    while (temp > 0)
    {
        digit = temp % 10;
        temp /= 10;

        // Double every second digit and add to numStr1
        if (count % 2 == 1)
        {
            int doubledDigit = digit * 2;
            sprintf(numStr1 + index1, "%d", doubledDigit);
            index1 += strlen(numStr1 + index1);
        }
        // Add the remaining digits to numStr2
        else
        {
            sprintf(numStr2 + index2, "%ld", digit);
            index2 += strlen(numStr2 + index2);
        }

        count++;
    }

    numStr1[index1] = '\0';
    numStr2[index2] = '\0';

    int sum1;
    int sum2;

    // Calculate the sum of digits in numStr1
    for (int i = 0; numStr1[i] != '\0'; i++)
    {
        sum1 += numStr1[i] - '0';
    }

    // Calculate the sum of digits in numStr2
    for (int i = 0; numStr2[i] != '\0'; i++)
    {
        sum2 += numStr2[i] - '0';
    }

    // Check if the final sum ends in a 0
    if ((sum1 + sum2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check the type of credit card based on the number
void checkCard(long num)
{
    long firstTwoDigits = num;
    long temp1 = num;
    int length = 0;

    // Calculate the length of the number
    while (temp1 > 0)
    {
        temp1 /= 10;
        length++;
    }

    // Extract the first two digits
    while (firstTwoDigits > 100)
    {
        firstTwoDigits /= 10;
    }

    // Check the card type based on the first two digits and length
    if ((firstTwoDigits >= 40 && firstTwoDigits <= 42) && (length > 12 && length < 17))
    {
        printf("VISA\n");
    }
    else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && (length == 15))
    {
        printf("AMEX\n");
    }
    else if ((firstTwoDigits >= 51 && firstTwoDigits <= 55) && (length == 16))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
