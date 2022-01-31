#include <stdio.h>

/* Print the sum of the integers from 1 to 1000 */
int main()
{
  int i;
  int sum;

  sum = 0;
  for (i = 0; i <= 1000; i++)
  {
    sum += i;
  }
  printf("%d \n", sum);

  return 0;
}