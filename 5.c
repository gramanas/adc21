#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char gamma_s[13];
char epsilon_s[13];

int count_ones[12] = { 0 };

int main() {
  
  int bufferLength = 255;
  char buffer[bufferLength];
  int c = 0;

  FILE * f = fopen("input/day3.txt", "r");
  while(fgets(buffer, bufferLength, f)) {
    for (int j = 0; j < 12; j++) {
      if (buffer[j] == '1') {
        count_ones[j]++;
      }
    }
    c++;
  }

  int j = 0;
  for (; j < 12; j++) {
    if (count_ones[j] >= (c / 2)) {
      gamma_s[j] = '1';
      epsilon_s[j] = '0';
    } else {
      gamma_s[j] = '0';
      epsilon_s[j] = '1';
    }
  }

  gamma_s[j] = '\0';
  epsilon_s[j] = '\0';

  char *ignore;
  long G = strtol(gamma_s, &ignore, 2);
  long E = strtol(epsilon_s, &ignore, 2);

  printf("%ld\n", G * E);
}
