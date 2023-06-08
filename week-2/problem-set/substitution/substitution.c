#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constants
const int nums = 26;
const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char substitution(char character, string key);

int main(int argc, string argv[])
{

    string key = argv[1];

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(key) != nums)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (!(key[i] >= 'a' && key[i] <= 'z' || key[i] >= 'A' && key[i] <= 'Z'))
        {
            printf("Key must only contain alphanumeric characters.\n");
            return 1;
        }
    }

    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = (i + 1); j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain any duplicates.\n");
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext: ");

    int plaintextLength = strlen(plaintext);
    char ciphertext[plaintextLength + 1]; // Array to store the ciphertext

    for (int i = 0; i < plaintextLength; i++)
    {
        ciphertext[i] = substitution(plaintext[i], key);
    }

    ciphertext[plaintextLength] = '\0';

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

char substitution(char character, char key[])
{
    if (isupper(character))
    {
        int position = character - 'A';
        return toupper(key[position]);
    }
    else if (islower(character))
    {
        int position = character - 'a';
        return tolower(key[position]);
    }
    else
    {
        return character;
    }
}