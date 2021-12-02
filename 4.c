#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  
  int bufferLength = 255;
  char buffer[bufferLength];

  int pos = 0;
  int depth = 0;
  int aim = 0;

  FILE * f = fopen("input/day2.txt", "r");
  int i = 0;
  while(fgets(buffer, bufferLength, f)) {
    int n = strlen(buffer);
    if (buffer[0] == 'f') {
      pos += buffer[n-2] - '0';
      depth += (buffer[n-2] - '0') * aim;
    } else if (buffer[0] == 'd') {
      aim += buffer[n-2] - '0';
    } else {
      aim -= buffer[n-2] - '0';
    }
  }

  printf("%d\n", pos * depth);
}
