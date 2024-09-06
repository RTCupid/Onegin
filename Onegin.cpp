#include <stdio.h>

void Input ();

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
    //Input ();                          // ������ � ���� ���� ������

    char sFirst[]    = {"hbcde"};
    char sSecond[]   = {"abcqg"};



    int result = Comparator (sFirst, sSecond);

    printf ("result = %d\n", result);

    return 0;
    }

// �������������� ������.......................................................

/*void input ()
    {
    char text [28][100] = {"�My uncle has most honest principles:",
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
                           "sigh � and think inwardly",
                           "when will the devil take you?�",

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
                           "There formerly I too promenaded �",
                           "but harmful is the North to me."};
    }
*/

// ��� ����������..............................................................

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




