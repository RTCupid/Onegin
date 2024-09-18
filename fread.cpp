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

#include "Onegin.h"

// учусь юзать fread, а точнее создаю массив указателей

bool InputMP ()
    {
    char* Onegin = NULL;
    size_t sizeOfFile = 0;

    InputOnegin (Onegin, &sizeOfFile);                              // читаю из файла в буффер текст Онегина и определяю размер буффера

    int nRow = 0;

    for (unsigned int i = 0; i < sizeOfFile; i++)                    // посимвольно зачем-то вывожу начальный текст Онегина
        {                                                            // точно, я не просто вывожу, а параллельно считаю количество
        if (Onegin[i] == '\n')                                       // строк, равное кличеству '\n'
            {
            printf ("Onegin[%d] = <'\\n'>\n", i);
            nRow = nRow + 1;
            }
        else
            printf ("Onegin[%d] = <%c>\n", i, Onegin[i]);
        }

    printf ("nRow = <%d>\n", nRow);                                  // I have this commit!

    char** Pointers = (char**)calloc (nRow, sizeof (char*));         // каллокаю массив указателей

    int nPointer = 0;

    printf ("\nInitialization of Pointers:\n\n");

    for (unsigned int i = 0; i < sizeOfFile; i++)                    // прохожу весь массив с текстом Онегина и заношу в массив указателей
        {                                                            // все элементы, которые следуют за '\n'
        if (Onegin[i] == '\n')
            {
            Pointers[nPointer] = &Onegin[i+1];
            printf ("Pointer[%d] = <%p>\n", nPointer, &Onegin[i+1]); // вывожу какими инициализируются элементы массива указателей
            nPointer = nPointer + 1;
            }
        }

    printf ("\nPointers:\n\n");

    char* Pointer = NULL;

    for (int n = 0; n < nPointer; n++)                               // вывожу все элементы массива указателей, сравниваю правильно ли
        {                                                            // вывожу то, что было инициализировано (правильно)
        printf ("n = <%d> | ", n);
        assert (n < nPointer);
        Pointer = Pointers[n];
        printf ("Pointers[%d]  = <%p>\n", n, Pointer);
        }

    OutputText (Pointers, nPointer);                                 // вывожу текст используя массив указателей


    return 1;
    }

void InputOnegin (char* Onegin, size_t* sizeOfFile)
    {
    struct stat fileInf = {};

    int err = stat ("Onegin.txt", &fileInf);
    if (err != 0)
        printf("Stat err %d\n", err);

    printf ("\n%ld\n", fileInf.st_size);
    printf ("count of char = %ld\n", fileInf.st_size / sizeof (char));

    Onegin = (char*)calloc (fileInf.st_size + 1, sizeof(char));     // каллочу буффер, чтобы в него считать текст

    FILE* file = fopen ("Onegin.txt", "rt");

    if (file == NULL)
        {
        printf ("File opening error\n");
        printf("errno = <%d>\n", errno);
        perror("Onegin.txt\n");
        }

    *sizeOfFile = fread (Onegin, sizeof (char), fileInf.st_size, file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (*sizeOfFile == 0)
        {
        printf ("errno = <%d>\n", errno);
        perror ("Onegin.txt");
        }

    //for(int i=0; i<sys_nerr; i++)
    //    printf("sys_errlist[%d] = \"%s\"\n", i, sys_errlist[i]);

    printf ("\n%s\n", Onegin);                                       // вывожу начальный текст Онегина

    fclose (file);                                                   // закрываю файл

    printf ("sizeOfFile = <%zu>\n\n", *sizeOfFile);
    }

 void OutputText (char* Pointers[], int nPointer)
    {
    int ptr = 0;

    size_t sizeOfRow = 0;

    for (; ptr < nPointer - 1; ptr++)                                    // ptr < общего количества строк
        {
        printf ("ptr = <%d>\n", ptr);
        assert (ptr < nPointer - 1);
        sizeOfRow = Pointers[ptr+1] - Pointers[ptr];
        OutputRow (Pointers, ptr, sizeOfRow);
        }
    }

void OutputRow (char* Pointers[], int ptr, size_t sizeOfRow)
    {
    for (unsigned int i = 0; i < sizeOfRow; i++)
        {
        assert (i < sizeOfRow);
        printf ("%c", *(Pointers[ptr] + i));                            // uvelichivat znachenie, idti vdol stroki
        }
    printf ("\n");
    }
