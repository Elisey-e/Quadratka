#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <assert.h>
#include "squaresolver.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	double indices[3] = { 0, 0, 0 };	/* Массив коэффициентов уравнения */
	double x1 = 0, x2 = 0;				/* Корни */
	printf("Введите коэффициенты квадратного уравнения вида ax^2 + bx + c = 0 по порядку\n");
	while (scanf("%lf %lf %lf", &indices[0], &indices[1], &indices[2]) != 3) {
		printf("Ввод некорректен, произведите ввод заново\n");
		while (getchar() != '\n') {}
	}
	printf("Решение уравнения ");
	int count = Solve_Square(indices[0], indices[1], indices[2], &x1, &x2);
	Reduce_To_0(&x1);
	Reduce_To_0(&x2);
	switch (count) {
	case 2: printf("\nx1 = %g\nx2 = % g\n", x1, x2);
		break;
	case 1: printf("\nx = %g\n", x1);
		break;
	case 0: printf("\nПустое множество\n.");
		break;
	case INF_ROOTS: printf("\nБесконечное множество\n.");
	}
}