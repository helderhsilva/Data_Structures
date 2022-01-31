#include <stdio.h>

int main(void)
{
  int myarray[10], j = 2;

  printf("j is %d \n", j);

  for (int i = 0; i < 10; i++)
  {
    myarray[i] = i * i;
  }
  printf("j is %d \n", j);

  return 0;
}