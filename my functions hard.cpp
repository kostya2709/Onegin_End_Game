#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/stat.h>
#include "my header hard.h"

/*! This function creates a string with the maximum amount length of symbols from the file.
@param[in] length The maximum amount of symbols.
@param[in] file_read The name of the file to read the string from.
\return The proper string from the file.
*/

char* Create_Str (long* length, const char* file_read)
{
    assert (length);
    assert (file_read);

    char* my_string = (char*) calloc (*length + 1, 1);

    *length = ReadFile (file_read, my_string, *length) + 1;
    realloc (my_string, *length);

    if (* (my_string + *length - 1) != '\n')
        * (my_string + *length) = '\n';
    else
        {
            realloc(my_string, *length - 1);
            *length -= 1;
        }

    return my_string;

}

/*! Greets the user and enters the names of the files
@param[in] file_read The name of the file where to read from.
@param[out] file_write The name of the file where to write to.
*/

void Greet (char** file_read, char** file_write)
{
    *file_read = (char*) calloc (256, 1);
    printf ("Enter which file to read: \n");
    scanf ("%s", *file_read);
    printf ("Hello\n");
    realloc (*file_read, Str_Length (*file_read) + 1);

    *file_write = (char*) calloc (256, 1);
    printf ("Enter where to write: \n");
    scanf ("%s", *file_write);
    printf ("after scanf\n");
    printf ("length is %ld\n", Str_Length (*file_write) + 1);
    realloc (*file_write, Str_Length (*file_write) + 1);
    printf ("SOSU C");
}

/*! Counts length of the string.
*/
long Str_Length (char* str)
{
    char* str_cur = str;
    char* str_start = str;
    for (;*str_cur; str_cur++)
        ;
    return str_cur - str_start;
}

/*! This function cleans the file with the name file_name.
@param[in] file_name The name of the file needs cleaning.
*/

void File_Clean (const char* file_name)
{
    assert (file_name);

    FILE* f = fopen (file_name, "w");
    fclose (f);
}

/*! This function counts the number of symbols in the file.
@param[in] file The pointer to the name of the file
\return The amount of symbols in the file
\warning This function also counts special invisible symbols as:
"\n" and "\r".
*/

long ReadFileLength (const char* file)
{
    assert (file);

    FILE* f = fopen (file, "r");

    fseek (f, 0, SEEK_END);
    long pointer2 = ftell (f);

    fclose (f);
    return (pointer2);

}

/*! This function reads a text from a file to a string.
@param[in] name The name of the file.
@param[in] str A pointer to the string where the text writes to.
@param[in] length The maximum length of the file.
\return 1 if everything is alright.
*/

long ReadFile (const char* name, char* str, int length)
{
    assert (name);
    assert (str);

    FILE* f = fopen (name, "r");
    struct stat ssize;
    stat (name, &ssize);

    //PRINTF ("Precise size is %ld\nID is %ld\nfile serial number is %ld\nmode of file %ld\nnumber of links to the file %ld\nUser ID of file %ld\ngroup ID of file %ld\ndevice ID %ld\ntime of last access %ld\ntime of last data modification %ld\ntime of last data change %ld\na file-specific preferred ... %ld\nnumber of blocks %ld\n", ssize.st_size, ssize.st_dev, ssize.st_ino, ssize.st_mode, ssize.st_uid, ssize.st_gid, ssize.st_rdev, ssize.st_atime, ssize.st_mtime, ssize.st_ctime);
    long real_size = fread ( (char*)str, 1, length, f);
    fclose (f);
    return real_size;
}

/*! This function replaces symbols '\n' to '\0'
@param[in] str The pointer to a string to write it.
@param[in] length The length of the string.
@param[in] poem_line pointer[] The array of poem_line.
\return The number of sublines.
*/

poem_line* StringMaker (char* str, int length, int amount)
{
    assert (str);

    poem_line* pointer = (poem_line*) calloc (amount + 1, sizeof (poem_line));

    pointer[0].start = str;
    int i;
    int counter = 0;
    for (i = 0; i < length; i++)
        if ((*(str + i)) == '\n')
        {
            *(str + i) = '\0';
            pointer[counter].end = str + i;
            counter++;
            if ((i + 1) < length) pointer[counter].start = str + i + 1;
        }
    return pointer;

}

