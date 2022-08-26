/*!
\file
\brief Исполняемый файл с функциями

Данный файл содержит в себе основные функций, используемые при решении квадратного уравнения
*/


#include <stdio.h>
#include <math.h>
#include <locale.h>
#include "squaresolver.h"
#include <windows.h>


void Clear_Sdin(){
    while (getchar() != '\n') {}
}


void Derive_Solution(){

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
        ASSERT(0 && "Switch defaukt err");
        break;
    }
}





void Test_Square(const char* in_file_name, const char* out_file_name)
{
    double indices[3] = {0, 0, 0};     	/* Коэффициенты уравнения */
	double x1 = 0, x2 = 0;				/* Решения функции Solve_Square */
    double r_x1 = 0, r_x2 = 0;          /* Истинные корни */
    int i = 0;                          /* Номер теста */
    int Real_nRoots = 0;                /* Истинное коливество корней */

    FILE *in_file;                      /* Входной файл с верными данными */
    in_file = fopen(in_file_name, "r");
    FILE *out_file;                     /* Выходной файл с результатами */
    out_file = fopen(out_file_name, "w");

    fprintf(out_file, "Results:\n\n");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    while (fscanf(in_file, "%lf\t\t%lf\t\t%lf\t\t%d", &indices[0], &indices[1], &indices[2], &Real_nRoots) != EOF) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);

        ++i;
        x1 = 0;
        x2 = 0;
        r_x1 = 0;
        r_x2 = 0;
        
        switch (Real_nRoots){
        case 2:
            fscanf(in_file, "\t\t%lf\t\t%lf", &r_x1, &r_x2);
            break;
        case 1:
            fscanf(in_file, "\t\t%lf", &r_x1);
            break;
        default: {}
        }

        int nRoots = Solve_Square(indices, &x1, &x2, 0);
        Print_In_Cons(x1, r_x1, x2, r_x2, indices, i, nRoots, Real_nRoots, out_file);
        printf("\n");
        fprintf(out_file, "\n");
    }
    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);

    fclose(in_file);
}


void Print_In_Cons(double x1, double r_x1, double x2, double r_x2, double indices[], int i, int nRoots, int Real_nRoots, FILE *out_file){
    double a = indices[0];
    double b = indices[1];
    double c = indices[2];

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!(nRoots == Real_nRoots)){
            printf("Test %d failed:\nexpected %d roots\ngot\t  %d roots\nequation ", i, Real_nRoots, nRoots);
            fprintf(out_file, "Test %d failed:\nexpected %d roots\ngot\t %d roots\ncoefficients: (a = %g, b = %g, c = %g)", i, Real_nRoots, nRoots, a, b, c);
            
            nRoots = Solve_Square(indices, &x1, &x2, 1);
            
            printf("\n");
            fprintf(out_file, "\n");
    }
    else if (!Eps_Comp(x1, r_x1) || !Eps_Comp(x2, r_x2)){
        switch (nRoots){
        case 2:
            printf("Test %d failed:\nexpected x1 = %lf; x2 = %lf roots\ngot\t x1 = %lf; x2 = %lf roots\nequation ", i, r_x1, r_x2, x1, x2);
            fprintf(out_file, "Test %d failed:\nexpected x1 = %lf; x2 = %lf\ngot\t x1 = %lf; x2 = %lf\ncoefficients: (a = %g, b = %g, c = %g)", i, r_x1, r_x2, x1, x2, a, b, c);

            nRoots = Solve_Square(indices, &x1, &x2, 1);

            printf("\n");
            fprintf(out_file, "\n");

            break;
        case 1:
            printf("Test %d failed:\nexpected x = %lf root\ngot\t x = %lf root\nequation ", i, r_x1, x1);
            fprintf(out_file, "Test %d failed:\nexpected x = %lf root\ngot\t x = %lf root\ncoefficients: (a = %g, b = %g, c = %g)", i, r_x1, x1, a, b, c);
            
            nRoots = Solve_Square(indices, &x1, &x2, 1);

            printf("\n");
            fprintf(out_file, "\n");

            break;
        default: {}
        }
    }
    else{
        SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
        printf("Test %d passed\n", i);
        fprintf(out_file, "Test %d passed\n", i);
    }
}


int Eps_Comp(double a, double b) {
	if (fabs(a - b) <= 0.00001) {
		return 1;
	}
	return 0;
}


void Print_Square_Problem(double a, double b, double c) {
	if (Eps_Comp(a, 1)) {
		printf("x^2");
	}
	else if (Eps_Comp(a, -1)) {
		printf("-x^2");
	}
	else printf("%gx^2", a);
	if (Eps_Comp(b, 1)) {
		printf(" + x");
	}
	else if (Eps_Comp(b, -1)) {
		printf(" - x");
	}
	else if (b < 0) {
		printf(" - %gx", -b);
	}
	else if (!Eps_Comp(b, 0)) {
		printf(" + %gx", b);
	}
	if (Eps_Comp(c, -1)) {
		printf(" - 1");
	}
	else if (c < 0) {
		printf(" - %g", -c);
	}
	else if (!Eps_Comp(c, 0)) {
		printf(" + %g", c);
	}
	printf(" = 0");
}


int Solve_Square(double indices[], double* x1, double* x2, int to_print) {
    double a = indices[0];
    double b = indices[1];
    double c = indices[2];
	double D = b * b - 4 * a * c;
    double sqd = sqrt(D);

	if (Eps_Comp(a, 0)) {
        if (to_print){
            Print_Linear_Problem(b, c);
        }
		if (Eps_Comp(b, 0)){
			if (Eps_Comp(c, 0)){
				return INF_ROOTS;
			}
			else{
				return 0;
			}
		}
		else {
			*x1 = -c / b;
			return 1;
		}
	}
    if (to_print){
        Print_Square_Problem(a, b, c);
    }
	if (Eps_Comp(D, 0)) {
		*x1 = -b / (2 * a);
		return 1;
	}
	else if (D > 0) {
		*x1 = (-b - sqd) / (2 * a);
		*x2 = (-b + sqd) / (2 * a);
		return 2;
	}
	else if (D < 0) {
		return 0;
	}
    return 0;
}


void Print_Linear_Problem(double b, double c) {
	if (Eps_Comp(b, -1)) {
		printf("-x");
	}
	else if (Eps_Comp(b, 1)) {
		printf("x");
	}
	else {
		printf("%gx", b);
	}
	if (Eps_Comp(c, -1)) {
		printf(" - 1");
	}
	else if (c < 0) {
		printf(" - %g", -c);
	}
	else if (!Eps_Comp(c, 0)) {
		printf(" + %g", c);
	}
	printf(" = 0");
}


void Reduce_To_0(double* x) {
	if (Eps_Comp(*x, 0)) {
		*x = 0;
	}
}