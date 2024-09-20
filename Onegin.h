#include <sys/types.h>
#include <sys/stat.h>

const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

struct PTR  {
            char* PtrStart;
            int lenString;
            };

void InputOnegin (char** Onegin, size_t* sizeofFile);

void SizeFile (struct stat* fileInf);

void CounterRow (int* nRow, char* Onegin, size_t sizeOfFile);

void InitialisatorPointers (size_t sizeOfFile, PTR* Pointers, char* Onegin, struct PTR* ParamString, int* nPointer);

void Sorting (PTR* Pointers, int nPointer);

void EOLSorting (PTR* Pointers, int nPointer);

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






