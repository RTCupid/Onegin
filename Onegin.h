const int MAX_ROWS = 29;
const int MAX_ELEM = 100;

// I have a commit!

_Bool Input (char text[MAX_ROWS][MAX_ELEM]);

void OutputText (char text[MAX_ROWS][MAX_ELEM]);

void Sorting (char** Pointers, int nRow);

_Bool Swapping (char* sFirst, char* sSecond);

_Bool SkipMarks (char* sFirst, char* sSecond, int* iIndexElem, int* jIndexElem);

int EOLComparator (char* sFirst, char* sSecond);

void EOLSorting (char text[MAX_ROWS][MAX_ELEM]);

_Bool EOLSkipMarks (char* sFirst, char* sSecond, int* iIndexElem, int* jIndexElem);
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

int Comparator (char* startFirst, char* endFirst, char* startSecond, char* endSecond);

void InputOnegin (char** Onegin, size_t* sizeofFile);

void OutputText (char* Pointers[], int nPointer);

void OutputRow (char* Pointers[], int ptr, size_t sizeOfRow);

void CounterRow (int* nRow, char* Onegin, size_t sizeOfFile);

void InitialisatorPointers (size_t sizeOfFile, char** Pointers, char* Onegin);
