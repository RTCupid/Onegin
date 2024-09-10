#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "Onegin.h"

// функция сортировки строчек по алфавиту......................................

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
                }                                                    // теперь, если меняли строки, строка, которая позже по алфавиту,
                                                                     // находится по адресу row + 1, значит в следующей итерации цикла
            }                                                        // эта строка будет сравниваться со следующей строкой, значит мне
        }                                                            // нужен ещё один большой цикл, который позволит каждой строке га-
    }                                                                // рантированно дойти до своего места в упорядоченном ряду строк

// это компаратор..............................................................

int Comparator ( char* sFirst, char* sSecond)
    {
    int indexElem = 0;
    printf ("\nindexElem before the loop = %d\n\n", indexElem);

    printf ("Compare:\n<%s>\nvs\n<%s>\n", sFirst, sSecond);
    int iIndexElem = 0;
    int jIndexElem = 0;

    if (SkipMarks (sFirst, sSecond, &iIndexElem, &jIndexElem))
        {
        printf ("Succesfull skipping marks!\n");
        printf ("After skipping:\niIndexElem = %d;"
                               "\njIndexElem = %d;\n",
                iIndexElem, jIndexElem);
        }

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
