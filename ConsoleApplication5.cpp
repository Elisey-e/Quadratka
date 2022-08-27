#include "squaresolver.h"


/*!
\file
\brief Главный файл проекта с функцией main
\authors Zhdanov_EA
*/


#define TEST


/*!
	Функция управляет запуском функций проверки и решения уравнения.
	\param[in] argc, argv - количество и названия файлов для тестирования квадратки, по умолчанию tests.txt и results.txt
*/
int main(int argc, const char* argv[])
{
#ifdef TEST
	const char in_file_name[]  = "tests.txt";
	const char out_file_name[] = "results.txt";

	switch (argc) {
	case 2:
		Test_Square(argv[1], out_file_name);
		break;
	case 3:
		Test_Square(argv[1], argv[2]);
		break;
	default:
		Test_Square(in_file_name, out_file_name);
	}
#else
	
	Derive_Solution();
#endif
}