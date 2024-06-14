#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declare height of pyramid
    int nheight;
    do
    {
        //user inputs height of pyramid
        nheight = get_int("Height(1-8): ");

    }
    while (!(nheight > 0 && nheight < 9));

    //check if height is between 1-8
    if (nheight > 0 && nheight < 9)
    {
        int length = 0;
        //sets length(number of hashes in a row) of pyramid to 0

        //for every row of pyramid repeated till nheight(user input) reached
        for (int i = 0; i < nheight; i++)
        {

            //if length does not equal nheight execute
            if (length != nheight)
            {

                //print spaces till nheight is smaller than 1 (tip of pyramic example(nheight: 3): -spaces-spaces-#)
                for (int k = nheight - i; k > 1; k--)
                {
                    printf(" ");
                }
                //print # for every row
                for (int j = 0; j <= i; j++)
                {
                    printf("#");
                }
                //prints space for other half of pyramid to be disconnected
                printf("  ");

                //prints only # of right side of pyramid
                for (int hashes = 0; hashes <= length; hashes++)
                {
                    printf("#");
                }

                printf("\n");
                length++;
            }
        }

    }
}
