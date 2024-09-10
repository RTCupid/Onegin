#include "TXLib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "Onegin.h"

// функция считывания инфы из файла и загрузки её в двумерный массив...........

_Bool Input (char text[MAX_ROWS][MAX_ELEM])
    {
    FILE* file = fopen("Onegin.txt", "r");

    if (file == NULL)
        {
        printf("File opening error");

        return 0;                                      // main () return -1
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
