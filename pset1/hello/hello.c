#include <stdio.h>
#include <cs50.h>

//main function
int main(void)

{
    //ask user for name and takes input as string
    string name = get_string("What is your name?: ");

    //prints Hello + input of user
    printf("hello, %s\n", name);
}