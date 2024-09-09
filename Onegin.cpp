#include "TXLib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

// I have a commit!

_Bool Input (char text[MAX_ROWS][MAX_ELEM]);

void OutputText (char text[MAX_ROWS][MAX_ELEM]);

void RunComparator (char text[MAX_ROWS][MAX_ELEM]);

void Sorting (char text[MAX_ROWS][MAX_ELEM]);

_Bool Swapping (char* sFirst, char* sSecond);

//{
/// @brief   Comparator - функци€, котора€ сравнивает две строки
///                       и выводит разницу между первыми не равными
///                       элементами строки. “о есть показывает кака€
///                       из строк должна сто€ть раньше
/// @param   sFirst     - перва€ из сравниваемых строк
/// @param   sSecond    - втора€ из сравниваемых строк
///
/// @return  разницу между первыми не равными символами между строками
///          разница отрицательна, если строка должна сто€ть выше,
///          и положительна, если ниже
/// @code
///          Comparator (sFirst, sSecond);
/// @endcode
//}

int Comparator (char* sFirst, char* sSecond);

int main ()
    {
    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n\n");

    char text[MAX_ROWS][MAX_ELEM] = {};

    _Bool inputCorrect = Input (text);
    if (inputCorrect == 0)
        return -1;

    OutputText (text);

    //RunComparator (text);

    Sorting (text); // toupper dobavit + znaki propuskat

    OutputText (text);

    return 0;
    }

// функци€ считывани€ инфы из файла и загрузки еЄ в двумерный массив...........

_Bool Input (char text[MAX_ROWS][MAX_ELEM])
    {
    FILE* file = fopen("Onegin.txt", "r");

    if (file == NULL)
        {
        printf("File opening error");

        return 0;                                // main () return -1
        }

    int row = 0;

    while (row < MAX_ROWS)
        {
        assert (row < MAX_ROWS);
        if (fgets (text[row], MAX_ELEM, file) == NULL) // считывает из файла в двумерный массив
            break;

        char* newLine = strchr (text[row], '\n');
        if (newLine != NULL)
            {
            *newLine = '#';
            }

        row++;
        }

    fclose (file);

    txDump (text);

    return 1;
    }

// выводит текст ќнегина.......................................................

void OutputText (char text[MAX_ROWS][MAX_ELEM])
    {
    int row = 0;

    for (; row < MAX_ROWS; row++)
        {
        assert (row < MAX_ROWS);
        printf ("string %02d => <%s>\n", row, text[row]);
        }
    }

// функци€ сортировки строчек по алфавиту......................................

void Sorting (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int nIterations = 0; nIterations < MAX_ROWS; nIterations++)
        {
        assert (nIterations < MAX_ROWS);
        for (int row = 0; row < MAX_ROWS-1; row++)
            {
            printf ("row = <%d>\n", row);
            assert (row < MAX_ROWS-1);

            int result = Comparator (text[row], text[row+1]);
            if (result > 0)                                          // тогда замена строк между собой
                {
                if (Swapping (text[row], text[row + 1]))
                    printf ("Successful exchange!\n");
                }                                                    // теперь, если мен€ли строки, строка, котора€ позже по алфавиту,
                                                                     // находитс€ по адресу row + 1, значит в следующей итерации цикла
            }                                                        // эта строка будет сравниватьс€ со следующей строкой, значит мне
        }                                                            // нужен ещЄ один большой цикл, который позволит каждой строке га-
    }                                                                 // рантированно дойти до своего места в упор€доченном р€ду строк
// запускает сравнение всех соседних строчек...................................

void RunComparator (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int row = 0; row < MAX_ROWS - 1; row++)
        {
        assert (row < MAX_ROWS);
        printf ("\nsFirst  = text[%d]\n"
                "sSecond = text[%d]",
                row, row+1);

        int result = Comparator (text[row], text[row+1]);

        printf ("result = %d\n", result);
        }
    }

// это компаратор..............................................................

int Comparator ( char* sFirst, char* sSecond)
    {
    int indexElem = 0;
    printf ("\nindexElem before the loop = %d\n\n", indexElem);

    printf ("Compare:\n<%s>\nvs\n<%s>\n", sFirst, sSecond);

    int iIndexElem = 0;
    int jIndexElem = 0;
    for (; !isalnum (sFirst[iIndexElem]); iIndexElem++)
       continue;
    for (; !isalnum (sSecond[jIndexElem]); jIndexElem++)
       continue;

    while (1)
        {
        printf ("'%c' vs '%c' -- %03d vs %03d\n", toupper(sFirst[iIndexElem]), toupper(sSecond[jIndexElem]), toupper(sFirst[iIndexElem]), toupper(sSecond[jIndexElem]));

        if (toupper(sFirst[iIndexElem]) != toupper(sSecond[jIndexElem]) || (sFirst[iIndexElem] == sSecond[jIndexElem] && sSecond[jIndexElem] == '\0'))
            break;

        iIndexElem++;
        jIndexElem++;
        }                                                    // cycle => loop (est)

    printf ("iIndexElem after the loop %d\n", iIndexElem);
    printf ("jIndexElem after the loop %d\n", jIndexElem);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", iIndexElem, jIndexElem, toupper(sFirst[iIndexElem]) - toupper(sSecond[jIndexElem]));

    return toupper(sFirst[iIndexElem]) - toupper(sSecond[jIndexElem]);
    }

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
    printf ("Row swap!\n");
    printf ("After swap:\n<%s>\nvs\n<%s>\n", sFirst, sSecond);
    return 1;
    }



