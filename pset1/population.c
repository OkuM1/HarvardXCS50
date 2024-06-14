#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n_start;
    do
    {
        n_start = get_int("StartSize: ");
    }
    while (n_start < 9);

    // TODO: Prompt for end size
    int n_end;
    do
    {
        n_end = get_int("EndSize: ");
    }
    while (n_end < n_start);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;

    while (n_start < n_end)
    {
        n_start = n_start + (n_start / 3) - (n_start / 4);
        years++;
    }
    // TODO: Print number of years

    printf("Years: %i\n", years);

}
