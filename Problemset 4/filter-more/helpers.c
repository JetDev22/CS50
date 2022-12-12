#include "helpers.h"
#include <math.h>
#include <stdio.h>

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
            image[row][column].rgbtBlue = (int)round(average);
            image[row][column].rgbtGreen = (int)round(average);
            image[row][column].rgbtRed = (int)round(average);
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
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) /
                                   9.0;
                float averageBlue = (copy[row - 1][column - 1].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue +
                                     copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) /
                                    9.0;
                float averageGreen = (copy[row - 1][column - 1].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen +
                                      copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) /
                                     9.0;

                // assign average to center pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For upper left corner
            if (row == 0 && column == 0)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) /
                                   4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) /
                                    4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) /
                                     4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For upper right corner
            if (row == 0 && column == width - 1)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column - 1].rgbtRed) /
                                   4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column - 1].rgbtBlue) /
                                    4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column - 1].rgbtGreen) /
                                     4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For lower left corner
            if (row == height - 1 && column == 0)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed) /
                                   4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) /
                                    4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) /
                                     4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For lower right corner
            if (row == height - 1 && column == width - 1)
            {
                float averageRed = (copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row - 1][column].rgbtRed + copy[row - 1][column - 1].rgbtRed) /
                                   4.0;
                float averageBlue = (copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row - 1][column].rgbtBlue + copy[row - 1][column - 1].rgbtBlue) /
                                    4.0;
                float averageGreen = (copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row - 1][column].rgbtGreen + copy[row - 1][column - 1].rgbtGreen) /
                                     4.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For left edge
            if (column == 0 && row > 0 && row < height - 1)
            {
                float averageRed = (copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed +
                                    copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) /
                                   6.0;
                float averageBlue = (copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue +
                                     copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) /
                                    6.0;
                float averageGreen = (copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen +
                                      copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) /
                                     6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For right edge
            if (column == width - 1 && row > 0 && row < height - 1)
            {
                float averageRed = (copy[row - 1][column].rgbtRed + copy[row - 1][column - 1].rgbtRed +
                                    copy[row][column].rgbtRed + copy[row][column - 1].rgbtRed +
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed) /
                                   6.0;
                float averageBlue = (copy[row - 1][column].rgbtBlue + copy[row - 1][column - 1].rgbtBlue +
                                     copy[row][column].rgbtBlue + copy[row][column - 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue) /
                                    6.0;
                float averageGreen = (copy[row - 1][column].rgbtGreen + copy[row - 1][column - 1].rgbtGreen +
                                      copy[row][column].rgbtGreen + copy[row][column - 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen) /
                                     6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For upper edge
            if (row == 0 && column > 0 && column < width - 1)
            {
                float averageRed = (copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row + 1][column - 1].rgbtRed + copy[row + 1][column].rgbtRed + copy[row + 1][column + 1].rgbtRed) /
                                   6.0;
                float averageBlue = (copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row + 1][column - 1].rgbtBlue + copy[row + 1][column].rgbtBlue + copy[row + 1][column + 1].rgbtBlue) /
                                    6.0;
                float averageGreen = (copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row + 1][column - 1].rgbtGreen + copy[row + 1][column].rgbtGreen + copy[row + 1][column + 1].rgbtGreen) /
                                     6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }

            // For lower edge
            if (row == height - 1 && column > 0 && column < width - 1)
            {
                float averageRed = (copy[row][column - 1].rgbtRed + copy[row][column].rgbtRed + copy[row][column + 1].rgbtRed +
                                    copy[row - 1][column - 1].rgbtRed + copy[row - 1][column].rgbtRed + copy[row - 1][column + 1].rgbtRed) /
                                   6.0;
                float averageBlue = (copy[row][column - 1].rgbtBlue + copy[row][column].rgbtBlue + copy[row][column + 1].rgbtBlue +
                                     copy[row - 1][column - 1].rgbtBlue + copy[row - 1][column].rgbtBlue + copy[row - 1][column + 1].rgbtBlue) /
                                    6.0;
                float averageGreen = (copy[row][column - 1].rgbtGreen + copy[row][column].rgbtGreen + copy[row][column + 1].rgbtGreen +
                                      copy[row - 1][column - 1].rgbtGreen + copy[row - 1][column].rgbtGreen + copy[row - 1][column + 1].rgbtGreen) /
                                     6.0;

                // assign average to pixel
                image[row][column].rgbtRed = (int)round(averageRed);
                image[row][column].rgbtGreen = (int)round(averageGreen);
                image[row][column].rgbtBlue = (int)round(averageBlue);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
        // Iterate through each column of given row
        for (int column = 0; column < width; column++)
        {
            // 9 pixel grid around origin possible
            if (column - 1 >= 0 && column + 1 <= width - 1 && row - 1 >= 0 && row + 1 <= height - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (0 * copy[row - 1][column].rgbtRed) +
                             (1 * copy[row - 1][column + 1].rgbtRed) +
                             (-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed) +
                             (-1 * copy[row + 1][column - 1].rgbtRed) + (0 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));
                int GyRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (-2 * copy[row - 1][column].rgbtRed) +
                             (-1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed) +
                             (1 * copy[row + 1][column - 1].rgbtRed) + (2 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (0 * copy[row - 1][column].rgbtGreen) +
                               (1 * copy[row - 1][column + 1].rgbtGreen) +
                               (-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen) +
                               (-1 * copy[row + 1][column - 1].rgbtGreen) + (0 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));
                int GyGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (-2 * copy[row - 1][column].rgbtGreen) +
                               (-1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen) +
                               (1 * copy[row + 1][column - 1].rgbtGreen) + (2 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (0 * copy[row - 1][column].rgbtBlue) +
                              (1 * copy[row - 1][column + 1].rgbtBlue) +
                              (-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue) +
                              (-1 * copy[row + 1][column - 1].rgbtBlue) + (0 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));
                int GyBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (-2 * copy[row - 1][column].rgbtBlue) +
                              (-1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue) +
                              (1 * copy[row + 1][column - 1].rgbtBlue) + (2 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Top Row
            if (row == 0 && column > 0 && column < width - 1)
            {
                int GxRed = ((-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed) +
                             (-1 * copy[row + 1][column - 1].rgbtRed) + (0 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));
                int GyRed = ((0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed) +
                             (1 * copy[row + 1][column - 1].rgbtRed) + (2 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen) +
                               (-1 * copy[row + 1][column - 1].rgbtGreen) + (0 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));
                int GyGreen = ((0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen) +
                               (1 * copy[row + 1][column - 1].rgbtGreen) + (2 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue) +
                              (-1 * copy[row + 1][column - 1].rgbtBlue) + (0 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));
                int GyBlue = ((0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue) +
                              (1 * copy[row + 1][column - 1].rgbtBlue) + (2 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Bottom Row
            if (row == height - 1 && column > 0 && column < width - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (0 * copy[row - 1][column].rgbtRed) +
                             (1 * copy[row - 1][column + 1].rgbtRed) +
                             (-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed));
                int GyRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (-2 * copy[row - 1][column].rgbtRed) +
                             (-1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (0 * copy[row - 1][column].rgbtGreen) +
                               (1 * copy[row - 1][column + 1].rgbtGreen) +
                               (-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen));
                int GyGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (-2 * copy[row - 1][column].rgbtGreen) +
                               (-1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (0 * copy[row - 1][column].rgbtBlue) +
                              (1 * copy[row - 1][column + 1].rgbtBlue) +
                              (-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue));
                int GyBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (-2 * copy[row - 1][column].rgbtBlue) +
                              (-1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Left Column
            if (column == 0 && row > 0 && row < height - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((0 * copy[row - 1][column].rgbtRed) + (1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed) +
                             (0 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));
                int GyRed = ((-2 * copy[row - 1][column].rgbtRed) + (-1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed) +
                             (2 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((0 * copy[row - 1][column].rgbtGreen) + (1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen) +
                               (0 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));
                int GyGreen = ((-2 * copy[row - 1][column].rgbtGreen) + (-1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen) +
                               (2 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((0 * copy[row - 1][column].rgbtBlue) + (1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue) +
                              (0 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));
                int GyBlue = ((-2 * copy[row - 1][column].rgbtBlue) + (-1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue) +
                              (2 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Right Column
            if (column == width - 1 && row > 0 && row < height - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (0 * copy[row - 1][column].rgbtRed) +
                             (-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) +
                             (-1 * copy[row + 1][column - 1].rgbtRed) + (0 * copy[row + 1][column].rgbtRed));
                int GyRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (-2 * copy[row - 1][column].rgbtRed) +
                             (0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) +
                             (1 * copy[row + 1][column - 1].rgbtRed) + (2 * copy[row + 1][column].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (0 * copy[row - 1][column].rgbtGreen) +
                               (-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) +
                               (-1 * copy[row + 1][column - 1].rgbtGreen) + (0 * copy[row + 1][column].rgbtGreen));
                int GyGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (-2 * copy[row - 1][column].rgbtGreen) +
                               (0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) +
                               (1 * copy[row + 1][column - 1].rgbtGreen) + (2 * copy[row + 1][column].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (0 * copy[row - 1][column].rgbtBlue) +
                              (-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) +
                              (-1 * copy[row + 1][column - 1].rgbtBlue) + (0 * copy[row + 1][column].rgbtBlue));
                int GyBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (-2 * copy[row - 1][column].rgbtBlue) +
                              (0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) +
                              (1 * copy[row + 1][column - 1].rgbtBlue) + (2 * copy[row + 1][column].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Top Left pixel
            if (row == 0 && column == 0)
            {
                // Edge Filter Red Channel
                int GxRed = ((0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed) +
                             (0 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));
                int GyRed = ((0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed) +
                             (2 * copy[row + 1][column].rgbtRed) + (1 * copy[row + 1][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen) +
                               (0 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));
                int GyGreen = ((0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen) +
                               (2 * copy[row + 1][column].rgbtGreen) + (1 * copy[row + 1][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue) +
                              (0 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));
                int GyBlue = ((0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue) +
                              (2 * copy[row + 1][column].rgbtBlue) + (1 * copy[row + 1][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Top Right Pixel
            if (row == 0 && column == width - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) +
                             (-1 * copy[row + 1][column - 1].rgbtRed) + (0 * copy[row + 1][column].rgbtRed));
                int GyRed = ((0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed) +
                             (1 * copy[row + 1][column - 1].rgbtRed) + (2 * copy[row + 1][column].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) +
                               (-1 * copy[row + 1][column - 1].rgbtGreen) + (0 * copy[row + 1][column].rgbtGreen));
                int GyGreen = ((0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen) +
                               (1 * copy[row + 1][column - 1].rgbtGreen) + (2 * copy[row + 1][column].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) +
                              (-1 * copy[row + 1][column - 1].rgbtBlue) + (0 * copy[row + 1][column].rgbtBlue));
                int GyBlue = ((0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue) +
                              (1 * copy[row + 1][column - 1].rgbtBlue) + (2 * copy[row + 1][column].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Bottom Left Pixel
            if (row == height - 1 && column == 0)
            {
                // Edge Filter Red Channel
                int GxRed = ((0 * copy[row - 1][column].rgbtRed) + (1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column].rgbtRed) + (2 * copy[row][column + 1].rgbtRed));
                int GyRed = ((-2 * copy[row - 1][column].rgbtRed) + (-1 * copy[row - 1][column + 1].rgbtRed) +
                             (0 * copy[row][column].rgbtRed) + (0 * copy[row][column + 1].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((0 * copy[row - 1][column].rgbtGreen) + (1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column].rgbtGreen) + (2 * copy[row][column + 1].rgbtGreen));
                int GyGreen = ((-2 * copy[row - 1][column].rgbtGreen) + (-1 * copy[row - 1][column + 1].rgbtGreen) +
                               (0 * copy[row][column].rgbtGreen) + (0 * copy[row][column + 1].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((0 * copy[row - 1][column].rgbtBlue) + (1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column].rgbtBlue) + (2 * copy[row][column + 1].rgbtBlue));
                int GyBlue = ((-2 * copy[row - 1][column].rgbtBlue) + (-1 * copy[row - 1][column + 1].rgbtBlue) +
                              (0 * copy[row][column].rgbtBlue) + (0 * copy[row][column + 1].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

            // Bottom Right Pixel
            if (row == height - 1 && column == width - 1)
            {
                // Edge Filter Red Channel
                int GxRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (0 * copy[row - 1][column].rgbtRed) +
                             (-2 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed));
                int GyRed = ((-1 * copy[row - 1][column - 1].rgbtRed) + (-2 * copy[row - 1][column].rgbtRed) +
                             (0 * copy[row][column - 1].rgbtRed) + (0 * copy[row][column].rgbtRed));

                // Edge Filter Green Channel
                int GxGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (0 * copy[row - 1][column].rgbtGreen) +
                               (-2 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen));
                int GyGreen = ((-1 * copy[row - 1][column - 1].rgbtGreen) + (-2 * copy[row - 1][column].rgbtGreen) +
                               (0 * copy[row][column - 1].rgbtGreen) + (0 * copy[row][column].rgbtGreen));

                // Edge Filter Blue Channel
                int GxBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (0 * copy[row - 1][column].rgbtBlue) +
                              (-2 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue));
                int GyBlue = ((-1 * copy[row - 1][column - 1].rgbtBlue) + (-2 * copy[row - 1][column].rgbtBlue) +
                              (0 * copy[row][column - 1].rgbtBlue) + (0 * copy[row][column].rgbtBlue));

                // set new value to pixel
                image[row][column].rgbtRed = ((int)round(sqrt((GxRed * GxRed) + (GyRed * GyRed))) > 255) ? 255 : (int)round(sqrt((GxRed * GxRed) +
                                             (GyRed * GyRed)));
                image[row][column].rgbtGreen = ((int)round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))) > 255) ? 255 : (int)round(sqrt((
                                                   GxGreen * GxGreen) + (GyGreen * GyGreen)));
                image[row][column].rgbtBlue = ((int)round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))) > 255) ? 255 : (int)round(sqrt((
                                                  GxBlue * GxBlue) + (GyBlue * GyBlue)));
            }

        }
    }
    return;
}
