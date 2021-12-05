#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data[2000];

int main() {
  
  int bufferLength = 255;
  char buffer[bufferLength];

  FILE * f = fopen("input/day1.txt", "r");
  int i = 0;
  while(fgets(buffer, bufferLength, f)) {
    data[i++] = atoi(buffer);
  }

  int c = 0;
  for (int j = 1; j < 2000; j++) {
    if (data[j] > data[j - 1]) c++;
  }

  printf("%d\n", c);
}
