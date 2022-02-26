#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


//clear screen use whichever method is applicable for current operating system
#ifdef _Win32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

//error codes
#define BIT_LENGTH_EXCEEDED 6
#define INVALID_MOVE 7

int gameLoop();
void printBits(unsigned int x);
void putBit(unsigned int* x, int index);
void resetBit(unsigned int* x, int index);
char hasGameFinished(unsigned int* gameData);
int charToInt(char c);
char getBit(unsigned int* x, int index);
char getPlayerChar(unsigned int* gameData, int fieldIndex);
void printGame(unsigned int* gameData);
char getMove(unsigned int* gameData);

int main(){

    gameLoop();

    return EXIT_SUCCESS;
}

int gameLoop(){
    unsigned int gameData = 0;

    while (!hasGameFinished(&gameData)) {
        printGame(&gameData);
        resetBit(&gameData, 18);
        printf("player 1, input your move (numbers 0 - 8)\n");
        putBit(&gameData, charToInt(getMove(&gameData)));

        printGame(&gameData);
        putBit(&gameData, 18);
        printf("player 2, input your move (numbers 0 - 8)\n");
        putBit(&gameData, charToInt(getMove(&gameData)) + 9);
    }

    return 0;
}

char getMove(unsigned int* gameData){
    char move;
    bool hasMoved = false;
    while (!hasMoved) {
        move = (char)getchar_unlocked();
        if(isdigit(move) && move <= 8){
            if (getBit(gameData, 18) == '0') {
                hasMoved = getBit(gameData, move)? true : false;
            }else {
                hasMoved = getBit(gameData, move + 9)? true : false;
            }
            hasMoved = true;
        }else {
            printf("invalid move, retry\n");
        }
    }
    return move;
}

void printGame(unsigned int* gameData){
    clrscr();
    printf("---------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 0), getPlayerChar(gameData, 1), getPlayerChar(gameData, 2));
    printf("---------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 3), getPlayerChar(gameData, 4), getPlayerChar(gameData, 5));
    printf("---------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 6), getPlayerChar(gameData, 7), getPlayerChar(gameData, 8));
    printf("---------\n");
}

char getPlayerChar(unsigned int* gameData, int fieldIndex){
    if(getBit(gameData, fieldIndex) == '1'){
        return 'x';
    }else if (getBit(gameData, fieldIndex + 9) == '1') {
        return 'o';
    }else {
        return ' ';
    }
}

int charToInt(char c){
    return c - '0';
}

char hasGameFinished(unsigned int* gameData){
    return 0;
}

char getBit(unsigned int* x, int index){
    return ((*x & ((unsigned int)1 << index)) >> index) == 1 ? '1' : '0';
}

void resetBit(unsigned int* x, int index){
    if(index > 32){
        exit(BIT_LENGTH_EXCEEDED);
    }
    *x ^= 1 << index;
}

void putBit(unsigned int* x, int index){
    if(index > 32){
        exit(BIT_LENGTH_EXCEEDED);
    }
    *x |= 1 << index;
}

void printBits(unsigned int x)
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}
