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

    printf ("nRow = <%d>\n", nRow);                                  // I have this commit!

    void* Pointers = calloc (nRow, sizeof (char*));                  // (char**)calloc..... чтобы сразу привести возвр.знач.
                                                                     // calloc к типу (char**)
    int nPointer = 0;

    printf ("\nInitialization of Pointers:\n\n");

    for (int i = 0; i < sizeOfFile; i++)
        {
        if (*((char*)Onegin + i * sizeof (char)) == '\n')
            {
            *((int*)Pointers + i + 1) = (size_t)Onegin + i * sizeof (char);
            printf ("Pointer[%d] = <%p>\n", nPointer, (size_t)Onegin + i * sizeof (char));
            nPointer = nPointer + 1;
            }
        }

    printf ("\nPointers:\n\n");

    char* Pointer = NULL;

    for (int n = 0; n < nPointer; n++)
        {
        Pointer = *(char**)((int*)Pointers + n * sizeof (int));
        printf ("Pointers[%d] = <%p>\n", n, Pointer);
        }






    return 1;
    }
