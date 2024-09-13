#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>

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


    printf ("%lld\n", fileInf.st_size);
    printf ("count of char = %lld\n", fileInf.st_size / sizeof (char));

    void* buffer = calloc (fileInf.st_size + 1, sizeof(char));

    FILE* file = fopen ("Onegin.txt", "rb");

    if (file == NULL)
        {
        printf ("File opening error\n");

        return 0;
        }

    if (feof (file))
        clearerr (file);

    size_t razmerFayla = fread (buffer, fileInf.st_size, sizeof (char), file);

    printf ("%s\n", buffer);

    fclose (file);

    printf ("%zu\n", razmerFayla);
    }
