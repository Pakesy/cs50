#include <cs50.h>
#include <stdio.h>

void pyramid(int size);
void clearInputBuffer();

int main(void)
{
    int height;
    printf("Height: ");
    while (scanf("%d", &height) != 1 || height < 1 || height > 8)
    {
        clearInputBuffer();
        printf("Height: ");
    }

    pyramid(height);

    return 0;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void pyramid(int size)
{
    for (int i = 1; i <= size; i++)
    {
        // Print spaces for the left side of the pyramid
        for (int j = size - i; j > 0; j--)
        {
            printf(" ");
        }

        // Print # symbols for the left side of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print spacing between the two sides of the pyramid
        printf("  ");

        // Print # symbols for the right side of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Move to the next line for the next row
        printf("\n");
    }
}
