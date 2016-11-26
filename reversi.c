#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define BLANK 0
#define BLACK 1
#define WHITE 2
#define FRAME 8

char board[FRAME][FRAME];
char turnFlg;
int vec_row[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int vec_col[] = {-1, 0, 1, 1, 1, 0, -1, -1};
  
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

void dispBoard() {
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
  int vec;
  int flg = FALSE;
  int vrow, vcol;
  if(row < 0 || col < 0 || row >= FRAME || col >= FRAME) return FALSE;
  if(board[row][col] != BLANK) return FALSE;
  for(vec = 0; vec < 8; vec++) {
    vrow = row;
    vcol = col;
    flg = FALSE;
    while(1) {
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
      break;
    }
  }
  return FALSE;
}

void flip(int row, int col) {
  int vec;
  int flg = FALSE;
  int vrow, vcol;
  for(vec = 0; vec < 8; vec++) {
    vrow = row;
    vcol = col;
    flg = FALSE;
    while(1) {
      vrow += vec_row[vec];
      vcol += vec_col[vec];
      if(board[vrow][vcol] == BLANK)  break;
      if(board[vrow][vcol] == ((turnFlg == BLACK) ? WHITE : BLACK)) {
        flg = TRUE;
        continue;
      }
      if(flg) {
        board[row][col] = (turnFlg == BLACK) ? BLACK : WHITE;
        vrow = row;
        vcol = col; 
        while(1) {
          vrow += vec_row[vec];
          vcol += vec_col[vec];
          if(board[vrow][vcol] != ((turnFlg == BLACK) ? BLACK : WHITE)) {
            board[vrow][vcol] = (turnFlg == BLACK) ? BLACK : WHITE; 
          } else {
            break;
          }
        }
      }
      break;
    }
  }
}

int isAvailable() {
  int row, col;
  int cnt = 0;
  for(row = 0; row < FRAME; row++) {
    for(col = 0; col < FRAME; col++) {
      if(isPutStone(row, col)) cnt++;
    }
  }
  if(cnt > 0) return TRUE;
  return FALSE;
}

void input(int *row, int *col) {
  if(!isAvailable()) {
    printf("PASS\n");
    turnFlg = (turnFlg == BLACK) ? WHITE : BLACK;
  }
  if(turnFlg == BLACK) {
    printf("●のターン > ");
  } else {
    printf("○のターン > ");
  }
  while(1) {
    scanf("%d%d",row, col);
    if(isPutStone(*row, *col)) break;
    printf("Error: その場所には置けません。\n> ");
  }

}

int isFinish() {
  int row, col;
  for(row = 0; row < FRAME; row++) {
    for(col = 0; col < FRAME; col++) {
      if(board[row][col] == BLANK) return FALSE;
    }
  }
  return TRUE;
}

void dispScore() {
  int row, col;
  int score_black = 0, score_white = 0;
  for(row = 0; row < FRAME; row++) {
    for(col = 0; col < FRAME; col++) {
      if(board[row][col] == BLACK) {
        score_black++;
      } else if(board[row][col] == WHITE) {
        score_white++;
      }
    }
  }
  if(score_black > score_white) {
    printf("WIN: BLACK\n");
  } else if(score_white > score_black) {
    printf("WIN: WHITE\n");
  } else {
    printf("DRAW\n");
  }
  printf("BLACK(%d) : WHITE(%d)\n",score_black, score_white);
}

int main() {
  int row, col;

  init();
  while(1) {
    dispBoard();
    input(&row, &col);
    flip(row, col);
    if(isFinish()) break;
    turnFlg = (turnFlg == BLACK) ? WHITE : BLACK;
  }
  dispScore();
  return 0;
}

