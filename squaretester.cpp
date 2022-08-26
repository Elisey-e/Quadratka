/*!
\file
\brief Исполняемый файл с функциями
Данный файл содержит в себе основные функций, используемые при решении квадратного уравнения
*/


#include <stdio.h>
#include "squaresolver.h"
#include <windows.h>


void Test_Square(const char* in_file_name, const char* out_file_name)
{
    double indices[3] = {0, 0, 0};						/* Коэффициенты уравнения */
	double   x1 = 0,   x2 = 0;							/* Решения функции Solve_Square */
    double r_x1 = 0, r_x2 = 0;							/* Истинные корни */
    int i = 0;											/* Номер теста */
    int Real_nRoots = 0;								/* Истинное коливество корней */

    FILE *in_file  = fopen(in_file_name,  "r");			/* Выходной файл с результатами */
    FILE *out_file = fopen(out_file_name, "w");			/* Выходной файл с результатами */

	if (!in_file) {
		printf( "Входной файл \"%s\" не обнаружен, будет использован файл \"tests.txt\" по умолчанию\n",    in_file_name);
		in_file = fopen("tests.txt", "r");
	}

	if (!out_file) {
		printf("Выходной файл \"%s\" не обнаружен, будет использован файл \"results.txt\" по умолчанию\n", out_file_name);
		out_file = fopen("results.txt", "w");
	}

    fprintf(out_file, "Results:\n\n");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    while (fscanf(in_file, "%lf %lf %lf %d", &indices[0], &indices[1], &indices[2], &Real_nRoots) != EOF) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);

        ++i;
        x1 = x2 = r_x1 = r_x2 = 0;
        
        switch (Real_nRoots) {
        case 2:
            fscanf(in_file, "%lf %lf", &r_x1, &r_x2);
            break;
        case 1:
            fscanf(in_file, "%lf",     &r_x1);
            break;
        default: {}
        }

        int nRoots = Solve_Square(indices, &x1, &x2, 0);
        Print_In_Cons(x1, r_x1, x2, r_x2, indices, i, nRoots, Real_nRoots, out_file);
        printf(           "\n");
        fprintf(out_file, "\n");
    }
    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);

    fclose(in_file);
	// fcl
}

void Print_In_Cons(double x1, double r_x1, double x2, double r_x2, double indices[], int i, int nRoots, int Real_nRoots, FILE *out_file)
{
    double a = indices[0];
    double b = indices[1];
    double c = indices[2];

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!(nRoots == Real_nRoots)) {
            printf(           "Test %d failed:\nexpected%5d roots\ngot%10d roots\nequation ", i, Real_nRoots, nRoots);
            fprintf(out_file, "Test %d failed:\nexpected%5d roots\ngot%10d roots\ncoefficients: (a = %g, b = %g, c = %g)", i, Real_nRoots, nRoots, a, b, c);
            
            nRoots = Solve_Square(indices, &x1, &x2, 1);
            
            printf("\n");
            fprintf(out_file, "\n");
    }
    else if (!Eps_Comp(x1, r_x1) || !Eps_Comp(x2, r_x2)) {
        switch (nRoots){
        case 2:
            printf(           "Test %d failed:\nexpected x1 = %.3lf; x2 = %.3lf roots\ngot\t x1 = %.3lf; x2 = %.3lf roots\nequation ", i, r_x1, r_x2, x1, x2);
            fprintf(out_file, "Test %d failed:\nexpected x1 = %.3lf; x2 = %.3lf\ngot\t x1 = %.3lf; x2 = %.3lf\ncoefficients: (a = %g, b = %g, c = %g)", i, r_x1, r_x2, x1, x2, a, b, c);

            nRoots = Solve_Square(indices, &x1, &x2, 1);

            printf("\n");
            fprintf(out_file, "\n");

            break;
        case 1:
            printf(           "Test %d failed:\nexpected x = %.3lf root\ngot\t x = %.3lf root\nequation ", i, r_x1, x1);
            fprintf(out_file, "Test %d failed:\nexpected x = %.3lf root\ngot\t x = %.3lf root\ncoefficients: (a = %g, b = %g, c = %g)", i, r_x1, x1, a, b, c);
            
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