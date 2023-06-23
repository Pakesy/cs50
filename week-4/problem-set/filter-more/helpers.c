#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute the average of the red, green, and blue components for each pixel
            int gray = (int)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 + 0.5);

            // Assign the computed average to each colour component of the pixel to create the grayscale effect
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage for the pixel during the swap process
    RGBTRIPLE temp;

    // Loop over each pixel in the image, only going up to the halfway point horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap each pixel with its horizontally reflected counterpart
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage for the new blurred image
    RGBTRIPLE temp[height][width];

    // Loop over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Variables for the total red, green and blue values, as well as a counter for the number of valid pixels
            int red = 0, green = 0, blue = 0, count = 0;

            // Loop over the pixel and its eight immediate neighbours
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // If the neighbour pixel is valid (i.e., within the image boundaries), add its color values to the total and
                    // increment the counter
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        red += image[k][l].rgbtRed;
                        green += image[k][l].rgbtGreen;
                        blue += image[k][l].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average colour value for each component and assign it to the corresponding pixel in the temporary image
            temp[i][j].rgbtRed = round((float) red / count);
            temp[i][j].rgbtGreen = round((float) green / count);
            temp[i][j].rgbtBlue = round((float) blue / count);
        }
    }

    // Replace the original image with the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage for the new image
    RGBTRIPLE temp[height][width];

    // Define Sobel filters
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize Sobel filter response for both filters and each colour channel
            float Gx_red = 0, Gx_green = 0, Gx_blue = 0;
            float Gy_red = 0, Gy_green = 0, Gy_blue = 0;

            // Loop over the filter size (3x3)
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // If the neighbour pixel is valid (i.e., within the image boundaries), apply the Sobel filter
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        // Multiply each neighbour pixel's colour value by the corresponding filter weight and add it to the total
                        // for both filters
                        Gx_red += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        Gx_green += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        Gx_blue += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];

                        Gy_red += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        Gy_green += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        Gy_blue += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            // Compute gradient strength for each colour channel by combining the Sobel filter responses
            int final_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int final_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int final_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap colour values at 255
            temp[i][j].rgbtRed = final_red > 255 ? 255 : final_red;
            temp[i][j].rgbtGreen = final_green > 255 ? 255 : final_green;
            temp[i][j].rgbtBlue = final_blue > 255 ? 255 : final_blue;
        }
    }

    // Replace the original image with the edge-detected image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}