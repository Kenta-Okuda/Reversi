#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define BLANK 0
#define BLACK 1
#define WHITE 2
#define FRAME 8

char board[FRAME][FRAME];
char turnFlg;

void init() {
  int i, j;
  for(i = 0; i < FRAME; i++) {
    for(j = 0; j < FRAME; j++) {
      board[i][j] = BLANK;
    }
  }
  board[FRAME/2 - 1][FRAME/2 -1] = board[FRAME/2][FRAME/2] = WHITE;
  board[FRAME/2 - 1][FRAME/2] = board[FRAME/2][FRAME/2 - 1] = BLACK;
  turnFlg = BLACK;
}

void viewBoard() {
  int i, j;
  printf("  ");
  for(i = 0; i < FRAME; i++) printf(" %d",i);
  printf("\n");
  for(i = 0; i < FRAME; i++) {
    printf("%d |",i);
    for(j = 0; j < FRAME; j++) {
      switch(board[i][j]) {
        case BLANK:
          printf(" ");
          break;
        case BLACK:
          printf("●");
          break;
        case WHITE:
          printf("○");
          break;
        default: printf(" ");
      }
      printf("|");
    }
    printf("\n");
  }
}

int isPutStone(int row, int col) {
  int vec_row[] = {-1, -1, -1, 0, 1, 1, 1, 0};
  int vec_col[] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int vec, i;
  int flg = FALSE;
  int vrow, vcol;
  if(row < 0 || col < 0 || row >= FRAME || col >= FRAME) return FALSE;
  if(board[row][col] != BLANK) return FALSE;
  for(vec = 0; vec < 8; vec++) {
    vrow = row;
    vcol = col;
    flg = FALSE;
    for(i = 0; i < FRAME; i++) {
      vrow += vec_row[vec];
      vcol += vec_col[vec];
      if(board[vrow][vcol] == BLANK)  break;
      if(board[vrow][vcol] == ((turnFlg == BLACK) ? WHITE : BLACK)) {
        flg = TRUE;
        continue;
      }
      if(flg) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

int main() {
  int row, col;
  init();

  while(1) {
    viewBoard();

    if(turnFlg == BLACK) {
      printf("●のターン > ");
    } else {
      printf("○のターン > ");
    }
    while(1) {
      scanf("%d%d",&row, &col);
      if(isPutStone(row, col)) break;
      printf("Error: その場所には置けません。\n> ");
    }
    board[row][col] = turnFlg;
    turnFlg = (turnFlg == BLACK) ? WHITE : BLACK;
  }
  return 0;
}

