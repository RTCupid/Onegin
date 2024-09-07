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

int main ()
    {
    printf ("# The program for sorting strings\n");
    printf ("# (c) RTCupid, 2024\n");


    char text[28][100] = {};

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

    while (row < 28)
        {
        if (fgets (text[row], 100, file) == NULL) // считывает из файла в двумерный массив
            break;
        char* newLine = strchr (text[row], '\n');
        if (newLine != NULL)
            {
            *newLine = '#';
            }

        row++;
        }
    fclose (file);

    row = 0;

    for (; row < 28; row++)
        {
        printf ("string %d => <%s>\n", row, text[row]);
        }



    for (int i = 0; i < 27; i++)
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
    int j = -1;
    printf ("\nj before the cycle = %d\n", j);
    do
        {
        j++;
        }
    while (sFirst[j] == sSecond[j]);

    printf ("j after the cycle %d\n", j);

    printf ("sFirst[%d] - sSecond[%d] = %d\n", j, j, sFirst[j] - sSecond[j]);

    return sFirst[j] - sSecond[j];
    }




