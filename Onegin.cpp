#include "Onegin.h"

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

// ������� ���������� ���� �� ����� � �������� � � ��������� ������...........

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
    for (int nIterations = 0; nIterations < MAX_ROWS; nIterations++)
        {
        assert (nIterations < MAX_ROWS);
        for (int row = 0; row < MAX_ROWS-1; row++)
            {
            printf ("row = <%d>\n", row);
            assert (row < MAX_ROWS-1);

            int result = Comparator (text[row], text[row+1]);
            if (result > 0)                                          // ����� ������ ����� ����� �����
                {
                if (Swapping (text[row], text[row + 1]))
                    printf ("Successful exchange!\n");
                }                                                    // ������, ���� ������ ������, ������, ������� ����� �� ��������,
                                                                     // ��������� �� ������ row + 1, ������ � ��������� �������� �����
            }                                                        // ��� ������ ����� ������������ �� ��������� �������, ������ ���
        }                                                            // ����� ��� ���� ������� ����, ������� �������� ������ ������ ��-
    }                                                                // ������������ ����� �� ������ ����� � ������������� ���� �����

// ��� ����������..............................................................

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

//  ������� �������� ������, ������� �� �������� ������� ��� ������� � ������ ������

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

