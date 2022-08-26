#ifndef SQUARESOLVER_H
#define SQUARESOLVER_H
/*!
\file
\brief Заголовочный файл с описанием функций

Данный файл содержит в себе определения основных 
функций, используемых при решении квадратного уравнения
*/


#define INF_ROOTS -1
#define ASSERT(cond) \
	if (!(cond))\
		printf("\tError in line %d\n\tof the file %s\n\tcondinion (%s) is false\n", __LINE__, __FILE__, #cond);


/*!
	\brief Функция, которая проверяет присутствие 2-х чисел в одной эпсилон-окрестности
	\param[in] a, b Два числа, которые мы сравниваем
	\return 1 если оба числа принадлежат одной окрестности или 0 если нет
*/
int  Eps_Comp(double a, double b);


/*!
	\brief Функция, выводящая интерфейс для решения квадратного уравнения
*/
void Derive_Solution();


/*!
	\brief Функция, которая распечатывает квадратное уравнение с подставленными числовыми коэффициентами
	\param[in] a, b, c Три числа - коэффициента уравнения
*/
void Print_Square_Problem(double a, double b, double c);


/*!
	\brief Функция, которая решает квадратное уравнение, линейное в случае равенства коэффициента при x^2 нулю
	\param[in] a, b, c Три числа - коэффициента уравнения
	\param[in] x1, x2 Две ссылки на корни уравнения
	\param[in] to_print Печатать ли исходное уравнение
	\return Количество решений уравнения, INF_ROOTS если корней бесконечно много
*/
int  Solve_Square(double indices[], double* x1, double* x2, int to_print);


/*!
	\brief Функция, которая распечатывает линейное уравнение с подставленными числовыми коэффициентами
	\param[in] b, c Два числа - коэффициента уравнения
*/
void Print_Linear_Problem(double b, double c);


/*!
	\brief Функция, изменяющая число на 0 в случае его равенства -0
	\param[in] x Ссылка на изменяемое число
*/
void Reduce_To_0(double* x);


/*!
	\brief Функция, тестирующая функцию Solve_Square
*/
void Test_Square(const char* in_file_name_ptr, const char* out_file_name_ptr);


/*!
	\brief Функция, производящая вывод в поток и файл информацию
	\param[in] x1, x2 Проверяемые корни уравнения
	\param[in] r_x1, r_x2 Истинные корни уравнения
	\param[in] indices[] Массив индексов уравнения
	\param[in] i Номер теста
	\param[in] nRoots, Real_nRoots Проверяемое и истинное число корней уравнения
	\param[in] *out_file Ссылка на файл с результатом
*/
void Print_In_Cons(double x1, double r_x1, double x2, double r_x2, double indices[], int i, int nRoots, int Real_nRoots, FILE *out_file);


/*!
	\brief Функция, очищающая входной поток
*/
void Clear_Sdin();


/*!
	\brief Функция, производящая вывод в поток и файл информацию
	\param[in] *x1 Ссылка на корень уравнения
	\param[in] indices Массив индексов уравнения
	\param[in] to_print Печатать ли уравнение
*/
int Solve_Linear(double indices[], double* x1, int to_print);


#endif