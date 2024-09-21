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

typedef int (*Compare_func_t)(const void*, const void*);

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

    if (CorrectMakePointers == 0)
        {
        printf ("Error MakePointers");
        return -1;
        }

    //qsort (Pointers, nPointer,sizeof (PTR), Comparator);

    Sorting (Pointers, nPointer, Comparator);

    printf ("After Sorting\n\n");
    Print (Pointers[2]);
    Print (Pointers[3]);

    FILE* file = fopen ("InputOnegin.txt", "w");

    OutputText (Pointers, nPointer,file);                            // toupper dobavit + znaki propuskat (est)+

    //qsort (Pointers, nPointer,sizeof (PTR), EOLComparator);

    Sorting (Pointers, nPointer, EOLComparator);

    OutputText (Pointers, nPointer, file);

    WriteTheOriginalOfPushkinGreatestPoemEugeneOnegin (Onegin, file);

    fclose (file);

    return 0;
    }

//
int MakePointers (char** Onegin, size_t* sizeOfFile, int* nPointer, PTR** Pointers, PTR* ParamString, const char* nameFile)
    {
    InputOnegin (Onegin, sizeOfFile, nameFile);

    int nRows = 0;

    char symbol = '\n';

    CounterSymbol (&nRows, *Onegin, *sizeOfFile, symbol);

    *Pointers = (PTR*)calloc (nRows * 2, sizeof (char*));        // каллокаю массив указателей

    if (*Pointers == NULL)
        {
        printf ("Error calloc Pointers");
        return 0;
        }

    InitialisatorPointers (*sizeOfFile, *Pointers, *Onegin, ParamString, nPointer);

    printf ("nPointer = <%d>\n", *nPointer);

    return 1;
    }

// читаю из файла в буффер текст Онегина и определяю размер буффера

void InputOnegin (char** Onegin, size_t* sizeOfFile, const char* nameFile)
    {
    struct stat fileInf = {};

    SizeFile (&fileInf, nameFile);

    *Onegin = (char*)calloc (fileInf.st_size + 1, sizeof(char));     // каллочу буффер, чтобы в него считать текст

    FILE* file = fopen (nameFile, "rt");

    if (file == NULL)
        {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror(nameFile);
        }

    *sizeOfFile = fread (*Onegin, sizeof (char), fileInf.st_size, file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (*sizeOfFile == 0)
        {
        printf ("errno = <%d>\n", errno);
        perror (nameFile);
        }

    printf ("\n%s\n", *Onegin);                                      // вывожу начальный текст Онегина

    fclose (file);                                                   // закрываю файл

    printf ("sizeOfFile = <%zu>\n\n", *sizeOfFile);
    }

// функция определения размера файла с помощью стата

void SizeFile (struct stat* fileInf, const char* nameFile)
    {
    int err = stat (nameFile, fileInf);
    if (err != 0)
        printf("Stat err %d\n", err);

    printf ("\n%ld\n", (*fileInf).st_size);
    printf ("count of char = %ld\n", (*fileInf).st_size / sizeof (char));
    }

// считает количество строк, чтобы каллокнуть массив указателей

void CounterSymbol (int* nRows, char* Onegin, size_t sizeOfFile, char symbol)
    {
    for (unsigned int i = 0; i < sizeOfFile; i++)                    // посимвольно зачем-то вывожу начальный текст Онегина
        {                                                            // точно, я не просто вывожу, а параллельно считаю количество
        if (Onegin[i] == symbol)                                     // строк, равное кличеству '\n'
            {
            printf ("Onegin[%d] = <'%c'>\n", i, symbol);
            *nRows = *nRows + 1;
            }
        else
            printf ("Onegin[%d] = <%c>\n", i, Onegin[i]);
        }

    printf ("nRow = <%d>\n", *nRows);
    }

// ф-я инициализирует массив указателей

void InitialisatorPointers (size_t sizeOfFile, PTR* Pointers, char* Onegin, struct PTR* ParamString , int* nPointer)
    {
    printf ("\nInitialization of Pointers:\n\n");

    printf ("&ParamString = <%p>\n", ParamString);
    printf ("&Pointers    = <%p>\n", Pointers);

    ParamString->PtrStart = Onegin;

    for (unsigned int i = 0; i < sizeOfFile; i++)
        {
        if (Onegin[i] == '\n')
            {
            ParamString->lenString = &Onegin[i - 1] - ParamString->PtrStart;
            Pointers[*nPointer] = *ParamString;
            *nPointer = *nPointer + 1;
            ParamString->PtrStart = &Onegin[i + 1];
            }
        }

    printf ("nPointer = <%d>\n", *nPointer);
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

void WriteTheOriginalOfPushkinGreatestPoemEugeneOnegin (char* Onegin, FILE* file)
    {
    fputs (Onegin, file);
    }





