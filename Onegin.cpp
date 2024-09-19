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
    sruct ParamString {
                      char* PtrStart;
                      char* PtrEnd:
                      };

    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n\n");

    char* Onegin = NULL;
    size_t sizeOfFile = 0;

    InputOnegin (&Onegin, &sizeOfFile);

    int nRows = 0;

    CounterRow (&nRows, Onegin, sizeOfFile);

    char** Pointers = (char**)calloc (nRows * 2, sizeof (char*));         // каллокаю массив указателей

    InitialisatorPointers (sizeOfFile, Pointers, Onegin);

    /*char text[MAX_ROWS][MAX_ELEM] = {};                            // здесь я создавал и заполнял двумерный массив

    _Bool inputCorrect = Input (text);
    if (inputCorrect == 0)
        return -1;*/

    //OutputText (text);

    Sorting (Pointers, nRows);                                                  // toupper dobavit + znaki propuskat (est)

    /*OutputText (text);

    EOLSorting (text);

    OutputText (text);*/

    return 0;
    }

// читаю из файла в буффер текст Онегина и определяю размер буффера

void InputOnegin (char** Onegin, size_t* sizeOfFile)
    {
    struct stat fileInf = {};

    int err = stat ("Onegin.txt", &fileInf);
    if (err != 0)
        printf("Stat err %d\n", err);

    printf ("\n%ld\n", fileInf.st_size);
    printf ("count of char = %ld\n", fileInf.st_size / sizeof (char));

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


// ф-я инициализирует массив указателей

void InitialisatorPointers (size_t sizeOfFile, char** Pointers, char* Onegin)
    {
    int nPointer = 1;

    printf ("\nInitialization of Pointers:\n\n");

    Pointers[0] = Onegin;
    printf ("PointerStart of Row № %d = <%p>\n", 0, Pointers[0]);

    for (unsigned int i = 0; i < sizeOfFile; i++)                    // прохожу весь массив с текстом Онегина и заношу в массив указателей
        {                                                            // все элементы, которые следуют за '\n'
        if (Onegin[i] == '\n')
            {
            Pointers[nPointer] = &Onegin[i - 1];
            Pointers[nPointer + 1] = &Onegin[i + 1];
            printf ("PointerEnd   of Row № %d = <%p>\n", nPointer, Pointers[nPointer]);
            printf ("PointerStart of Row № %d = <%p>\n", nPointer , Pointers[nPointer + 1]); // вывожу какими инициализируются элементы массива указателей
            nPointer = nPointer + 2;
            }
        }

    printf ("\nPointers:\n\n");

    char* Pointer = NULL;

    for (int n = 0; n < nPointer; n += 2)                               // вывожу все элементы массива указателей, сравниваю правильно ли
        {                                                            // вывожу то, что было инициализировано (правильно)
        printf ("n = <%d> | ", n);
        assert (n < nPointer);
        Pointer = Pointers[n];
        printf ("Pointers[%d]  = <%p>\n", n, Pointer);
        }
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


// ������� ���������� �� ����� ������..........................................

void EOLSorting (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int nIterations = 0; nIterations < MAX_ROWS; nIterations++)
        {
        assert (nIterations < MAX_ROWS);
        for (int row = 0; row < MAX_ROWS-1; row++)
            {
            printf ("row = <%d>\n", row);
            assert (row < MAX_ROWS-1);

            int result = EOLComparator (text[row], text[row+1]);
            if (result > 0)                                          // ����� ������ ����� ����� �����
                {
                if (Swapping (text[row], text[row + 1]))
                    printf ("Successful exchange!\n");
                }
            }
        }
    }

// ������� ���������� ��� ������ � ���������� �������, ������� � ����� ������..

int EOLComparator (char* sFirst, char* sSecond)
    {
    printf ("\nCompare:\n<%s>\nvs\n<%s>\n", sFirst, sSecond);

    int iIndexElem = 0;
    int jIndexElem = 0;

    for (; sFirst[iIndexElem] != '\0'; iIndexElem++)                 // ������� ����� ����� ������
        continue;
    for (; sSecond[jIndexElem] != '\0'; jIndexElem++)                // ������� ����� ����� ������
        continue;

    if (EOLSkipMarks (sFirst, sSecond, &iIndexElem, &jIndexElem))
        {
        printf ("Succesfull skipping marks!\n");
        printf ("After skipping:\niIndexElem = %d;"
                               "\njIndexElem = %d;\n",
                iIndexElem, jIndexElem);
        }

    printf ("iIndexElem before the loop = %d\n", iIndexElem);
    printf ("jIndexElem before the loop = %d\n", jIndexElem);

    while (1)
        {
        printf ("'%c' vs '%c' -- %03d vs %03d\n", toupper(sFirst[iIndexElem]), toupper(sSecond[jIndexElem]), toupper(sFirst[iIndexElem]), toupper(sSecond[jIndexElem]));

        if (toupper(sFirst[iIndexElem]) != toupper(sSecond[jIndexElem]) || (iIndexElem == jIndexElem && jIndexElem == 0))
            break;

        iIndexElem--;
        jIndexElem--;
        }

    printf ("iIndexElem after the loop %d\n", iIndexElem);
    printf ("jIndexElem after the loop %d\n", jIndexElem);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", iIndexElem, jIndexElem, toupper(sFirst[iIndexElem]) - toupper(sSecond[jIndexElem]));

    return toupper(sFirst[iIndexElem]) - toupper(sSecond[jIndexElem]);
    }

//

_Bool EOLSkipMarks (char* sFirst, char* sSecond, int* iIndexElem, int* jIndexElem)
    {
    int startiIndex = *iIndexElem;
    int startjIndex = *jIndexElem;

    for (; !isalnum (sFirst[*iIndexElem]);)
        *iIndexElem = *iIndexElem - 1;

    for (; !isalnum (sSecond[*jIndexElem]);)
        *jIndexElem = *jIndexElem - 1;

    if (*iIndexElem != startiIndex || *jIndexElem != startjIndex)
        return 1;
    return 0;
    }








