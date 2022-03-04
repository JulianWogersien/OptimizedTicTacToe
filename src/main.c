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

void gameLoop();
void printBits(unsigned int x);
void putBit(unsigned int* x, int index);
void resetBit(unsigned int* x, int index);
bool hasGameFinished(unsigned int* gameData);
int charToInt(char c);
char getBit(unsigned int* x, int index);
char getPlayerChar(unsigned int* gameData, int fieldIndex);
void printGame(unsigned int* gameData);
char getMove(unsigned int* gameData);

int main(){

    gameLoop();

    return EXIT_SUCCESS;
}

void gameLoop(){
    unsigned int gameData = 0;
    putBit(&gameData, 19);
    
    while (getBit(&gameData, 19) == '1') {
        printGame(&gameData);
        resetBit(&gameData, 18);
        printf("player 1, input your move (numbers 0 - 8)\n");
        putBit(&gameData, charToInt(getMove(&gameData)));
        if (hasGameFinished(&gameData)) {
            printf("congratulations player 1 you won");
            resetBit(&gameData, 19);
        }else{
            printGame(&gameData);
            putBit(&gameData, 18);
            printf("player 2, input your move (numbers 0 - 8)\n");
            putBit(&gameData, charToInt(getMove(&gameData)) + 9);

            if (hasGameFinished(&gameData)) {
                printf("congratulations player 2 you won");
                resetBit(&gameData, 19);
            }
        }
    }
}

char getMove(unsigned int* gameData){
    char move;
    bool hasMoved = false;
    while (!hasMoved) {
        move = (char)getchar_unlocked();
        if(isdigit(move) && move <= '8'){
            if (getBit(gameData, charToInt(move)) == '0' && getBit(gameData, charToInt(move) + 9) == '0') {
                hasMoved = true;
            }
        }
    }
    return move;
}

void printGame(unsigned int* gameData){
    clrscr();
    printf("-------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 0), getPlayerChar(gameData, 1), getPlayerChar(gameData, 2));
    printf("-------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 3), getPlayerChar(gameData, 4), getPlayerChar(gameData, 5));
    printf("-------\n");
    printf("|%c|%c|%c|\n", getPlayerChar(gameData, 6), getPlayerChar(gameData, 7), getPlayerChar(gameData, 8));
    printf("-------\n");
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

bool hasGameFinished(unsigned int* gameData){
    bool hasGameFinished = false;

    if (getBit(gameData, 0) == '1' && getBit(gameData, 1) == '1' && getBit(gameData, 2) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 3) == '1' && getBit(gameData, 4) == '1' && getBit(gameData, 5) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 6) == '1' && getBit(gameData, 7) == '1' && getBit(gameData, 8) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 0) == '1' && getBit(gameData, 3) == '1' && getBit(gameData, 6) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 1) == '1' && getBit(gameData, 4) == '1' && getBit(gameData, 7) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 2) == '1' && getBit(gameData, 5) == '1' && getBit(gameData, 8) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 0) == '1' && getBit(gameData, 4) == '1' && getBit(gameData, 8) == '1') {
        hasGameFinished = true;
    }else if (getBit(gameData, 2) == '1' && getBit(gameData, 4) == '1' && getBit(gameData, 6) == '1') {
        hasGameFinished = true;
    }

    return hasGameFinished;
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
