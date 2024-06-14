#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    //The loops go over every pixel
    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {

        // Iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {
            //define pixel and each column and row assign a pixel with i and j
            RGBTRIPLE pixel = image[i][j];

            //if scanned pixel is black
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                //changing color of black pixels to these values
                image[i][j].rgbtBlue = 100;
                image[i][j].rgbtRed = 40;
            }

        }

    }
}