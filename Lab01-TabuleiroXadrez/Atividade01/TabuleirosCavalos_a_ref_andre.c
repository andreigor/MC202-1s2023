#include <stdio.h>
#include <stdbool.h>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define MAX_POSSIBLE_KNIGHT_MOVES 8


char board[BOARD_HEIGHT][BOARD_WIDTH];
int x_displacements[MAX_POSSIBLE_KNIGHT_MOVES] = {-1, 1, 2, 2, 1, -1, -2, -2};
int y_displacements[MAX_POSSIBLE_KNIGHT_MOVES] = {2, 2, 1, -1, -2, -2, -1, 1};

typedef struct _position{
    int row;
    int col;
} position;

int charToInt(char c){
    int answer = (int)(c - 'A');
    return answer;
}

char intToChar(int i){
    int answer = (char)((char)i + 'A');
    return answer;
}

void initializeBoard(){
    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = '-';
        }
    }
}

void printBoard(){
    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

position readAndAddKnight(){
    char row = ' ';
    int intRow ,col;
    position knightPosition;

    scanf("%c %d", &row, &col);
    intRow = charToInt(row);

    board[intRow][col] = 'N';

    knightPosition.row = intRow;
    knightPosition.col = col;

    return knightPosition;
}

bool validBoardLocation(int row, int col){
    if (row < 0 || row > 7) return false;
    if (col < 0 || col > 7) return false;

    return true;
}

void printAvailableMoves(int row, int col){
    for (int i = 0; i < MAX_POSSIBLE_KNIGHT_MOVES; i++){
        int dstRow = row + x_displacements[i];
        int dstCol = col + y_displacements[i];
        if (validBoardLocation(dstRow, dstCol)){
            printf("%c %d\n", intToChar(dstRow), dstCol);
        }
    }
}


int main(void){
    position knightPosition;
    initializeBoard();
    knightPosition = readAndAddKnight();
    // printBoard();
    printAvailableMoves(knightPosition.row,knightPosition.col);
    return 0;
}