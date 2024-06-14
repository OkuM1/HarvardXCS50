#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string txt = get_string("Text: ");

    //go though txt as array
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        //convert to ASCII
        int decimal = txt[i];

        int bin[] = {0, 0, 0, 0, 0, 0, 0, 0};

        //ASCII to binary

        int j = 0;

        while (decimal > 0)
        {
            bin[j] = decimal % 2;
            decimal = decimal / 2;
            j++;
        }

        //print array in reverse to make binary from right to left
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            print_bulb(bin[k]);
        }
        printf("\n");
    }


}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

