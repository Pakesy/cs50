#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

// Function prototypes
int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
int check_filename(char *filename);

// Main function
int main(int argc, char *argv[])
{
    // Ensure there are enough arguments
    if (argc != 3)
    {
        printf("Usage ./reverse.c input.wav output.wav\n");
        return 1;
    }

    // Define input and output filenames
    char *input_name = argv[1];
    char *output_name = argv[2];

    // Check the file names are correct .wav files
    if (!check_filename(input_name) || !check_filename(output_name))
    {
        printf("Both files must end with .wav.\n");
        return 1;
    }

    // Open the input file for reading
    FILE *input_file = fopen(input_name, "r");
    if (input_file == NULL)
    {
        printf("Could not open the input file %s\n", input_name);
        return 1;
    }

    // Read the WAV file header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input_file);

    // Check the WAV format is correct
    if (!check_format(header))
    {
        printf("Invalid WAV format\n");
        return 1;
    }

    // Open the output file for writing
    FILE *output_file = fopen(output_name, "w");
    if (output_file == NULL)
    {
        printf("Could not open the output file %s\n", output_name);
        return 1;
    }

    // Write the header to the output file
    fwrite(&header, sizeof(WAVHEADER), 1, output_file);

    // Calculate the block size
    int block_size = get_block_size(header);
    unsigned char *sample = malloc(block_size);

    // Determine the start and end positions of the audio data
    long dataStartPos = sizeof(WAVHEADER);
    long dataEndPos = dataStartPos + header.subchunk2Size;
    int totalSamples = header.subchunk2Size / block_size;

    // Loop over each sample in reverse order
    for (int i = 0; i < totalSamples; i++)
    {
        fseek(input_file, dataEndPos - block_size * (i + 1), SEEK_SET);
        fread(sample, block_size, 1, input_file);
        fwrite(sample, block_size, 1, output_file);
    }

    // Clean up and close files
    free(sample);
    fclose(input_file);
    fclose(output_file);
    return 0;
}

// Function to check if the WAV format is correct
int check_format(WAVHEADER header)
{
    return strncmp((char *)header.format, "WAVE", 4) == 0 &&
           strncmp((char *)header.subchunk1ID, "fmt ", 4) == 0 &&
           strncmp((char *)header.subchunk2ID, "data", 4) == 0;
}

// Function to calculate the block size based on header data
int get_block_size(WAVHEADER header)
{
    return header.numChannels * header.bitsPerSample / 8;
}

// Function to check if the filename ends with .wav
int check_filename(char *filename)
{
    int length = strlen(filename);

    // Check if filename is too short to be a .wav
    if (length < 4)
    {
        return 0;
    }

    // Check if filename ends with .wav
    if (strcmp(&filename[length - 4], ".wav") != 0)
    {
        return 0;
    }

    return 1;
}