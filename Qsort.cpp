#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "my header hard.h"

#ifdef Debugg
#define DEBUG
#endif // Debug

/*!
@brief This function sorts quick elements of the array.
@param[in] left The left bound of the part of the array needs sorting.
@param[in] right The right bound of the part of the array needs sorting.
@param[in] *pointer[NLINES] The array which elements need sorting.
*/
/*
void Void_Qsort (void  *arr, size_t amount, size_t ssize, int (*compare)(const void*, const void*))
{
        assert (arr);

        char* left = (char*)arr;
        char* right = (char*)arr + ssize * (amount - 1);


        if (left >= right)
            return;

        char* mid = (char*)(((int)left + (int)right) / 2);

        poem_line leftp = *(poem_line*)((char*)arr + (int)(left - (char*)arr)*ssize);

        poem_line leftpp = *((poem_line*)((char*)arr + (int)(mid - (char*)arr)*ssize));
printf ("2 = %s\n", leftpp.start); printf ("I am here!\n");
        poem_line leftppp = *(poem_line*)((char*)arr + ((int)(right - (char*)arr))*ssize);

        //printf ("line left = %s,\n line mid= %s\n, line right = %s\n", leftp.start, leftpp.start, leftppp.start);
        Swap ((void*)((char*)arr + (int)(left - (char*)arr)*ssize), (void*)((char*)arr + (int)(mid - (char*)arr)*ssize), ssize);

        char* last = left;
        int i;
        for (i = 0; i < amount; i++)
        {
            printf ("Hello\n");
            if (compare((void*)((char*)arr + (int)(left - (char*)arr)*ssize), (void*)((char*)arr + i*ssize)) > 0)
                   Swap ((void*)((char*)arr + i*ssize), (void*)((char*)arr + (int)(++last - (char*)arr)*ssize), ssize);
        }
        Swap ((void*)((char*)arr + (int)(left - (char*)arr)*ssize), (void*)((char*)arr + (int)(last - (char*)arr)*ssize), ssize);

        Void_Qsort(left, (int)(last - 1 - (char*)arr), ssize, compare);
        Void_Qsort(last + 1, (int)(right - 1 - (char*)last), ssize, compare);

    }
*/
void Qsort (int left, int right, void* arr, int ssize, int (*compare)(const void*, const void*))
    {
        assert (arr);

        if (left >= right)
            return;

        int mid = (left + right) / 2;
        Swap ((char*)arr + left * ssize, (char*)arr + mid * ssize, ssize);

        int last = left;
        int i = 0;
        //printf ("I am in qsort\n");
        for (i = left; i <= right; i++)
            if (compare ((void*)((char*)arr + left * ssize), (void*)((char*)arr + i * ssize)) > 0)
                Swap ((char*)arr + i * ssize, (char*)arr + (++last) * ssize, ssize);

        Swap ((char*)arr + left * ssize, (char*)arr + last * ssize, ssize);

        Qsort (left, last -  1, arr, ssize, compare);
        Qsort (last + 1, right, arr, ssize, compare);

    }
