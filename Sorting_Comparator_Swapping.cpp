#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "Onegin.h"

const int EOL = -1;
const int SOL =  1;

typedef const void* cvoid;

// функция сортировки строчек по алфавиту......................................

void Sorting (PTR* Pointers, int nPointer, Compare_func_t CmpFnc)
    {
    for (int i = 0; i < nPointer; i++)
        {
        assert (i < nPointer);
        for (int elem = 0; elem < nPointer - 1; elem++)
            {
            printf ("elem = <%d>\n", elem);
            printf ("nPointer = <%d>\n", nPointer);
            assert (elem < nPointer - 1);

            int result = CmpFnc ((const void*)(Pointers + elem), (const void*)(Pointers + elem + 1));
            if (result > 0)                                          // тогда замена строк между собой
                {
                printf ("Swapping:\n");
                Print (Pointers[elem]);
                printf ("and");
                Print (Pointers[elem + 1]);
                Swapping (&Pointers[elem], &Pointers[elem + 1]);
                printf ("After swapping:\n");
                Print (Pointers[elem]);
                printf ("and");
                Print (Pointers[elem + 1]);
                }
            printf ("\n");
            }
        }
    }

// это компаратор..............................................................

int Comparator (const void* voidParamFirst, const void* voidParamSecond)
    {
    const PTR paramFirst  = *((const PTR*)voidParamFirst );
    const PTR paramSecond = *((const PTR*)voidParamSecond);

    printf ("Comparing:\n");
    Print (paramFirst );
    printf ("Vs:\n");
    Print (paramSecond);

    int i = 0;                                                       // Index for First  String
    int j = 0;                                                       // Index for Second String

    SkipMarks (paramFirst , &i, SOL);
    SkipMarks (paramSecond, &j, SOL);

    printf ("paramFirst.lenString  = <%d>\n", paramFirst.lenString );
    printf ("paramSecond.lenstring = <%d>\n", paramSecond.lenString);

    for (; i < paramFirst.lenString && j < paramSecond.lenString; j++, i++)
        {
        assert (i < paramFirst.lenString );
        assert (j < paramSecond.lenString);
        printf ("<%c> Vs <%c> | <%d> Vs <%d>\n",*(paramFirst.PtrStart + i),
                                                *(paramSecond.PtrStart + j),
                                                *(paramFirst.PtrStart + i),
                                                *(paramSecond.PtrStart + j));

        if (toupper(*(paramFirst.PtrStart + i)) != toupper(*(paramSecond.PtrStart + j)))
                break;
        }
    printf ("return %d\n", (toupper(*paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j)));
    return toupper(*(paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j));
    }

// компаратор по концу строки..................................................

int EOLComparator (const void* voidParamFirst, const void* voidParamSecond)
    {
    const PTR paramFirst  = *((const PTR*)voidParamFirst );
    const PTR paramSecond = *((const PTR*)voidParamSecond);

    printf ("Comparing:\n");
    Print (paramFirst);
    printf ("Vs:\n");
    Print (paramSecond);

    int i = paramFirst.lenString;
    int j = paramSecond.lenString;

    SkipMarks (paramFirst,  &i, EOL);
    SkipMarks (paramSecond, &j, EOL);

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

// функция вывода строки по её структуре.......................................

void Print (PTR paramFirst)
    {
    printf ("lenString = <%d>\n", paramFirst.lenString);
    for (int j = 0; j <= paramFirst.lenString; j++)
        {
        assert (j <= paramFirst.lenString);
        printf ("%c", *(paramFirst.PtrStart + j));
        }
    printf ("\n");
    }

//  функция пропуска знаков, которые не являются буквами или цифрами в начале строки

void SkipMarks (PTR paramString, int* i, int deltai)
    {
    for (; !isalnum (paramString.PtrStart[*i]);)
        *i = *i + deltai;
    }

// функция обмена строк........................................................

void Swapping (PTR* paramFirst, PTR* paramSecond)
    {
    char* ptrSwapp = paramFirst->PtrStart;
    int   lenSwapp = paramFirst->lenString;

    paramFirst->PtrStart  = paramSecond->PtrStart;
    paramFirst->lenString = paramSecond->lenString;

    paramSecond->PtrStart  = ptrSwapp;
    paramSecond->lenString = lenSwapp;
    }
