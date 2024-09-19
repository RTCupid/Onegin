#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "Onegin.h"

// функция сортировки строчек по алфавиту......................................

void Sorting (PTR* Pointers, int nPointer)
    {
    for (int i = 0; i < nPointer; i++)
        {
        assert (i < nPointer);
        for (int row = 0; row < nPointer - 1; row++)
            {
            printf ("row = <%d>\n", row);
            assert (row < nPointer - 1);

            int result = Comparator (Pointers[row], Pointers[row + 1]);
            if (result > 0)                                          // тогда замена строк между собой
                {
                printf ("Swapping:\n");
                Print (

                Swapping
                }

            }
        }
    }

// это компаратор..............................................................

int Comparator (PTR paramFirst, PTR paramSecond)
    {
    int lenFirstRow  = paramFirst.PtrEnd - paramFirst.PtrStart;
    int lenSecondRow = paramSecond.PtrEnd - paramSecond.PtrStart;

    printf ("Comparing:\n");
    Print (paramFirst, lenFirstRow);
    printf ("Vs:\n");
    Print (paramSecond, lenSecondRow);

    int i = 0;                                                       // Index for First  String
    int j = 0;                                                       // Index for Second String

    for (; i < lenFirstRow; i++)
        {
        assert (i , lenFirstRow);
        for (; j < lenSecondRow; j++)
            {
            assert (j < lenSecondRow);
            while (*(paramFirst.PtrStart + i) == *(paramSecond.PtrStart + j))
                continue;
            }
        }

    return *(paramFirst.PtrStart + i) - *(paramSecond.PtrStart + j);
    }

void Print (PTR paramFirst, int lenString)
    {
    printf ("lenString = <%d>\n", lenString);
    for (int j = 0; j <= lenString; j++)
        {
        assert (j <= lenString);
        printf ("%c", *(paramFirst.PtrStart + j));
        }
    printf ("\n");
    }



// функция обмена строк........................................................

_Bool Swapping (char* sFirst, char* sSecond)
    {
    char charForSwap = '*';
    int indexElem = 0;
    while (indexElem < MAX_ELEM || (sFirst[indexElem] == sSecond[indexElem] && sFirst[indexElem] == '\0'))
        {
        assert (indexElem < MAX_ELEM);
        charForSwap = sFirst[indexElem];
        sFirst[indexElem] = sSecond[indexElem];
        sSecond[indexElem] = charForSwap;

        indexElem++;
        }
    printf ("Row exchange:\n");
    printf ("<%s>\nvs\n<%s>\n", sFirst, sSecond);
    return 1;
    }

//  функция пропуска знаков, которые не являются буквами или цифрами в начале строки

_Bool SkipMarks (char* sFirst, char* sSecond, int* iIndexElem, int* jIndexElem)
    {
    for (; !isalnum (sFirst[*iIndexElem]);)
        *iIndexElem = *iIndexElem + 1;

    for (; !isalnum (sSecond[*jIndexElem]);)
        *jIndexElem = *jIndexElem + 1;

    if (*iIndexElem != 0 || *jIndexElem != 0)
        return 1;
    return 0;
    }
