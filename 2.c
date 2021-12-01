#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int data[2000];

int main() {
  
  int bufferLength = 255;
  char buffer[bufferLength];

  FILE * f = fopen("input/1.txt", "r");
  int i = 0;
  while(fgets(buffer, bufferLength, f)) {
    data[i++] = atoi(buffer);
  }

  int c = 0;
  for (int j = 3; j < 2000; j++) {
    int g1 = data[j-1] + data[j-2] + data[j-3];
    int g2 = data[j] + data[j-1] + data[j-2];
    if (g2 > g1) c++;
  }

  printf("%d\n", c);
}
