#include <stdio.h>
#include <locale.h>
#include <math.h>


char white_list[13] = { '0', '1', '2', '3', '4', '5',	/* белый список вводимых символов */
						'6', '7', '8', '9', '.', ',', '-' };
int n = 13;												/* размер белого списка */


int find_element(char el)
{
	for (int i = 0; i < n; i++) {
		if (white_list[i] == el) {
			return 1;
		}
	}
	return 0;
}


main()
{
	setlocale(LC_ALL, "Rus");
	double indices[3] = { 0, 0, 0 };	/* Массив коэффициентов уравнения */
	int signs[3] = { 0, 0, 0 };			/* Количество знаков после запятой */
	int z;								/* Вводимый элемент */
	int pointed = 0;					/* Введена ли точка или запятая как разделитель в числе */
	int j = 1;							/* Десятичная степень дробной части коэффициента */
	int pass = 0;						/* Считывать ли символ*/
	int minus = 1;						/* Знак коэффициента*/
	int q = 0;							/* Порядковый номер символа */
	printf("Введите коэффициенты квадратного уравнения вида ax^2 + bx + c = 0\n");
	for (int i = 0; i < 3; i++){
		printf("%c = ", 'a' + i);
		pass = 0;
		j = 1;
		pointed = 0;
		minus = 1;
		q = 0;
		while ((z = getchar()) != '\n') {
			if ((find_element(z) == 0 && pass == 0) || (q != 0 && z == '-')) {
				printf("В вашем вводе обнаружен недопустимый символ. Пожалуйста, произведите ввод заново\n");
				--i;
				pass = 1;
			}
			else if (pass == 1) {}
			else if (z == '.' || z == ',') {
				pointed = 1;
			}
			else if (z == '-') {
					minus = -1;
				}
			else {
				z = z - '0';
				if (pointed == 1) {
					indices[i] += z / pow(10.0, j);
					++j;
				}
				else {
					indices[i] = indices[i] * 10 + z;
				}
			}
			++q;
		}
		indices[i] *= minus;
		if (indices[0] == 0) {
			printf("Это не квадратное уравнение:), пока:))\n");
			return 0;
		}
	}
	double D = indices[1] * indices[1] - 4 * indices[0] * indices[2];
	if (D > 0) {
		double x1 = (-indices[1] + pow(D, 0.5)) / (2 * indices[0]);
		double x2 = (-indices[1] - pow(D, 0.5)) / (2 * indices[0]);
		printf("Решения квадратного уравнения вида %gx^2 + %gx + %g = 0\n", indices[0], indices[1], indices[2]);
		printf("x1 = %g\n", x1);
		printf("x2 = %g\n", x2);
	}
	else if (D == 0) {
		double x = -indices[1] / (2 * indices[0]);
		printf("Решение квадратного уравнения вида %gx^2 + %gx + %g = 0\n", indices[0], indices[1], indices[2]);
		printf("x = %g\n", x);
	}
	else{
		double re = -indices[1] / (2 * indices[0]);
		double im = pow(-D, 0.5) / (2 * indices[0]);
		printf("К сожалению, уравнение не имеет решений в действительных числах. Но у нас есть, что Вам предложить:)\n");
		printf("Решение квадратного уравнения вида %gx^2 + %gx + %g = 0\n", indices[0], indices[1], indices[2]);
		printf("x1 = %g + %g * i\n", re, im);
		printf("x2 = %g - %g * i\n", re, im);


	}
	printf("Здесь могла бы быть Ваша реклама:)");
}
