#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "Onegin.h"

typedef int  (*Compare_func_t )(const void*, const void*);
typedef void (*Swapping_func_t)(const void*, const void*);

int main ()
    {
    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n\n");

    struct PTR ParamString  {
                            NULL,
                            0
                            };

    char* Onegin = NULL;
    size_t sizeOfFile = 0;
    int nPointer = 0;
    PTR* Pointers = NULL;
    const char nameFile[] = "Onegin.txt";

    int CorrectMakePointers = 0;

    CorrectMakePointers = MakePointers (&Onegin, &sizeOfFile, &nPointer, &Pointers, &ParamString, nameFile); // make PTR* Pointers and his param+

    if (CorrectMakePointers != 1)
        {
        printf ("Error MakePointers");
        return -1;
        }

    //qsort (Pointers, nPointer,sizeof (PTR), Comparator);

    Sorting (Pointers, nPointer, sizeof (PTR), Comparator);

    DBG printf ("After Sorting\n\n");
    DBG Print (Pointers[2]);
    DBG Print (Pointers[3]);

    FILE* file = fopen ("InputOnegin.txt", "w");

    printf ("Sorted text:..............................................................................................\n\n");

    OutputText (Pointers, nPointer,file);                            // toupper dobavit + znaki propuskat (est)+

    //qsort (Pointers, nPointer,sizeof (PTR), EOLComparator);

    Sorting (Pointers, nPointer, sizeof (PTR), EOLComparator);

    printf ("EOLSorted text:...........................................................................................\n\n");

    OutputText (Pointers, nPointer, file);

    WriteTheOriginalOfPushkinGreatestPoemEugeneOnegin (Onegin, file);

    fclose (file);

    return 0;
    }

//
int MakePointers (char** Onegin, size_t* sizeOfFile, int* nPointer, PTR** Pointers, PTR* ParamString, const char* nameFile)
    {
    if (!InputOnegin (Onegin, sizeOfFile, nameFile))
        return -1;

    int nRows = 0;

    char symbol = '\n';

    CounterSymbol (&nRows, *Onegin, *sizeOfFile, symbol);

    *Pointers = (PTR*)calloc (nRows * 2, sizeof (char*));        // каллокаю массив указателей

    if (*Pointers == NULL)
        {
        printf ("Error calloc Pointers");
        return -1;
        }

    InitialisatorPointers (*sizeOfFile, *Pointers, *Onegin, ParamString, nPointer);

    DBG printf ("nPointer = <%d>\n", *nPointer);

    return 1;
    }

// читаю из файла в буффер текст Онегина и определяю размер буффера

bool InputOnegin (char** Onegin, size_t* sizeOfFile, const char* nameFile)
    {
    struct stat fileInf = {};

    SizeFile (&fileInf, nameFile);

    *Onegin = (char*)calloc (fileInf.st_size + 1, sizeof(char));     // каллочу буффер, чтобы в него считать текст

    if (*Onegin == NULL)
        {
        printf ("Onegin = NULL");
        return 0;
        }

    FILE* file = fopen (nameFile, "rt");

    if (file == NULL)
        {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror(nameFile);
        return 0;
        }

    *sizeOfFile = fread (*Onegin, sizeof (char), fileInf.st_size, file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (*sizeOfFile == 0)
        {
        printf ("errno = <%d>\n", errno);
        perror (nameFile);
        return 0;
        }

    printf ("\n%s\n", *Onegin);                                      // вывожу начальный текст Онегина

    fclose (file);                                                   // закрываю файл

    DBG printf ("sizeOfFile = <%zu>\n\n", *sizeOfFile);
    return 1;
    }

// функция определения размера файла с помощью стата

void SizeFile (struct stat* fileInf, const char* nameFile)
    {
    int err = stat (nameFile, fileInf);
    if (err != 0)
        printf("Stat err %d\n", err);

    DBG printf ("\n%ld\n", (*fileInf).st_size);
    DBG printf ("count of char = %ld\n", (*fileInf).st_size / sizeof (char));
    }

// считает количество строк, чтобы каллокнуть массив указателей

void CounterSymbol (int* nRows, char* Onegin, size_t sizeOfFile, char symbol)
    {
    for (unsigned int i = 0; i < sizeOfFile; i++)                    // посимвольно зачем-то вывожу начальный текст Онегина
        {                                                            // точно, я не просто вывожу, а параллельно считаю количество
        assert (i < sizeofFile);

        if (Onegin[i] == symbol)                                     // строк, равное кличеству '\n'
            {
            DBG printf ("Onegin[%d] = <'%c'>\n", i, symbol);
            *nRows = *nRows + 1;
            }
        else
            DBG printf ("Onegin[%d] = <%c>\n", i, Onegin[i]);
        }

    DBG printf ("nRow = <%d>\n", *nRows);
    }

// ф-я инициализирует массив указателей

void InitialisatorPointers (size_t sizeOfFile, PTR* Pointers, char* Onegin, struct PTR* ParamString , int* nPointer)
    {
    printf ("\nInitialization of Pointers:\n\n");

    DBG printf ("&ParamString = <%p>\n", ParamString);
    DBG printf ("&Pointers    = <%p>\n", Pointers);

    ParamString->PtrStart = Onegin;

    for (unsigned int i = 0; i < sizeOfFile; i++)
        {
        assert (i < sizeOfFile);

        if (Onegin[i] == '\n')
            {
            ParamString->lenString = &Onegin[i - 1] - ParamString->PtrStart;
            Pointers[*nPointer] = *ParamString;
            *nPointer = *nPointer + 1;
            ParamString->PtrStart = &Onegin[i + 1];
            }
        }

    DBG printf ("nPointer = <%d>\n", *nPointer);
    }

// функция вывода текста по массиву структур...................................

void OutputText (PTR* Pointers, int nPointer, FILE* file)
    {
    for (int i = 0; i < nPointer; i++)
        {
        assert (i < nPointer);

        Print (Pointers[i]);
        printf ("\n");

        fwrite ((Pointers[i]).PtrStart, (Pointers[i]).lenString + 2, sizeof(char), file);
        }
    fputc ('\n', file);
    }

// write original text.........................................................

void WriteTheOriginalOfPushkin\
GreatestPoem\
EugeneOnegin (char* Onegin, FILE* file)
    {
    fputs (Onegin, file);
    }





