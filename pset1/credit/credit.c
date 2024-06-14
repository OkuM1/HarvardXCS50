#include <cs50.h>
#include <stdio.h>

//Credit Card Number
long CCN ;
//loop
int i = 0;


void userInput()
{
    //get ccn input from user
    do
    {
        CCN = get_long("Please enter your credit card number: ");
        printf("Checking %li ...\n", CCN);
    }
    while (CCN < 0);

}

//IMPORTANT MODULO OPERATOR DIVIDES AND GIVES THE REST OF DIVISION. %10 GIVES LAST DIGIT OF NUMBER

void cardType()
{
    long firstdigit = CCN;
    do
    {
        firstdigit = firstdigit / 10;
    }
    while (firstdigit > 100);

    if ((firstdigit / 10 == 5) && (0 < firstdigit % 10 && firstdigit % 10 < 6))
    {
        printf("MASTERCARD\n");
        return;
    }
    else if ((firstdigit / 10 == 3) && (firstdigit % 10 == 4 || firstdigit % 10 == 7))
    {
        printf("AMEX\n");
        return;
    }
    else if (firstdigit / 10 == 4)
    {
        printf("VISA\n");
        return;
    }
    else
    {
        printf("INVALID\n");
        return;
    }
}

int main()
{
//gets CCN input function
    userInput();


    long length = CCN;
// Count length
    while (length > 0)
    {
        length = length / 10;
        i++;
    }

// Check if length is valid
    if (i != 13 && i != 15 && i != 16)
    {
        printf("INVALID\n");
        return 0;
    }

//Luhns Algo
    int sum1 = 0;
    int sum2 = 0;
    //x is here to create loop condition to work through the entire ccn
    long x = CCN;
    int total = 0;
    int lastnumberofmod2;
    int firstnumberofmod2;
    //these take every other digit
    int mod1;
    int mod2;
    do
    {
        //take remainder of ccn
        mod1 = x % 10;
        x = x / 10;
        sum1 = sum1 + mod1;

        mod2 = x % 10;
        x = x / 10;

        mod2 = mod2 * 2;
        lastnumberofmod2 = mod2 % 10;
        firstnumberofmod2 = mod2 / 10;
        //add sums
        sum2 = sum2 + lastnumberofmod2 + firstnumberofmod2;
    }
    while (x > 0);

    total = sum1 + sum2;

    //check if last digit in the total is 0
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;

    }

//check for card type
    cardType();

}

