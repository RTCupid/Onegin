#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "Onegin.h"

int main ()
    {
    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n\n");

    InputMP ();

    /*char text[MAX_ROWS][MAX_ELEM] = {};                            // здесь я создавал и заполнял двумерный массив

    _Bool inputCorrect = Input (text);
    if (inputCorrect == 0)
        return -1;*/

    //OutputText (text);

    Sorting (text);                                                  // toupper dobavit + znaki propuskat (est)

    OutputText (text);

    EOLSorting (text);

    OutputText (text);

    return 0;
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








