#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


#include "Onegin.h"

const int EOL = -1;
const int SOL =  1;

// функция сортировки строчек по алфавиту......................................

void Sorting (void* Pointers, int nPointer, size_t sizeElem, Compare_func_t CmpFnc, Swapping_func_t SwpFnc)
    {
    DBG printf ("nPointer = <%d>\n", nPointer);
    for (int i = 0; i < nPointer; i++)
        {
        DBG printf ("i = <%d>\nnPointer = <%d>", i, nPointer);
        assert (i < nPointer);
        for (int elem = 0; elem < nPointer - 1; elem++)
            {
            DBG printf ("elem = <%d>\n", elem);
            DBG printf ("nPointer = <%d>\n", nPointer);

            assert (elem < nPointer - 1);
            DBG printf ("Pointers = <%p>\n", Pointers);
            int result = CmpFnc ((const void*)((char*)Pointers + elem * sizeElem), (const void*)((char*)Pointers + (elem + 1) * sizeElem));
            DBG printf ("result = %d\n", result);

            if (result > 0)                                          // тогда замена строк между собой
                {
                DBGPTR printf ("Swapping:\n");
                DBGPTR Print (*((PTR*)Pointers + elem));
                DBGPTR printf ("and\n");
                DBGPTR Print (*((PTR*)Pointers + elem + 1));
                SwpFnc ((void*)((char*)Pointers + elem * sizeElem), (void*)((char*)Pointers + (elem + 1) * sizeElem));
                DBGPTR printf ("After swapping:\n");
                DBGPTR Print (*((PTR*)Pointers + elem));
                DBGPTR printf ("and\n");
                DBGPTR Print (*((PTR*)Pointers + elem + 1));
                }
            DBG printf ("\n");
            }
        }
    }

// это компаратор..............................................................

int Comparator (const void* voidParamFirst, const void* voidParamSecond)
    {
    DBG printf ("Start comparator\n");
    DBG printf ("(const PTR*)voidParamFirst = <%p>\n", (const PTR*)voidParamFirst);

    const PTR paramFirst  = *((const PTR*)voidParamFirst );
    const PTR paramSecond = *((const PTR*)voidParamSecond);

    DBG printf ("Comparing:\n");
    DBG Print (paramFirst );
    DBG printf ("Vs:\n");
    DBG Print (paramSecond);

    int i = 0;                                                       // Index for First  String
    int j = 0;                                                       // Index for Second String

    SkipMarks (paramFirst , &i, SOL);
    SkipMarks (paramSecond, &j, SOL);

    DBG printf ("paramFirst.lenString  = <%d>\n", paramFirst.lenString );
    DBG printf ("paramSecond.lenstring = <%d>\n", paramSecond.lenString);

    for (; i < paramFirst.lenString && j < paramSecond.lenString; j++, i++)
        {
        assert (i < paramFirst.lenString );
        assert (j < paramSecond.lenString);
        DBG printf ("<%c> Vs <%c> | <%d> Vs <%d>\n",*(paramFirst.PtrStart + i ),
                                                    *(paramSecond.PtrStart + j),
                                                    *(paramFirst.PtrStart + i ),
                                                    *(paramSecond.PtrStart + j));

        if (toupper(*(paramFirst.PtrStart + i)) != toupper(*(paramSecond.PtrStart + j)))
                break;
        }
    DBG printf ("return *(paramFirst.PtrStart + %d) - *(paramSecond.PtrStart + %d) = %d\n", i, j, toupper(*(paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j)));
    return toupper(*(paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j));
    }

// компаратор по концу строки..................................................

int EOLComparator (const void* voidParamFirst, const void* voidParamSecond)
    {
    const PTR paramFirst  = *((const PTR*)voidParamFirst );
    const PTR paramSecond = *((const PTR*)voidParamSecond);

    DBG printf ("EOLComparing:\n");
    DBG Print (paramFirst);
    DBG printf ("Vs:\n");
    DBG Print (paramSecond);

    int i = paramFirst.lenString;
    int j = paramSecond.lenString;

    SkipMarks (paramFirst,  &i, EOL);
    SkipMarks (paramSecond, &j, EOL);

    DBG printf ("paramFirst.lenString  = <%d>\n", paramFirst.lenString );
    DBG printf ("paramSecond.lenstring = <%d>\n", paramSecond.lenString);

    while (1)
        {
        DBG printf ("<%c> Vs <%c> | <%d> Vs <%d>\n", *(paramFirst.PtrStart + i), *(paramSecond.PtrStart + j), *(paramFirst.PtrStart + i), *(paramSecond.PtrStart + j));

        if (toupper (*(paramFirst.PtrStart + i)) != toupper (*(paramSecond.PtrStart + j)) || i == 0 || j == 0)
            {
            break;
            }
        i--;
        j--;
        }
    DBG printf ("return *(paramFirst.PtrStart + %d) - *(paramSecond.PtrStart + %d) = %d\n", i, j, toupper(*(paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j)));
    return toupper(*(paramFirst.PtrStart + i)) - toupper(*(paramSecond.PtrStart + j));
    }

// функция вывода строки по её структуре.......................................

void Print (PTR paramFirst)
    {
    DBG printf ("lenString = <%d>\n", paramFirst.lenString);
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

void SwappingPTR (void* voidParamFirst, void* voidParamSecond)
    {
    PTR* paramFirst  = (PTR*)voidParamFirst ;
    PTR* paramSecond = (PTR*)voidParamSecond;

    DBG printf ("in function Swapping:\n");
    DBG Print (*paramFirst );
    DBG printf ("and\n");
    DBG Print (*paramSecond);

    char* ptrSwapp = paramFirst->PtrStart ;
    int   lenSwapp = paramFirst->lenString;

    paramFirst->PtrStart  = paramSecond->PtrStart ;
    paramFirst->lenString = paramSecond->lenString;

    paramSecond->PtrStart  = ptrSwapp;
    paramSecond->lenString = lenSwapp;
    }
