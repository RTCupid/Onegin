#include <sys/types.h>
#include <sys/stat.h>

const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

struct PTR  {
            char* PtrStart;
            int lenString;
            };

typedef int (*Compare_func_t)(PTR paramFirst, PTR paramSecond);

void MakePointers (char** Onegin, size_t* sizeOfFile, int* nPointer, PTR** Pointers, PTR* ParamString, char* namefile);

void InputOnegin (char** Onegin, size_t* sizeofFile, char* nameFile);

void SizeFile (struct stat* fileInf, char* nameFile);

void CounterRow (int* nRow, char* Onegin, size_t sizeOfFile);

void InitialisatorPointers (size_t sizeOfFile, PTR* Pointers, char* Onegin, struct PTR* ParamString, int* nPointer);

void Sorting (PTR* Pointers, int nPointer, Compare_func_t CmpFnc);

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
int Comparator (PTR paramFirst, PTR paramSecond);

int EOLComparator (PTR paramFirst, PTR paramSecond);

void SkipMarks (PTR paramString, int* i);

void EOLSkipMarks (PTR paramString, int* i);

void Swapping (PTR* paramFirst, PTR* paramSecond);

void Print (PTR paramString);

void OutputText (PTR* Pointers, int Pointer, FILE* file);






