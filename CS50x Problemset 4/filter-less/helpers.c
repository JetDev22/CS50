#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row
    for (int row = 0; row < height; row++)
    {
        // Iterate through each column of row
        for (int column = 0; column < width; column++)
        {
            // get average of pixels rgb values
            float average = (image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3.0;

            // assigne average value to pixel
            image[row][column].rgbtBlue = (int) round(average);
            image[row][column].rgbtGreen = (int) round(average);
            image[row][column].rgbtRed = (int) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row
    for (int row = 0; row < height; row++)
    {
        // Iterate through each column of row
        for (int column = 0; column < width; column++)
        {
            // Apply sepia algorithm to each color
            float sepiaRed = .393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue;
            float sepiaGreen = .349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue;
            float sepiaBlue = .272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue;

            // Round to nearest int
            sepiaRed = (int) round(sepiaRed);
            sepiaGreen = (int) round(sepiaGreen);
            sepiaBlue = (int) round(sepiaBlue);

            // Check if any value greater 255, if so, set to 255
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;

            // assigne average value to pixel
            image[row][column].rgbtBlue = sepiaBlue;
            image[row][column].rgbtGreen = sepiaGreen;
            image[row][column].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row
    for (int row = 0; row < height; row++)
    {
        // even number of pixels in row
        if (width % 2 == 0)
        {
            // define last object in row for swap
            int currentEndOfRow = width - 1;

            // look at first half of pixels and swap with other half
            for (int column = 0; column <= (width - 1) / 2; column++)
            {
                RGBTRIPLE tmp = image[row][column];
                image[row][column] = image[row][currentEndOfRow];
                image[row][currentEndOfRow] = tmp;
                currentEndOfRow--;
            }
        }

        // uneven number of pixels in row
        if (width % 2 != 0)
        {
            // define middle pixel that will not be swapped
            int middlePixel = (width - 1) / 2;

            // define last object in row for swap
            int currentEndOfRow = width - 1;

            // look at first half of pixels and swap with other half
            for (int column = 0; column < middlePixel; column++)
            {
                RGBTRIPLE tmp = image[row][column];
                image[row][column] = image[row][currentEndOfRow];
                image[row][currentEndOfRow] = tmp;
                currentEndOfRow--;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy of image to get unaltered rgb values
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }
    }


    // Iterate through each row
    for (int row = 0; row < height; row++)
    {
        // Iterate through each column of row
        for (int column = 0; column < width; column++)
        {
            // 9 pixel grid around origin possible
            if (column - 1 >= 0 && column + 1 <= width - 1 && row - 1 >= 0 && row + 1 <= height - 1)
            {
                float averageRed = (copy[row - 1][column - 1].rgbtRed + copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed +
                                    copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 9.0;
                float averageBlue = (copy[row - 1][column - 1].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue +
                                     copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 9.0;
                float averageGreen = (copy[row - 1][column - 1].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen +
                                      copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 9.0;

                // assign average to center pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For upper left corner
            if (row == 0 && column == 0)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For upper right corner
            if (row == 0 && column == width - 1)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column - 1].rgbtRed) / 4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column - 1].rgbtBlue) / 4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column - 1].rgbtGreen) / 4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For lower left corner
            if (row == height - 1 && column == 0)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed) / 4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) / 4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) / 4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For lower right corner
            if (row == height - 1 && column == width - 1)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row - 1][column].rgbtRed + copy[row - 1][column - 1].rgbtRed) / 4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row - 1][column].rgbtBlue + copy[row - 1][column - 1].rgbtBlue) / 4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row - 1][column].rgbtGreen + copy[row - 1][column - 1].rgbtGreen) / 4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For left edge
            if (column == 0 && row > 0 && row < height - 1)
            {
                float averageRed = (copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed +
                                    copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 6.0;
                float averageBlue = (copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue +
                                     copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 6.0;
                float averageGreen = (copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen +
                                      copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For right edge
            if (column == width - 1 && row > 0 && row < height - 1)
            {
                float averageRed = (copy[row - 1][column].rgbtRed + copy[row - 1][column - 1].rgbtRed +
                                    copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed) / 6.0;
                float averageBlue = (copy[row - 1][column].rgbtBlue + copy[row - 1][column - 1].rgbtBlue +
                                     copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue) / 6.0;
                float averageGreen = (copy[row - 1][column].rgbtGreen + copy[row - 1][column - 1].rgbtGreen +
                                      copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen) / 6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For upper edge
            if (row == 0 && column > 0 && column < width - 1)
            {
                float averageRed = (copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) / 6.0;
                float averageBlue = (copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) / 6.0;
                float averageGreen = (copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) / 6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }

            // For lower edge
            if (row == height - 1 && column > 0 && column < width - 1)
            {
                float averageRed = (copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row - 1][column - 1].rgbtRed + copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed) / 6.0;
                float averageBlue = (copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row - 1][column - 1].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) / 6.0;
                float averageGreen = (copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row - 1][column - 1].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) / 6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int) round(averageRed);
                image[row][column].rgbtGreen = (int) round(averageGreen);
                image[row][column].rgbtBlue = (int) round(averageBlue);
            }
        }
    }
    return;
}
