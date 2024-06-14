#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>




int count_letters();
int count_words();
int count_sentences();

int main(void)
{

    string text = get_string("Text: ");

//turn counts into floats or output is still int
    float letterCount = count_letters(text);
    float wordCount = count_words(text);
    float sentenceCount = count_sentences(text);


    float L = 100 * (letterCount / wordCount);
    float S = 100 * (sentenceCount / wordCount);

//colmeman-liau
    float calc = round(0.0588 * L - 0.296 * S - 15.8);
    int index = round(calc);


    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }



}

int count_letters(string text)
{
    int letters;
    int n = 0;
    letters = strlen(text);

    for (int i = 0; i < letters; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            n++;
        }

    }

    return n;

}

int count_words(string text)
{
    int letters;
    int words = 0;
    letters = strlen(text);

    for (int i = 0; i < letters; i++)
    {
        if ((text[i]) == ' ')
        {
            words++;
        }

    }
    words++;


    return words;
}

int count_sentences(string text)
{
    int letters;
    int sentences = 0;
    letters = strlen(text);

    for (int i = 0; i < letters; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sentences++;
        }

    }


    return sentences;
}
