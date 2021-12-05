#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pos {
  int n;
  int marked;
} pos;

typedef struct _board {
  pos i[5][5];
} board;

int nums[100];
int nums_n = 0;

board boards[1000];
int boards_n = -1;

void print_boards() {
  for (int j = 0; j < boards_n; j++) {
    printf("Board %d:\n", j);
    for (int x = 0; x < 5; x++) {
      printf("%d| ", x);
      for (int y = 0; y < 5; y++) {
        char c1 = boards[j].i[x][y].marked ? '[' : ' ';
        char c2 = boards[j].i[x][y].marked ? ']' : ' ';
        printf("%c%2d%c ", c1, boards[j].i[x][y].n, c2);
      }
      printf("\n");
    }
    printf("\n");
  }
}

int sum_marked_col(pos l[5][5], int col) {
  return l[0][col].marked + l[1][col].marked + l[2][col].marked + l[3][col].marked + l[4][col].marked;
}

int sum_marked_row(pos l[5][5], int row) {
  return l[row][0].marked + l[row][1].marked + l[row][2].marked + l[row][3].marked + l[row][4].marked;
}

int sum_unmarked(int board_id) {
  int acc = 0;
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      if (!boards[board_id].i[x][y].marked) {
        acc += boards[board_id].i[x][y].n;
      }
    }
  }
  return acc;
}

// returns the id of the winning board, -1 otherwise
int mark_number(int n) {
  for (int j = 0; j < boards_n; j++) {
    // mark board
    for (int x = 0; x < 5; x++) {
      for (int y = 0; y < 5; y++) {
        if (boards[j].i[x][y].n == n) {
          boards[j].i[x][y].marked = 1;
        }
      }
    }
    // check if wins
    for (int x = 0; x < 5; x++) {
      if (sum_marked_row(boards[j].i, x) == 5 ||
          sum_marked_col(boards[j].i, x) == 5) {
        return j;
      }
    }
  }

  return -1;
}

int main() {
  int bufferLength = 1023;
  char buffer[bufferLength];

  FILE * f = fopen("input/day4.txt", "r");
  int i = 0;

  while(fgets(buffer, bufferLength, f)) {
    if (i == 0) {
      char *token;
      
      token = strtok(buffer, ",");
      while (token != NULL) {
        nums[nums_n++] = atoi(token);
        token = strtok(NULL, ",");
      }
    } else if (i % 6 == 1) {
      boards_n++;
    } else {
      char *token;
      int x = 0;

      token = strtok(buffer, " ");
      while (token != NULL) {
        boards[boards_n].i[((i - 2) % 6)][x++].n = atoi(token);
        token = strtok(NULL, " ");
      }
    }
    i++;
  }
  // add the last one
  boards_n++;

  // win board 99 with col
  /* printf("%d\n", mark_number(15)); */
  /* printf("%d\n", mark_number(24)); */
  /* printf("%d\n", mark_number(54)); */
  /* printf("%d\n", mark_number(67)); */
  /* printf("%d\n", mark_number(64)); */

  // win board 99 with row
  /* printf("%d\n", mark_number(15)); */
  /* printf("%d\n", mark_number(95)); */
  /* printf("%d\n", mark_number(2)); */
  /* printf("%d\n", mark_number(82)); */
  /* printf("%d\n", mark_number(33)); */
  int j;
  int win;
  for (j = 0; j < nums_n; j++) {
    win = mark_number(nums[j]);
    if (win != -1) {
      break;
    }
  }

  // return solution
  printf("board %d wins at number %d which is %d, %d * %d = %d\n", win, j, nums[j], nums[j], sum_unmarked(win), nums[j] * sum_unmarked(win));

  //print_boards();
}
