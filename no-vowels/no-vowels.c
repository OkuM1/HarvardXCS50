// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string Replace(string s);

int main(int argc, string argv[])
{
    if (argc < 1)
    {
        printf("Error");
        return 1;

    }

    string word = argv[1];

    string result = Replace(word);


}

string Replace(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 'a')
        {
            s[i] = '6';
        }
    }

    printf("%s\n", s);

    return 0;
}
