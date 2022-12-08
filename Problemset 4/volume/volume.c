// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // changed "w" to "a" to allow header not to be overwritten by samples
    FILE *output = fopen(argv[2], "a");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // read input header to an array
    uint8_t *headerArray = malloc(sizeof(uint8_t) * 44);
    fread(headerArray, sizeof(uint8_t), 44, input);
    fwrite(headerArray, sizeof(uint8_t), 44, output);
    free(headerArray);

    // TODO: Read samples from input file and write updated data to output file
    int16_t sampleBuffer;
    while (fread(&sampleBuffer, sizeof(int16_t), 1, input) != 0)
    {
        sampleBuffer = (int16_t)(sampleBuffer * factor);
        fwrite(&sampleBuffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
