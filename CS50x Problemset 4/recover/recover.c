#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check if only one command line argument given
    if (argc != 2)
    {
        printf("Only one command line argument allowed! Only sd-card image\n");
        return 1;
    }

    // Open file and return error if not able to open
    FILE *sdcard = fopen("card.raw", "r");
    if (sdcard == NULL)
    {
        printf("Could not open file!\n");
        return 1;
    }

    // jpg counter and name source
    int jpgCounter = 0;

    // check if first jpg created
    int firstExists = 0;

    // array to store filename
    char *filename = malloc((sizeof(char) * 7) + 1);

    // Generate type to store hex values
    typedef uint8_t BYTE;

    // Create array to store 512 byte chunks from sd-card
    BYTE *buffer = malloc(sizeof(BYTE) * 512);

    // pointer for jpg container
    FILE *jpg = NULL;

    // Loop through sdcard in 512 byte chunks
    while (fread(buffer, sizeof(BYTE), 512, sdcard) != 0)
    {
        // Check if 512byte chunk is start of jpeg
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            // No prior jpgs created
            if (jpg == NULL)
            {
                sprintf(filename, "%03i.jpg", jpgCounter);
                jpg = fopen(filename, "w");
                //fwrite(buffer, sizeof(BYTE), 512, jpg);
            }
            // Prior jpgs exist
            else
            {
                fclose(jpg);
                jpgCounter++;
                sprintf(filename, "%03i.jpg", jpgCounter);
                jpg = fopen(filename, "w");
            }
        }

        if (jpg != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }
    }
    free(filename);
    free(buffer);
    fclose(jpg);
    fclose(sdcard);
}