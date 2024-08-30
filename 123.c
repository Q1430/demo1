#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define MINES 10

char board[ROWS][COLS];
char display[ROWS][COLS];
int mine_positions[MINES][2];
int i,j,k;

// 初始化游戏板
void initializeBoard() {
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = '0';
            display[i][j] = '*';
        }
    }
}

// 放置地雷
void placeMines() {
    srand(time(NULL));
    int count = 0;
    while (count < MINES) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col] != 'M') {
            board[row][col] = 'M';
            mine_positions[count][0] = row;
            mine_positions[count][1] = col;
            count++;
        }
    }
}

// 计算每个格子的数字
void calculateNumbers() {
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == 'M') {
                continue;
            }
            int count = 0;
            for (k = 0; k < 8; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && board[ni][nj] == 'M') {
                    count++;
                }
            }
            board[i][j] = '0' + count;
        }
    }
}

// 显示游戏板
void printBoard(char b[ROWS][COLS]) {
    printf("   ");
    for (j = 0; j < COLS; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (i = 0; i < ROWS; i++) {
        printf("%d  ", i);
        for (j = 0; j < COLS; j++) {
            printf("%c ", b[i][j]);
        }
        printf("\n");
    }
}

// 执行用户输入的点击操作
int revealCell(int row, int col) {
    if (board[row][col] == 'M') {
        return 0; // 踩到地雷，游戏结束
    } else {
        display[row][col] = board[row][col];
        return 1; // 继续游戏
    }
}

// 判断游戏是否获胜
int checkWin() {
    int covered_cells = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (display[i][j] == '*') {
                covered_cells++;
            }
        }
    }
    return covered_cells == MINES; // 所有非雷格子都被揭开则获胜
}

// 主游戏循环
void playGame() {
    int row, col;
    int game_over = 0;
    while (!game_over) {
        printBoard(display);
        printf("输入行和列 (例如 3 4): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("输入无效，请重新输入。\n");
            continue;
        }

        if (!revealCell(row, col)) {
            printf("踩到地雷，游戏结束！\n");
            printBoard(board);
            game_over = 1;
        } else if (checkWin()) {
            printf("恭喜你，赢得了游戏！\n");
            printBoard(board);
            game_over = 1;
        }
    }
}

int main() {
	
    initializeBoard();
    placeMines();
    calculateNumbers();
    playGame();
    return 0;
}

