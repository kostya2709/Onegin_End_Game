#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "my header hard.h"

void UniTest ()
{
    File_Clean_Test();

    Str_Length_Test ();

    Qsort_Test ();

    Is_Larger_Str_Test ();

    Is_Larger_Str_Reverse_Test ();

    Swap ();
}

void File_Clean_Test (void)
{
    char* test_str = "Test_project";
    FILE* f = fopen (test_str, "w");
    for (int i = 0; i < 100; i++)
        fputc (rand()%100, f);
    fclose (f);

    File_Clean(test_str);

    char* str = (char*)calloc (101, 1);

    f = fopen (test_str, "w");
    long length = fread (str, 101, 1, f);
    if (!length)
        printf ("Great! File_Clean works correctly!\n\n");
    else
        printf ("Error! The file is not empty! File_Clean is wrong!\n\n");
    fclose (f);

    free (str);
    free (test_str);
}

void Str_Length_Test (void)
{                 //00000000001111111111222222222233333333334444444444
    // TEST 1     //01234567890123456789012345678901234567890123456789
    char* string = "With great power comes great responsibility!";
    long length = Str_Length (string);
    if (length == 44)
        printf ("Great! The first test in Str_Length_Test is done! Go ahead!\n");
    else
        printf ("Oops! Something went wrong in Str_Length_Test Test_1\n");
    free (string);

    //  TEST 2
    length = rand() % 100;
    string = (char*) calloc (length, 1);
    int i = 0;
    for (i = 0; i < length; i++)
        *(string + i) = 'a' + rand() % 26;
    if (length == Str_Length (string))
        printf ("Great! The second test is completed!\n");
    else
        printf ("Ooops! The second test in Str_Length_Test has failed!\n");
    free (string);

    //TEST 3
    char* empty = (char*)calloc (1,1);
    if (!Str_Length (empty))
        printf ("Excellent! The test 3 is completed!\n\n");
    else
    printf ("The third test has failed\n\n");
    free (empty);

}

int Test_Compare (const void* a, const void* b)
{
    assert (a);
    assert (b);

    int a1 = *((int*)a);
    int b1 = *((int*)b);
    if (a1 > b1) return 1;
    else if (a1 == b1) return 0;
    else return -1;
}

void Qsort_Test ()
{
    // TEST 1
    int size = rand() % 100;
    int arr[size] = {};
    int i = 0;
    for (i = 0; i < size; i++)
        arr[i] = rand () % 100 - 50;

    Qsort (0, size, arr, sizeof(int), Test_Compare);

    for (i = 0; i < size - 1; i++)
        if (Test_Compare ((void*)(arr + i), (void*)(arr + i + 1)) > 0)
        {
            printf ("Error! The first Qsort test has failed!\n");
            printf ("ERROR %d %d\n", *(arr + i), *(arr + i +1));
            break;
        }

    if (i == size - 1) printf ("Hey! Your Qsort is good! The first test is done!\n\n");

    //TEST 2
    /*size = rand () % 100 + 5;
    char* tline[size];
    for (i = 0; i < size; i++)
        tline [i] = (char*) calloc (1, 10);
    tline [0] = "You";
    tline [1] = "shell";
    tline [2] = "not";
    tline [3] = "pass!";

    int j = 0;
    for (i = 4; i < size; i++)
        for (j = 0; i < rand ()% 10; j++)
            **(tline + i + j) = 'a' + rand() % 26;

    for (i = 0; i < size; i++)
        printf ("%s\n", tline[i]);
*/

}

void Is_Larger_Str_Test()
{
    int result = 0;
    //Test 1
    poem_line word1 = *((poem_line*)calloc(20, 1));
    poem_line word2 = *((poem_line*)calloc(20, 1));
    word1.start = "abcd";
    word2.start = "abce";

    result = Is_Larger_Str (&word1, &word2);
    if (result != -1)
        printf ("Error! The first Is_Larger_Str test failed! Expected -1, received %d!\n", result);
    else printf ("Great! The first Is_Larger_Str comparing test is o'kay!\n");

    //TEST 2
    word1.start = "+*(abcd";
    word2.start = "=-abcd";

    result = Is_Larger_Str (&word1, &word2);
    if (result != 0)
        printf ("Error! The second Is_Larger_Str test failed! Expected -1, received %d!\n", result);
    else printf ("Great! The second Is_Larger_Str comparing test is o'kay!\n");

    // TEST 3
    word1.start = "AbCd";
    word2.start = "aBce";

    result = Is_Larger_Str (&word1, &word2);
    if (result != -1)
        printf ("Error! The third Is_Larger_Str test failed! Expected -1, received %d!\n", result);
    else printf ("Great! The third Is_Larger_Str comparing test is o'kay!\n");

    //TEST 4
    word1.start = "Life is great!";
    word2.start = "Life is great!";

    result = Is_Larger_Str (&word1, &word2);
    if (result != 0)
        printf ("Error! The fourth Is_Larger_Str test failed! Expected 0, received %d!\n", result);
    else printf ("Great! The fourth Is_Larger_Str comparing test is o'kay!\n");

    //TEST 5
    word1.start = "Life is great!";
    word2.start = " ";

    result = Is_Larger_Str (&word1, &word2);
    if (result <= 0)
        printf ("Error! The fifth Is_Larger_Str test failed! Expected '76', received %d!\n\n", result);
    else printf ("Great! The fifth Is_Larger_Str comparing test is o'kay!\n\n");

    free (word1.start);
    free (word2.start);
}

