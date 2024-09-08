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

//{
/// @brief   Comparator - функция, которая сравнивает две строки
///                       и выводит разницу между первыми не равными
///                       элементами строки. То есть показывает какая
///                       из строк должна стоять раньше
/// @param   sFirst     - первая из сравниваемых строк
/// @param   sSecond    - вторая из сравниваемых строк
///
/// @return  разницу между первыми не равными символами между строками
///          разница отрицательна, если строка должна стоять выше,
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

// функция считывания инфы из файла и загрузки её в двумерный массив...........

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

// выводит текст Онегина.......................................................

void OutputText (char text[MAX_ROWS][MAX_ELEM])
    {
    int row = 0;

    for (; row < MAX_ROWS; row++)
        {
        assert (row < MAX_ROWS);
        printf ("string %02d => <%s>\n", row, text[row]);
        }
    }

// функция сортировки строчек по алфавиту......................................

void Sorting (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int nIterations = 0; nIterations < MAX_ROWS; nIterations++)
        {
        assert (nIterations < MAX_ROWS);
        for (int row = 0; row < MAX_ROWS-1; row++)
            {
            printf ("row = <%d>\n", row);                    // не инициализирована переменная nString (когда она называлась
            assert (row < MAX_ROWS-1);                           // row было тоже самое)

            int result = Comparator (text[row], text[row+1]);
            if (result > 0)                                          // тогда замена строк между собой
                {
                char charForSwap = '*';
                int indexElem = 0;
                while (indexElem < MAX_ELEM || (text[row][indexElem] == text[row+1][indexElem] && text[row][indexElem] == '\0'))
                    {
                    assert (indexElem < MAX_ELEM);
                    charForSwap = text[row][indexElem];
                    text[row][indexElem] = text[row+1][indexElem];
                    text[row+1][indexElem] = charForSwap;

                    indexElem++;
                    }
                }                                                    // теперь, если меняли строки, строка, которая позже по алфавиту,
                                                                     // находится по адресу row + 1, значит в следующей итерации цикла
            }                                                        // эта строка будет сравниваться со следующей строкой, значит мне
        }                                                            // нужен ещё один большой цикл, который позволит каждой строке га-
    }                                                                 // рантированно дойти до своего места в упорядоченном ряду строк
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
    printf ("\nindexElem before the loop = %d\n", indexElem);

    while (1)
        {
        printf ("'%c' vs '%c' -- %03d vs %03d\n", sFirst[indexElem], sSecond[indexElem], sFirst[indexElem], sSecond[indexElem]);
        if (sFirst[indexElem] != sSecond[indexElem] || (sFirst[indexElem] == sSecond[indexElem] && sSecond[indexElem] == '\0'))
            break;
        indexElem++;
        }                                                    // cycle => loop (est)

    printf ("indexElem after the loop %d\n", indexElem);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", indexElem, indexElem, sFirst[indexElem] - sSecond[indexElem]);

    return sFirst[indexElem] - sSecond[indexElem];
    }




