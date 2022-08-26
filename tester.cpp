

#include <stdio.h>
#include <locale.h>
#include "squaresolver.h"


int main()
{
    setlocale(LC_ALL, "Rus");

	double x1 = 0, x2 = 0;
	int nRoots = Solve_Square(1, 0, -4, &x1, &x2);
	ASSERT(nRoots == 2 && Eps_Comp(x1, -2) && Eps_Comp(x2, 2));
}