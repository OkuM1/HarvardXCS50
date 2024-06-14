#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {

        // Iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {

            //changing color
            int average_RGB = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average_RGB;
            image[i][j].rgbtBlue = average_RGB;
            image[i][j].rgbtGreen = average_RGB;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {

        // Iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {
            //define pixel and each column and row assign a pixel with i and j
            RGBTRIPLE pixel = image[i][j];

            //changing color to formula
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //cap range of RGB for each color value, can also use fmin apparently here
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < width / 2; j++)
        {

            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - j - 1];

            image[i][width - j - 1] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {

        // Iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {

            //copy image
            copy[i][j] = image [i][j];

        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int red = 0;
            int green = 0;
            int blue = 0;
            float n = 0.0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    //new coordinate to exclude out of bounds
                    int nowk = i + k;
                    int nowl = j + l;

                    //if in bounds
                    if (nowk < 0 || nowk > (height - 1) || nowl < 0 || nowl > (width - 1))
                    {

                        continue;
                    }
                    //sum up rgb values of surrounding ixel
                    red += image[nowk][nowl].rgbtRed;
                    green += image[nowk][nowl].rgbtGreen;
                    blue += image[nowk][nowl].rgbtBlue;

                    n++;
                }
            }

            //calculate average rgb values of surrounding pixel rgb
            copy[i][j].rgbtRed = round(red / n);
            copy[i][j].rgbtGreen = round(green / n);
            copy[i][j].rgbtBlue = round(blue / n);
        }
    }



    for (int i = 0; i < height; i++)
    {

        // Iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {

            //copy image back
            image[i][j] = copy[i][j];

        }

    }

    return;

}
