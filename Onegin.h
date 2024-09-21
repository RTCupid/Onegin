#include <sys/types.h>
#include <sys/stat.h>

const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

struct PTR  {
            char* PtrStart;
            int lenString;
            };

typedef int (*Compare_func_t)(const void*, const void*);

#define DBG if (0)

int MakePointers (char** Onegin, size_t* sizeOfFile, int* nPointer, PTR** Pointers, PTR* ParamString, const char* namefile);

bool InputOnegin (char** Onegin, size_t* sizeofFile, const char* nameFile);

void SizeFile (struct stat* fileInf, const char* nameFile);

void CounterSymbol (int* nRow, char* Onegin, size_t sizeOfFile, char symbol);

void InitialisatorPointers (size_t sizeOfFile, PTR* Pointers, char* Onegin, struct PTR* ParamString, int* nPointer);

void Sorting (void* Pointers, int nPointer, size_t sizeElem, Compare_func_t CmpFnc);

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
int Comparator (const void* voidParamFirst, const void* voidParamSecond);

int EOLComparator (const void* paramFirst, const void* paramSecond);

void SkipMarks (const PTR paramString, int* i, int deltai);

void SwappingPTR (PTR* paramFirst, PTR* paramSecond);

void Print (const PTR paramString);

void OutputText (PTR* Pointers, int Pointer, FILE* file);

void WriteTheOriginalOfPushkinGreatestPoemEugeneOnegin (char* Onegin, FILE* file);






