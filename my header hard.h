#ifndef MY_HEADER_H_INCLUDED
#define MY_HEADER_H_INCLUDED

//#define Debug


#ifdef Debug
#define GO_GREET if (0)
#define PRINTF printf
#else
#define PRINTF if (0) printf
#define GO_GREET
#endif // My_Debug

typedef struct {
    char* start;
    char* end;
    }poem_line;

void Greet (char** file_read, char** file_write);

long Str_Length (char* str);

void File_Clean (const char* file_name);

long Symb_Counter (char* str, char c);

int IsLetter (char c);

poem_line* StringMaker (char* str, int length, int amount);

long ReadFileLength (const char* file);

long ReadFile (const char* name, char* str, int length);

void Qsort (int left, int right, void* arr, int ssize, int (*compare)(const void*, const void*));

//void Void_Qsort (void  *arr, size_t amount, size_t ssize, int (*compare)(const void*, const void*));

int Is_Larger_Str (const void* str1, const void* str2);

int Is_Larger_Str_Reverse (const void* str1, const void* str2);

void Swap (void* a, void* b, int sizze);

poem_line* Point_Maker (int length);

char Down (char c);

int WriteFile (const char *file, int num, poem_line pointer[]);

poem_line* Point_Maker (int length);

char* Create_Str (long* length, const char* file_read);


//TESTS
void UniTest (void);

void File_Clean_Test (void);

void Str_Length_Test (void);

void Qsort_Test (void);

void Is_Larger_Str_Test (void);

void Is_Larger_Str_Reverse_Test (void);

#endif // MY_HEADER_H_INCLUDED


