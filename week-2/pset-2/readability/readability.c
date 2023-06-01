#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_score(string text);

int main(void)
{
    string test_text = get_string("Text: ");
    int score = calculate_score(test_text);

    if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (score > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", calculate_score(test_text));
    }

    return 0;
}

int count_letters(string text)
{
    int string_length = 0;
    int i = 0;

    while (text[i] != '\0')
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            string_length++;
        }

        i++;
    }

    return string_length;
}

int count_words(string text)
{
    int number_of_words = 1;
    int i = 0;

    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            number_of_words++;
        }

        i++;
    }

    return number_of_words;
}

int count_sentences(string text)
{
    int number_of_sentences = 0;
    int i = 0;

    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            number_of_sentences++;
        }

        i++;
    }

    return number_of_sentences;
}

int calculate_score(string text)
{
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = ((float)letters / (float)words * 100);
    float S = ((float)sentences / (float)words * 100);

    float calc = 0.0588 * L - 0.296 * S - 15.8;

    int score = round(calc);

    return score;
}