void Is_Larger_Str_Reverse_Test()
{
    int result = 0;
    //Test 1
    poem_line word1 = *((poem_line*)calloc(20, 1));
    poem_line word2 = *((poem_line*)calloc(20, 1));

    word1.start = "babc\0";
    word1.end = word1.start + Str_Length(word1.start) + 1;
        //printf ("sym = %c, length = %d, length pointer = %d\n", *(word1.end - 2), Str_Length(word1.start), word1.end - word1.start);
    word2.start = "aabc\0";
    word2.end = word2.start + Str_Length(word2.start) + 1;

    result = Is_Larger_Str_Reverse (&word1, &word2);
    if (result != 1)
         printf ("Error! The first Is_Larger_Str_Reverse test failed! Expected 1, received %d!\n", result);
    else printf ("Great! The first Is_Larger_Str_Reverse comparing test is o'kay!\n");

    //TEST 2
    word1.start = "bbcd++\0";
    word2.start = "abcd#/\0";

    word1.end = word1.start + Str_Length(word1.start) + 1;
    word2.end = word2.start + Str_Length(word2.start) + 1;

    result = Is_Larger_Str_Reverse (&word1, &word2);
    if (result <= 0)
         printf ("Error! The second Is_Larger_Str_Reverse test failed! Expected 1, received %d!\n", result);
    else printf ("Great! The second Is_Larger_Str_Reverse comparing test is o'kay!\n");

    // TEST 3
    word1.start = "AbCd\0";
    word2.start = "BBcD\0";

    word1.end = word1.start + Str_Length(word1.start) + 1;
    word2.end = word2.start + Str_Length(word2.start) + 1;

    result = Is_Larger_Str_Reverse (&word1, &word2);
    if (result >= 0)
         printf ("Error! The third Is_Larger_Str_Reverse test failed! Expected 1, received %d!\n", result);
    else printf ("Great! The third Is_Larger_Str_Reverse comparing test is o'kay!\n");

    //TEST 4
    word1.start = "Life is great!\0";
    word2.start = "Life is great!\0";

    word1.end = word1.start + Str_Length(word1.start) + 1;
    word2.end = word2.start + Str_Length(word2.start) + 1;

    result = Is_Larger_Str_Reverse (&word1, &word2);
    if (result != 0)
         printf ("Error! The fourth Is_Larger_Str_Reverse test failed! Expected 0, received %d!\n", result);
    else printf ("Great! The fourth Is_Larger_Str_Reverse comparing test is o'kay!\n");

    //TEST 5
    word1.start = "Life is great!";
    word2.start = " ";

    word1.end = word1.start + Str_Length(word1.start) + 1;
    word2.end = word2.start + Str_Length(word2.start) + 1;

    result = Is_Larger_Str_Reverse (&word1, &word2);
    if (result <= 0)
        printf ("Error! The fifth Is_Larger_Str_Reverse test failed! Expected '76', received %d!\n\n", result);
    else printf ("Great! The fifth Is_Larger_Str_Reverse comparing test is o'kay!\n\n");

    free (word1.start);
    free (word2.start);
}

void Swap (void)
{
    //TEST 1
    int a = rand()%1000 - 500;
    int b = rand()%1000 - 500;
    int a1 = a;
    int b1 = b;
    Swap (&a, &b, sizeof (int));
    if (a == b1 && b == a1)
        printf ("Great! The first Swap test is passed!\n");
    else printf ("Error! The first Swap test has failed! Expected a = %d, b = %d!, received a = %d, b = %d\n", b1, a1, a, b);

    //TEST 2
    poem_line str1 = *((poem_line*)calloc(20, 1));
    poem_line str2 = *((poem_line*)calloc(20, 1));
    poem_line str3 = *((poem_line*)calloc(20, 1));
    poem_line str4 = *((poem_line*)calloc(20, 1));
    str1.start = "I am exhausted! :(";
    str2.start = "Me too!";
    str3.start = "Me too!";
    str4.start = "I am exhausted! :(";

    Swap (&str1.start, &str2.start, sizeof(char*));

    if ((!(Is_Larger_Str (&str1.start, &str3.start))) && (!(Is_Larger_Str (&str2.start, &str4.start))))
        printf ("Great! The second Swap test is passed!\n\n");
    else printf ("Error! The second Swap test has failed! Expected a = %s, b = %s, received a = %s, b = %s\n\n", &str3.start, &str4.start, &str1.start, &str2.start);

    free (str1.start);
    free (str2.start);
    free (str3.start);
    free (str4.start);

}

