#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _point {
  int x;
  int y;
} point;

typedef struct _segment {
  point s; // start
  point e; // end
} segment;

int tbl[1000][1000];

segment segments[1000];
int segments_n = 0;
int count = 0;

void pprint_segment(int i) {
  printf("Segment %d: [%d,%d] -> [%d,%d]\n", i, segments[i].s.x, segments[i].s.y, segments[i].e.x, segments[i].e.y);
}

void print_segment(int i) {
  printf("%d,%d -> %d,%d\n", segments[i].s.x, segments[i].s.y, segments[i].e.x, segments[i].e.y);
}

int segment_is_v_or_h(int i) {
  return (segments[i].s.x == segments[i].e.x || segments[i].s.y == segments[i].e.y);
}

void print_table() {
  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      if (tbl[x][y] == 0) printf(".");
      else {
        printf("%d", tbl[x][y]);
      }
    }
  printf("\n");
  }
}

void tbl_count() {
  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      if (tbl[x][y] > 1) {
        count++;
      }
    }
  }
}

// only draws horizontal or vertical segments
void draw_hv_segment_to_tbl(int i) {
  if (segments[i].s.x == segments[i].e.x &&
      segments[i].s.y > segments[i].e.y) {
    for (int j = segments[i].e.y; j <= segments[i].s.y; j++ ) {
      tbl[j][segments[i].s.x]++;
    }
  }
  else if (segments[i].s.x == segments[i].e.x &&
           segments[i].s.y < segments[i].e.y) {
    for (int j = segments[i].s.y; j <= segments[i].e.y; j++ ) {
      tbl[j][segments[i].s.x]++;
    }
  }    
  else if (segments[i].s.y == segments[i].e.y &&
           segments[i].s.x > segments[i].e.x) {
    for (int j = segments[i].e.x; j <= segments[i].s.x; j++ ) {
      tbl[segments[i].s.y][j]++;
    }
  }    
  else if (segments[i].s.y == segments[i].e.y &&
           segments[i].s.x < segments[i].e.x) {
    for (int j = segments[i].s.x; j <= segments[i].e.x; j++ ) {
      tbl[segments[i].s.y][j]++;
    }
  }    
}

int main() {
  int bufferLength = 255;
  char buffer[bufferLength];

  FILE * f = fopen("input/day5.txt", "r");
  while(fgets(buffer, bufferLength, f)) {
    char *token, *subtoken;
    char *saveptr1, *saveptr2;

    token = strtok_r(buffer, " -> ", &saveptr1);
    subtoken = strtok_r(token, ",", &saveptr2);
    segments[segments_n].s.x = atoi(subtoken);
    subtoken = strtok_r(NULL, ",", &saveptr2);
    segments[segments_n].s.y = atoi(subtoken);

    token = strtok_r(NULL, " -> ", &saveptr1);
    subtoken = strtok_r(token, ",", &saveptr2);
    segments[segments_n].e.x = atoi(subtoken);
    subtoken = strtok_r(NULL, ",", &saveptr2);
    segments[segments_n].e.y = atoi(subtoken);

    segments_n++;
  }

  for (int i = 0; i < segments_n; i++) {
    if (segment_is_v_or_h(i))
      draw_hv_segment_to_tbl(i);
  }

  //print_table();
  tbl_count();
  printf("%d\n", count);
}
