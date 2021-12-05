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
int skips[100]; // boards to skip
int nums_n = 0;
int skips_n = 0;

board boards[1000];
int boards_n = -1;

void print_board(int id) {
  printf("Board %d:\n", id);
  for (int x = 0; x < 5; x++) {
    printf("%d| ", x);
    for (int y = 0; y < 5; y++) {
      char c1 = boards[id].i[x][y].marked ? '[' : ' ';
      char c2 = boards[id].i[x][y].marked ? ']' : ' ';
      printf("%c%2d%c ", c1, boards[id].i[x][y].n, c2);
    }
    printf("\n");
  }
  printf("\n");
}

void print_boards() {
  for (int j = 0; j < boards_n; j++) {
    print_board(j);
  }
}

int contains(int list[100], int n) {
  for (int i = 0; i < 100; i++) {
    if (list[i] == n) return 1;
  }
  return 0;
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

int mark_number(int n) {
  for (int j = 0; j < boards_n; j++) {
    if (contains(skips, j)) {
      printf("Skipping %d\n", j);
      continue;
    }
    // mark board
    for (int x = 0; x < 5; x++) {
      for (int y = 0; y < 5; y++) {
        if (boards[j].i[x][y].n == n) {
          boards[j].i[x][y].marked = 1;
        }
      }
    }
    // check if wins
    int flag = 0;
    for (int x = 0; x < 5; x++) {
      if (sum_marked_row(boards[j].i, x) == 5 ||
          sum_marked_col(boards[j].i, x) == 5) {
        flag = 1;
      }
    }
    if (flag) {
      if (skips_n == boards_n - 1) return j;
      printf("Adding %2d to skips\n", j);
      skips[skips_n++] = j;
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

  // set skips to -1
  for (int i = 0; i < 100; i++) {
    skips[i] = -1;
  }
  
  int j;
  int last_win;
  for (j = 0; j < nums_n; j++) {
    last_win = mark_number(nums[j]);
    if (last_win != -1) {
      break;
    }
  }

  // return solution
  printf("board %d is the last to win at number %d which is %d, %d * %d = %d\n", last_win, j, nums[j], nums[j], sum_unmarked(last_win), nums[j] * sum_unmarked(last_win));
  
  //print_boards();
}
