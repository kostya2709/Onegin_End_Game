//!@file

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "my header hard.h"

#define DO( what )                   \
    printf ("Doing " #what "...\n"); \
    what;                            \
    printf ("End "  #what "...\n\n");

int main ()
{
    UniTest();

    char* file_read  = "file_read.txt";
    char* file_write = "file_write.txt";

    //GO_GREET Greet (&file_read, &file_write);

    long fsize = 0;
    long num_lines = 0;
    char* my_string = File_Reader (file_read, &num_lines, &fsize);

    DO ( poem_line* pointer = StringMaker (my_string, fsize, num_lines); )

    DO ( Qsort (0, num_lines - 1, pointer, sizeof (pointer[0]), Is_Larger_Str); )

    DO ( File_Clean (file_write); )

    DO ( WriteFile (file_write, num_lines, pointer); )

    DO ( Qsort (0, num_lines - 1, pointer, sizeof (pointer[0]), Is_Larger_Str_Reverse); )

    DO ( WriteFile (file_write, num_lines, pointer); )

    DO ( free (my_string); )

    my_string = NULL;

    return 0;
}

