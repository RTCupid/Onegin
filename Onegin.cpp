#include <stdio.h>

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

    char text[28][100] = {};

    Input (text);                          // теперь у меня есть массив Onegina

    char* sFirst  = NULL;
    char* sSecond = NULL;

    for (int i = 0; i < 27; i++)
        {
        sFirst  = text[i];
        sSecond = text[i + 1];

        int result = Comparator (sFirst, sSecond);

        printf ("result = %d\n", result);
        }

    return 0;
    }

// инициализирует массив.......................................................

void Input (char text[28][100])
    {
    text = {"“My uncle has most honest principles:",
            "when he was taken gravely ill,",
            "he forced one to respect him",
            "and nothing better could invent.",
            "To others his example is a lesson;",
            "but, good God, what a bore to sit",
            "by a sick person day and night, not stirring",
            "a step away!",
            "What base perfidiousness",
            "to entertain one half-alive,",
            "adjust for him his pillows,",
            "sadly serve him his medicine,",
            "sigh — and think inwardly",
            "when will the devil take you?”",

            "Thus a young scapegrace thought",
            "as with post horses in the dust he flew,",
            "by the most lofty will of Zeus",
            "the heir of all his kin.",
            "Friends of Lyudmila and Ruslan!",
            "The hero of my novel,",
            "without preambles, forthwith,",
            "I'd like to have you meet:",
            "Onegin, a good pal of mine,",
            "was born upon the Neva's banks,",
            "where maybe you were born,",
            "or used to shine, my reader!",
            "There formerly I too promenaded —",
            "but harmful is the North to me."};
    }

// это компаратор..............................................................

int Comparator ( char* sFirst, char* sSecond)
    {
    int j = -1;
    printf ("j before the cycle = %d\n", j);
    do
        {
        j++;
        printf ("j in the %d'th iteration of the cycle = %d\n", j, j);
        }
    while (sFirst[j] == sSecond[j]);

    printf ("j after the cycle %d\n", j);

    printf ("sFirst[%d] - sSecond[%d] = %d\n\n", j, j, sFirst[j] - sSecond[j]);

    return sFirst[j] - sSecond[j];
    }




