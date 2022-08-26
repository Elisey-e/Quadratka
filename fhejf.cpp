#include <stdio.h>

void show_array (double array [], int number_of_elements)
{
   for (int i = 0; i < number_of_elements; i++) {
       printf("%g\t", array[i]);
   }
   printf("\n");
}

int main()
{
   double little_numbers[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
   show_array(little_numbers, 5);
}