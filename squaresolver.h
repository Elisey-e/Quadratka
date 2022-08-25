#define INF_ROOTS -1
#define ASSERT(cond) \
	if (!(cond))\
		printf("\tError in line %d\n\tof the file %s\n\tcondinion (%s) is false\n", __LINE__, __FILE__, #cond);


int  Eps_Comp(double a, double b);											/* Сравнение чисел с точностью до эпсилон*/
void Print_Square_Problem(double a, double b, double c);					/* Вывод квадратного уравнения*/
int  Solve_Square(double a, double b, double c, double* x1, double* x2);	/* Расчет решений квадратного уравнения*/
void Print_Linear_Problem(double b, double c);								/* Вывод линейного уравнения*/
void Reduce_To_0(double* x);												/* Функция, приводящая ответ -0 к 0*/
void TestSquare();


void TestSquare()
{
	double x1 = 0, x2 = 0;
	int nRoots = Solve_Square(1, 0, -4, &x1, &x2);
	ASSERT(nRoots == 2 && Eps_Comp(x1, -2) && Eps_Comp(x2, 2));
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


int Solve_Square(double a, double b, double c, double* x1, double* x2) {
	double D = b * b - 4 * a * c;
	double sqd = sqrt(D);
	if (Eps_Comp(a, 0)) {
		Print_Linear_Problem(b, c);
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
	Print_Square_Problem(a, b, c);
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