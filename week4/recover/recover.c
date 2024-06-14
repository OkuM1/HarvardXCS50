#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: recover infile\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *file = fopen(infile, "r");

    if (file == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    //buffer with size 512
    BYTE buffer[512];
    //count of jpgs
    int jpg_count = 0;
    //for new jpgs new file
    FILE *outptr = NULL;
    //allocate memory to output
    char *newfile = malloc(8);


    //4 byte jpg header 0xff 0xd8 0xff and 0xe0,1,2...


    //read blocks of 512 bytes into buffer
    while (fread(buffer, 1, 512, file) == 512)
    {


        //check for jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_count != 0)
            {
                fclose(outptr);
            }

            //write first jpg found
            sprintf(newfile, "%03i.jpg", jpg_count);

            outptr = fopen(newfile, "w");

            jpg_count++;
        }


        if (outptr != NULL)
        {
            fwrite(buffer, 512, 1, outptr);
        }

    }



    //close
    fclose(file);
    fclose(outptr);
    free(newfile);


    return 0;

}