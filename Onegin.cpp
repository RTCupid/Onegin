#include "TXLib.h"
#include <stdio.h>
#include <string.h>


void Input (char text[28][100]);

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

const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

int main ()
    {
    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n");


    char text[MAX_ROWS][MAX_ELEM] = {};

    FILE* file = fopen("Onegin.txt", "r");

    /*char* sFirst  = NULL;
    char* sSecond = NULL;
    */

    if (file == NULL)
        {
        printf("File opening error");

        return -1;                                // main () return -1
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

    row = 0;

    for (; row < MAX_ROWS; row++)
        {
        printf ("string %02d => <%s>\n", row, text[row]);
        }



    for (int i = 0; i < MAX_ROWS - 1; i++)
        {

        printf ("\nsFirst  = text[%d]\n"
                "sSecond = text[%d]",
                i, i+1);

        int result = Comparator (text[i], text[i+1]);

        printf ("result = %d\n", result);
        }

    return 0;
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




