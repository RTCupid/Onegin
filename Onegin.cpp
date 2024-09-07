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
/// @brief   Comparator - �������, ������� ���������� ��� ������
///                       � ������� ������� ����� ������� �� �������
///                       ���������� ������. �� ���� ���������� �����
///                       �� ����� ������ ������ ������
/// @param   sFirst     - ������ �� ������������ �����
/// @param   sSecond    - ������ �� ������������ �����
///
/// @return  ������� ����� ������� �� ������� ��������� ����� ��������
///          ������� ������������, ���� ������ ������ ������ ����,
///          � ������������, ���� ����
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

    Sorting (text);

    RunComparator (text);

    return 0;
    }

// ������� ���������� ���� �� ����� � �������� � � ��������� ������...........

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
        if (fgets (text[row], MAX_ELEM, file) == NULL) // ��������� �� ����� � ��������� ������
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

// ������� ����� �������.......................................................

void OutputText (char text[MAX_ROWS][MAX_ELEM])
    {
    int row = 0;

    for (; row < MAX_ROWS; row++)
        {
        assert (row < MAX_ROWS);
        printf ("string %02d => <%s>\n", row, text[row]);
        }
    }

// ������� ���������� ������� �� ��������......................................

void Sorting (char text[MAX_ROWS][MAX_ELEM])
    {
    for (int i = 0;


// ��������� ��������� ���� �������� �������...................................

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

// ��� ����������..............................................................

int Comparator ( char* sFirst, char* sSecond)
    {
    int indexElem = 0;
    printf ("\nindexElem before the loop = %d\n", j);

    while (1)
        {
        printf ("'%c' vs '%c' -- %03d vs %03d\n", sFirst[indexElem], sSecond[indexElem], sFirst[indexElem], sSecond[indexElem]);
        if (sFirst[indexElem] != sSecond[indexElem] || (sFirst[indexElem] == sSecond[indexElem] && sSecond[indexElem] == '\0'))
            break;
        indexElem++;
        }                                                    // cycle => loop (est)

    printf ("indexElem after the loop %d\n", indexElem);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", indexElem, indexElem, sFirst[indexElem] - sSecond[indexElem]);

    return sFirst[indexelem] - sSecond[indexElem];
    }




