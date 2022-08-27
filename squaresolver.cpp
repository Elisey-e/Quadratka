/*!
\file
\brief Исполняемый файл с функциями
Данный файл содержит в себе основные функций, используемые при решении квадратного уравнения
*/

#include "squaresolver.h"


const double Epsilon = 1e-5;


void Clear_Sdin()
{
    while (getchar() != '\n') {}
}

void Derive_Solution()
{

	double indices[3] = { 0, 0, 0 };	/* Массив коэффициентов уравнения */
	double x1 = 0, x2 = 0;				/* Корни */

	printf("Введите коэффициенты квадратного уравнения вида ax^2 + bx + c = 0 по порядку\n");
	while (scanf("%lf %lf %lf", &indices[0], &indices[1], &indices[2]) != 3) {
		printf("Ввод некорректен, произведите ввод заново\n");
		Clear_Sdin();
	}

	printf("Решение уравнения ");
	int count = Solve_Square(indices, &x1, &x2, 1);

	Reduce_To_0(&x1);
	Reduce_To_0(&x2);

	switch (count) {
	case 2:
		printf("\nx1 = %g\nx2 = % g\n", x1, x2);
		break;
	case 1:
		printf("\nx = %g\n", x1);
		break;
	case 0:
		printf("\nПустое множество\n.");
		break;
	case INF_ROOTS: 
		printf("\nБесконечное множество\n.");
        break;
    default:
        ASSERT(0 && "Switch default error");
        break;
    }
}

int Eps_Comp(double a, double b)
{
	assert(!isnan(a));
	assert(!isnan(b));
	return (fabs(a - b) <= Epsilon);
}

void Print_Square_Problem(double a, double b, double c)
{
	assert(!isnan(a));
	assert(!isnan(b));
	assert(!isnan(c));
	if (      Eps_Comp(a, 1)) {
		printf("x^2");
	}
	else if ( Eps_Comp(a, -1)) {
		printf("-x^2");
	}
	else printf("%.4gx^2", a);


	if (      Eps_Comp(b, 1)) {
		printf(" + x");
	}
	else if ( Eps_Comp(b, -1)) {
		printf(" - x");
	}
	else if (b < 0) {
		printf(" - %.4gx", -b);
	}
	else if (!Eps_Comp(b, 0)) {
		printf(" + %.4gx", b);
	}


	if (	  Eps_Comp(c, -1)) {
		printf(" - 1");
	}
	else if (c < 0) {
		printf(" - %.4g", -c);
	}
	else if (!Eps_Comp(c, 0)) {
		printf(" + %.4g", c);
	}


	printf(" = 0");
}

int Solve_Square(double indices[], double* x1, double* x2, int to_print)
{
	assert(!isnan(to_print));

	assert(		x1 != NULL);
	assert(		x2 != NULL);
	assert(indices != NULL);
    double a = indices[0];
    double b = indices[1];
    double c = indices[2];

	if (Eps_Comp(a, 0)) {
        if (to_print) {
            Print_Linear_Problem(b, c);
        }
		if (Eps_Comp(b, 0)) {
			if (Eps_Comp(c, 0)) {
				return INF_ROOTS;
			}
			else {
				return 0;
			}
		}
		else {
			*x1 = -c / b;
			return 1;
		}
	}
    if (to_print) {
        Print_Square_Problem(a, b, c);
    }
	double D = b * b - 4 * a * c;
	if (Eps_Comp(D, 0)) {
		*x1 = -b / (2 * a);
		return 1;
	}
	else if (D > 0) {
		double sqrtd = sqrt(D);
		*x1 = (-b - sqrtd) / (2 * a);
		*x2 = (-b + sqrtd) / (2 * a);
		return 2;
	}
	else if (D < 0) {
		return 0;
	}
    return 0;
}

void Print_Linear_Problem(double b, double c)
{
	assert(!isnan(b));
	assert(!isnan(c));
	if (Eps_Comp(b, -1)) {
		printf("-x");
	}
	else if (Eps_Comp(b, 1)) {
		printf("x");
	}
	else {
		printf("%.4gx", b);
	}


	if (Eps_Comp(c, -1)) {
		printf(" - 1");
	}
	else if (c < 0) {
		printf(" - %.4g", -c);
	}
	else if (!Eps_Comp(c, 0)) {
		printf(" + %.4g", c);
	}


	printf(" = 0");
}

void Reduce_To_0(double* x)
{
	assert(x != NULL);
	if (Eps_Comp(*x, 0)) {
		*x = 0;
	}
}

int Solve_Linear(double indices[], double* x1, int to_print)
{
	assert(x1 != NULL);
	assert(!isnan(to_print));
	assert(indices != NULL);
    double b = indices[0];
    double c = indices[1];
    if (to_print) {
        Print_Linear_Problem(b, c);
    }
	if (Eps_Comp(b, 0)) {
		if (Eps_Comp(c, 0)) {
			return INF_ROOTS;
		}
		else {
			return 0;
		}
	}
	else {
		*x1 = -c / b;
		return 1;
	}
	return 0;
}