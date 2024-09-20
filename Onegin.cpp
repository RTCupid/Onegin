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

    InputOnegin (&Onegin, &sizeOfFile);

    int nRows = 0;

    CounterRow (&nRows, Onegin, sizeOfFile);

    PTR* Pointers = (PTR*)calloc (nRows * 2, sizeof (char*));         // каллокаю массив указателей

    int nPointer = 0;

    InitialisatorPointers (sizeOfFile, Pointers, Onegin, &ParamString, &nPointer);

    printf ("nPointer = <%d>\n", nPointer);

    Sorting (Pointers, nPointer);

    printf ("After Sorting\n\n");
    Print (Pointers[2]);
    Print (Pointers[3]);

    FILE* file = fopen ("InputOnegin.txt", "w");

    OutputText (Pointers, nPointer,file);                                                  // toupper dobavit + znaki propuskat (est)+

    EOLSorting (Pointers, nPointer);

    OutputText (Pointers, nPointer, file);

    fputs (Onegin, file);

    fclose (file);

    return 0;
    }

// читаю из файла в буффер текст Онегина и определяю размер буффера

void InputOnegin (char** Onegin, size_t* sizeOfFile)
    {
    struct stat fileInf = {};

    SizeFile (&fileInf);

    *Onegin = (char*)calloc (fileInf.st_size + 1, sizeof(char));     // каллочу буффер, чтобы в него считать текст

    FILE* file = fopen ("Onegin.txt", "rt");

    if (file == NULL)
        {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror("Onegin.txt\n");
        }

    *sizeOfFile = fread (*Onegin, sizeof (char), fileInf.st_size, file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (*sizeOfFile == 0)
        {
        printf ("errno = <%d>\n", errno);
        perror ("Onegin.txt");
        }

    printf ("\n%s\n", *Onegin);                                      // вывожу начальный текст Онегина

    fclose (file);                                                   // закрываю файл

    printf ("sizeOfFile = <%zu>\n\n", *sizeOfFile);
    }

// функция определения размера файла с помощью стата

void SizeFile (struct stat* fileInf)
    {
    int err = stat ("Onegin.txt", fileInf);
    if (err != 0)
        printf("Stat err %d\n", err);

    printf ("\n%ld\n", (*fileInf).st_size);
    printf ("count of char = %ld\n", (*fileInf).st_size / sizeof (char));
    }

// считает количество строк, чтобы каллокнуть массив указателей

void CounterRow (int* nRows, char* Onegin, size_t sizeOfFile)
    {
    for (unsigned int i = 0; i < sizeOfFile; i++)                    // посимвольно зачем-то вывожу начальный текст Онегина
        {                                                            // точно, я не просто вывожу, а параллельно считаю количество
        if (Onegin[i] == '\n')                                       // строк, равное кличеству '\n'
            {
            printf ("Onegin[%d] = <'\\n'>\n", i);
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
            ParamString->lenString   = &Onegin[i - 1] - ParamString->PtrStart;
            Pointers[*nPointer]   =  *ParamString;
            *nPointer = *nPointer + 1;
            ParamString->PtrStart = &Onegin[i + 1];
            }
        }

    printf ("nPointer = <%d>\n", *nPointer);
    }

// функция вывода текста по массиву структур...................................

void OutputText (PTR* Pointers, int nPointer, FILE* file)
    {
    char ch = '\0';
    for (int i = 0; i < nPointer; i++)
        {
        assert (i < nPointer);
        Print (Pointers[i]);

        for (int j = 0; j <= (Pointers[i]).lenString; j++)
            {
            assert (j <= (Pointers[i]).lenString);
            ch = *((Pointers[i]).PtrStart + j);
            fputc (ch, file);
            }
        ch = '\n';
        fputc (ch, file);
        printf ("\n");
        }
    fputc ('\n', file);
    }

// сортировка по концу строки..................................................

void EOLSorting (PTR* Pointers, int nPointer)
    {
    for (int i = 0; i < nPointer; i++)
        {
        assert (i < nPointer);
        for (int row = 0; row < nPointer - 1; row++)
            {
            printf ("row = <%d>\n", row);
            printf ("nPointer = <%d>\n", nPointer);
            assert (row < nPointer - 1);

            int result = EOLComparator (Pointers[row], Pointers[row + 1]);
            if (result > 0)                                          // тогда замена строк между собой
                {
                printf ("Swapping:\n");
                Print (Pointers[row]);
                printf ("and");
                Print (Pointers[row + 1]);
                Swapping (&Pointers[row], &Pointers[row + 1]);
                printf ("After swapping:\n");
                Print (Pointers[row]);
                printf ("and");
                Print (Pointers[row + 1]);
                }
            printf ("\n");
            }
        }
    }

// компаратор по концу строки..................................................

int EOLComparator (PTR paramFirst, PTR paramSecond)
    {
    printf ("Comparing:\n");
    Print (paramFirst);
    printf ("Vs:\n");
    Print (paramSecond);

    int i = paramFirst.lenString;
    int j = paramSecond.lenString;

    EOLSkipMarks (paramFirst,  &i);
    EOLSkipMarks (paramSecond, &j);

    while (1)
        {
        printf ("<%c> Vs <%c> | <%d> Vs <%d>\n", *(paramFirst.PtrStart + i), *(paramSecond.PtrStart + j), *(paramFirst.PtrStart + i), *(paramSecond.PtrStart + j));

        if (toupper (*(paramFirst.PtrStart + i)) != toupper (*(paramSecond.PtrStart + j)) || i == 0 || j == 0)
            {
            break;
            }
        i--;
        j--;
        }
    printf ("return *(paramFirst.PtrStart + i) - *(paramSecond.PtrStart + j) = %d\n", *(paramFirst.PtrStart + i) - *(paramSecond.PtrStart + j));
    return *(paramFirst.PtrStart + i) - *(paramSecond.PtrStart + j);
    }

// пропускает знаки с конца строки.............................................

void EOLSkipMarks (PTR paramString, int* i)
    {
    for (; !isalnum (paramString.PtrStart[*i]);)
        *i = *i - 1;
    }





