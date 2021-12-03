#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long find_CO2_scrubber_rating(char dt[1000][13], int count, int bit) {
  int count_ones = 0;
  int next_bit = bit + 1;
  int next_count = 0;
  char next_dt[1000][13];
  char *ignore;
  if (count == 1)
    return strtol(dt[0], &ignore, 2);

  if (bit == 12)
    return -1;
  
  // count 1's for bit `bit`
  for (int i = 0; i < count; i++) {
    if (dt[i][bit] == '1') {
      count_ones++;
    }
  }

  // form new list
  char choice = count_ones < (count / 2) ? '1' : '0';
  for (int i = 0; i < count; i++) {
    if (dt[i][bit] == choice) {
      strcpy(next_dt[next_count++], dt[i]);
    }
  }

  return find_CO2_scrubber_rating(next_dt, next_count, next_bit);
}

long find_oxygen_geneator_rating(char dt[1000][13], int count, int bit) {
  int count_ones = 0;
  int next_bit = bit + 1;
  int next_count = 0;
  char next_dt[1000][13];
  char *ignore;
  if (count == 1)
    return strtol(dt[0], &ignore, 2);

  if (bit == 12)
    return -1;
  
  // count 1's for bit `bit`
  for (int i = 0; i < count; i++) {
    if (dt[i][bit] == '1') {
      count_ones++;
    }
  }

  // form new list
  char choice = count_ones >= (count / 2) ? '1' : '0';
  for (int i = 0; i < count; i++) {
    if (dt[i][bit] == choice) {
      strcpy(next_dt[next_count++], dt[i]);
    }
  }

  return find_oxygen_geneator_rating(next_dt, next_count, next_bit);
}

int main() {
  int bufferLength = 255;
  char buffer[bufferLength];
  char data[1000][13];

  int c = 0;

  FILE * f = fopen("input/day3.txt", "r");
  int i = 0;
  while(fgets(buffer, bufferLength, f)) {
    strcpy(data[c++], buffer);
  }

  printf("%d\n", find_oxygen_geneator_rating(data, c, 0) * find_CO2_scrubber_rating(data, c, 0));
}