/*!
@brief This function compares two strings lexicographically.
@param[in] *str1 The pointer to the first string needs comparing
@param[in] *str2 The pointer to the second string needs comparing
\return The function returns an integer number.
If the first line is longer than the second one it returns a number that is more than 0;
if the second line is longer than the first one it returns a number that is less than 0;
if the lines are equal the function returns 0.
*/

int Is_Larger_Str (const void* str1, const void* str2)
{

        assert (str1);
        assert (str2);

        poem_line pointer1 = *((poem_line*)str1);
        poem_line pointer2 = *((poem_line*)str2);

        while (!IsLetter (*(pointer1.start)) && *(pointer1.start)) pointer1.start++;
        while (!IsLetter (*(pointer2.start)) && *(pointer2.start)) pointer2.start++;

        while (Down (*pointer1.start) && Down (*pointer2.start)&&(Down (*pointer1.start) == Down (*pointer2.start)))
        {
            pointer1.start++;
            pointer2.start++;
        }
        return Down (*pointer1.start) - Down (*pointer2.start);
}

/*!
@brief This function compares two strings lexicographically from the end.
@param[in] *str1 The pointer to the first string needs comparing
@param[in] *str2 The pointer to the second string needs comparing
\return The function returns an integer number.
If the first line is longer than the second one it returns a number that is more than 0;
if the second line is longer than the first one it returns a number that is less than 0;
if the lines are equal the function returns 0.
*/

int Is_Larger_Str_Reverse (const void* str1, const void* str2)
{

        assert (str1);
        assert (str2);

        poem_line pointer1 = *((poem_line*)str1);
        poem_line pointer2 = *((poem_line*)str2);


        while (!IsLetter (*(pointer1.end)) && (pointer1.end > pointer1.start)) pointer1.end--;
        while (!IsLetter (*(pointer2.end)) && (pointer2.end > pointer2.start)) pointer2.end--;

        while ((Down (*pointer1.end) == Down (*pointer2.end)) && (pointer1.end > pointer1.start)&& (pointer2.end > pointer2.start))
        {
            //printf ("sym = %c\n", *pointer1.end);
            pointer1.end--;
            pointer2.end--;
        }
        return Down (*pointer1.end) - Down (*pointer2.end);
}

/*! This function checks whether the char c is a letter
@param[in] char c need checking
\return 1 if c is a letter and 0 if c is not a letter
    */

int IsLetter (char c)
{
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
        return 1;
    else return 0;
}

/*!
@brief This function changes two elements to each other of the array arr[] with indexes a and b.
param[in] *arr[] The array which elements need changing with each other.
param[in] a The first index.
param[in] a The second index.
*/

void Swap (void* a, void* b, int sizze)
    {
        int i;
        int temp;
        for (i = 0; i < sizze; i++)
        {
            temp = (int)(*((char*)a + i));
            *((char*)a + i) = *((char*)b + i);
            *((char*)b + i) = temp;
        }
    }

/*!
@brief This function returns a little letter, if the letter was capital,
and else it returns this very symbol.
@param[in] char c The char needs checking if the letter is capital.
@param[out] The function returns the decapitallated symbol.
*/

char Down (char c)
{

    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    else return c;
}

/*!
@brief This function writes lines to a file from an
array of string with a pointer *pointer.
@param[in] *file Is a pointer to a file to write the text to.
@param[in] num Is an amount of the array that is written.
@param[in] *pointer[NLINES] Is a pointer to an array of char with NLINES lines.
The function writes strings from this array to the file.
\return It returns 1 if everything is alright and returns 0 if something went wrong.
*/

int WriteFile (const char *file, int num, poem_line pointer[])
{
    assert (file);
    assert (num);

    FILE* f = fopen (file, "a");
    if (!f)
    {
        printf ("This file - %s - doesn't exist!\n", file);
        return 1;
    }

    int i;
    printf ("num = %d", num);
    for (i = 0; i < num ; i++)
    {
        //printf ("%d is OK\n", i);
        fputs (pointer[i].start,f);
        fputc ('\n', f);
        //printf ("%d is OK\n", i);
    }
    fputc ('\n', f);
    fseek (f, 0, 0);
    fclose (f);

    return 0;

}

/*! This functions counts the number of char c in the string str.
@param[in] str String in which symbols are counted
@param[in] c The symbol need counting
\return The amount of the symbol in the string
*/

long Symb_Counter (char* str, char c)
{
    assert (str);

    long counter = 0;

    for (; *str; str++)
        if (*str == c) counter++;

    return counter;
}
