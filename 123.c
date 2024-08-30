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

// ��ʼ����Ϸ��
void initializeBoard() {
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = '0';
            display[i][j] = '*';
        }
    }
}

// ���õ���
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

// ����ÿ�����ӵ�����
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

// ��ʾ��Ϸ��
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

// ִ���û�����ĵ������
int revealCell(int row, int col) {
    if (board[row][col] == 'M') {
        return 0; // �ȵ����ף���Ϸ����
    } else {
        display[row][col] = board[row][col];
        return 1; // ������Ϸ
    }
}

// �ж���Ϸ�Ƿ��ʤ
int checkWin() {
    int covered_cells = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (display[i][j] == '*') {
                covered_cells++;
            }
        }
    }
    return covered_cells == MINES; // ���з��׸��Ӷ����ҿ����ʤ
}

// ����Ϸѭ��
void playGame() {
    int row, col;
    int game_over = 0;
    while (!game_over) {
        printBoard(display);
        printf("�����к��� (���� 3 4): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("������Ч�����������롣\n");
            continue;
        }

        if (!revealCell(row, col)) {
            printf("�ȵ����ף���Ϸ������\n");
            printBoard(board);
            game_over = 1;
        } else if (checkWin()) {
            printf("��ϲ�㣬Ӯ������Ϸ��\n");
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

