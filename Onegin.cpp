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

    RunComparator (text);

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
        printf ("string %02d => <%s>\n", row, text[row]);
        }
    }

void RunComparator (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int i = 0; i < MAX_ROWS - 1; i++)
        {
        printf ("\nsFirst  = text[%d]\n"
                "sSecond = text[%d]",
                i, i+1);

        int result = Comparator (text[i], text[i+1]);

        printf ("result = %d\n", result);
        }
    }

// это компаратор..............................................................

int Comparator ( char* sFirst, char* sSecond)
    {
    int j = 0;
    printf ("\nj before the cycle = %d\n", j);

    while (1)
        {
        printf ("'%c' vs '%c' -- %03d vs %03d\n", sFirst[j], sSecond[j], sFirst[j], sSecond[j]);
        if (sFirst[j] != sSecond[j] || (sFirst[j] == sSecond[j] && sSecond[j] == '\0'))
            break;
        j++;
        }                                                    // cycle => loop

    printf ("j after the cycle %d\n", j);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", j, j, sFirst[j] - sSecond[j]);

    return sFirst[j] - sSecond[j];
    }




