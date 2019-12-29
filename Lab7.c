#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void printBoard(char board[][26], int n) {
    char row = 'a', col = 'a';
    printf("  ");
    for(int count = 0; count < n; count++, row++) {
        printf("%c", row);
    }
    printf("\n");
    for(int rowIndex = 0; rowIndex < n; rowIndex++, col++) {
        printf("%c ", col);
        for(int colIndex = 0; colIndex < n; colIndex++) {
            printf("%c", board[rowIndex][colIndex]);
        }
        printf("\n");
    }
}

void configuration(char board[][26], int n) {
    char colour, row, col, garbage;
    int rowIndex, colIndex;
    printf("Enter board configuration:\n");
    while((colour != '!') && (row != '!') && (col != '!')) {
        scanf(" %c%c%c%c", &colour, &row, &col, &garbage);
        if((colour == 'B') || (colour == 'W')) {
            if(((row >= 'a') && (row < 'a'+n)) && ((col >= 'a') && (col < 'a'+n))) {
                rowIndex = row - 97;
                colIndex = col - 97;
                board[rowIndex][colIndex] = colour;
            }
        }
    }
}

char oppositeColour(char colour) {
    int opposite;
    if(colour == 'B') {
        opposite = 'W';
    }else if(colour == 'W') {
        opposite = 'B';
    }
    return opposite;
}

int availableMoves(char board[][26], int n, char colour) {
    int moves = 0;
    char oppColour = oppositeColour(colour);
    
    printf("Available moves for %c:\n", colour);
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            if(board[row][col] == 'U') {
                
                if(board[row][col-1] == oppColour) { //West
                    int count = 1;
                    while(board[row][col-count] == oppColour) count++;
                    if(board[row][col-count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row][col+1] == oppColour) { //East
                    int count = 1;
                    while(board[row][col+count] == oppColour) count++;
                    if(board[row][col+count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row-1][col] == oppColour) { //North
                    int count = 1;
                    while(board[row-count][col] == oppColour) count++;
                    if(board[row-count][col] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row+1][col] == oppColour) { //South
                    int count = 1;
                    while(board[row+count][col] == oppColour) count++;
                    if(board[row+count][col] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row-1][col-1] == oppColour) { //Northwest
                    int count = 1;
                    while(board[row-count][col-count] == oppColour) count++;
                    if(board[row-count][col-count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row-1][col+1] == oppColour) { //Northeast
                    int count = 1;
                    while(board[row-count][col+count] == oppColour) count++;
                    if(board[row-count][col+count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row+1][col-1] == oppColour) { //Southwest
                    int count = 1;
                    while(board[row+count][col-count] == oppColour) count++;
                    if(board[row+count][col-count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
                
                if(board[row+1][col+1] == oppColour) { //Southeast
                    int count = 1;
                    while(board[row+count][col+count] == oppColour) count++;
                    if(board[row+count][col+count] == colour) printf("%c%c\n", row+97, col+97), moves++;
                }
            }
        }
    }
    
    return moves;
}

bool positionInBounds(int n, int row, int col) {
    if((row-97 >= 0) && (row-97 < n) && (col-97 >= 0) && (col-97 < n)) {
        return true;
    }else {
        return false;
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int i = row + deltaRow, j = col + deltaCol;
    
    if(board[row][col] != 'U') return false;
    
    if(colour == 'W') {
        if(board[i][j] == 'B') {
            while(board[i][j] == 'B') {
                i = i + deltaRow;
                j = j + deltaCol;
            }
            if(board[i][j] == 'W') return true;
        }
    }
        
    if(colour == 'B') {
        if(board[i][j] == 'W') {
            while(board[i][j] == 'W') {
                i = i + deltaRow;
                j = j + deltaCol;
            }
            if(board[i][j] == 'B') return true;
        }
    }
    return false;
}

void change(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int i = row + deltaRow, j = col + deltaCol;
    
    board[row][col] = colour;
    
    while((board[i][j] != colour) && (i < n-1) && (j < n-1) && (i >= 0) && (j >= 0)) {
        board[i][j] = colour;
        i = i + deltaRow;
        j = j + deltaCol;
    }
}

void input(char board[][26], int n) {
    unsigned char row, col, colour;
    bool valid1 = false, valid2 = false, valid3 = false, valid4 = false, valid5 = false, valid6 = false, valid7 = false, valid8 = false, inBounds = false;
    
    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &row, &col);
    inBounds = positionInBounds(n, row, col);
    
    valid1 = checkLegalInDirection(board, n, row-97, col-97, colour, 0,-1); // West
    valid2 = checkLegalInDirection(board, n, row-97, col-97, colour, 0, 1); // East
    valid3 = checkLegalInDirection(board, n, row-97, col-97, colour,-1, 0); // North
    valid4 = checkLegalInDirection(board, n, row-97, col-97, colour, 1, 0); // South
    valid5 = checkLegalInDirection(board, n, row-97, col-97, colour,-1,-1); // Northwest
    valid6 = checkLegalInDirection(board, n, row-97, col-97, colour,-1, 1); // Northeast
    valid7 = checkLegalInDirection(board, n, row-97, col-97, colour, 1,-1); // Southwest
    valid8 = checkLegalInDirection(board, n, row-97, col-97, colour, 1, 1); // Southeast
    if(valid1 == true) change(board, n, row-97, col-97, colour, 0,-1);
    if(valid2 == true) change(board, n, row-97, col-97, colour, 0, 1);
    if(valid3 == true) change(board, n, row-97, col-97, colour,-1, 0);
    if(valid4 == true) change(board, n, row-97, col-97, colour, 1, 0);
    if(valid5 == true) change(board, n, row-97, col-97, colour,-1,-1);
    if(valid6 == true) change(board, n, row-97, col-97, colour,-1, 1);
    if(valid7 == true) change(board, n, row-97, col-97, colour, 1,-1);
    if(valid8 == true) change(board, n, row-97, col-97, colour, 1, 1);
    
    if((inBounds == true) && (valid1 == true || valid2 == true || valid3 == true || valid4 == true || valid5 == true || valid6 == true || valid7 == true || valid8 == true)) {
        printf("Valid move.\n");
    }else {
        printf("Invalid move.\n");
    }
}

int main(void) {
    
    int n = 0;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    char board[26][26];
    
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            board[row][col] = 'U';
        }
    }
    
    board[(n/2)-1][(n/2)-1] = 'W';
    board[n/2][n/2] = 'W';
    board[(n/2)-1][n/2] = 'B';
    board[n/2][(n/2)-1] = 'B';
    printBoard(board, n);
    configuration(board, n);
    printBoard(board, n);
    availableMoves(board, n, 'B');
    availableMoves(board, n, 'W');
    input(board, n);
    printBoard(board, n);
    
    return 0;
}