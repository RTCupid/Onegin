#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

_Bool InputMP ();

int main ()
    {

    InputMP ();

    return 0;
    }

// учусь юзать fread, а точнее создаю массив указателей

_Bool InputMP ()
    {
    struct stat fileInf;

    stat ("Onegin.txt", &fileInf);

    printf ("\n%lld\n", fileInf.st_size);
    printf ("count of char = %lld\n", fileInf.st_size / sizeof (char));

    void* Onegin = calloc (fileInf.st_size + 1, sizeof(char));

    FILE* file = fopen ("Onegin.txt", "rt");

    if (file == NULL)
        {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror("Onegin.txt\n");
        return 0;
        }

    size_t sizeOfFile = fread (Onegin, sizeof (char), fileInf.st_size, file);

    if (sizeOfFile == 0)
        {
        printf ("errno = <%d>\n", errno);
        perror ("Onegin.txt");
        }

    //for(int i=0; i<sys_nerr; i++)
    //    printf("sys_errlist[%d] = \"%s\"\n", i, sys_errlist[i]);

    printf ("\n%s\n", Onegin);

    fclose (file);

    printf ("sizeOfFile = <%zu>\n\n", sizeOfFile);

    int nRow = 0;

    for (int i = 0; i < sizeOfFile; i++)
        {
        if (*((char*)Onegin + i * sizeof (char)) == '\n')
            {
            printf ("Onegin[%d] = <'\\n'>\n", i);
            nRow = nRow + 1;
            }
        else
            printf ("Onegin[%d] = <%c>\n", i, *((char*)Onegin + i * sizeof (char)));
        }

    printf ("nRow = <%d>", nRow);






    }
