//!@file

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "my header hard.h"


int main ()
{
    UniTest();

    char* file_read = "go.txt";
    char* file_write = "file_write.txt";

    //GO_GREET Greet (&file_read, &file_write);

    File_Clean (file_write);
    PRINTF ("Clean\n");

    long fsize = ReadFileLength (file_read);
    PRINTF ("Number of symbols in the text = %ld\n", fsize);

    char* my_string = Create_Str (&fsize, file_read);
    PRINTF ("The REAL size is %d\n", fsize);

    long num_lines = Symb_Counter (my_string, '\n');
    PRINTF ("There are %ld lines in the file.\n", num_lines);
    poem_line* pointer = StringMaker (my_string, fsize, num_lines);
    PRINTF ("pOEM\n");

    PRINTF ("MY\n");

    Qsort (0, num_lines - 1, pointer, sizeof (pointer[0]), Is_Larger_Str);
    PRINTF ("Qsort\n");

    WriteFile (file_write, num_lines, pointer);
    PRINTF ("Write File\n");

    Qsort (0, num_lines - 1, pointer, sizeof (pointer[0]), Is_Larger_Str_Reverse);
    PRINTF ("Qsort2\n");

    WriteFile (file_write, num_lines, pointer);
    PRINTF ("WRITE FILE 2\n");

    free (my_string);
    PRINTF ("FREEE\n");
    my_string = NULL;

    return 0;
}

