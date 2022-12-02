//
// Created by Tr on 6/4/2019.
//

#ifndef INC_1_GAME_CONSOLE_H
#define INC_1_GAME_CONSOLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <dos.h>
#include <direct.h>
#include <dir.h>
#include <io.h>


#define MAXLINES 200
#define MAXLEN 100
//tells us if a variable is in game
struct game_variables{
    int solidblock;
    int deathblock;
    int moveblock;
    int wall;
    int up;
    int right;
    int down;
    int left;
    int character;
    int game_time;
    int target;
    int rpoint;
    int object;
    int opp;
    int attack;
    int put;
    int raindb;
    int game_exit;
};


struct player{
    int computer;
    char name[30];
    int score;
    char ch;
    int i;
    int j;
};

struct object{
    char ch;
    int i;
    int j;
};

struct bullet{
    char shape;
    int i;
    int j;
    int life_time;
};


struct rain_d{
    int i;
    int j;
    char shape;
};



int read_game(char *filename); //returns number of read lines
int read_map(char *filename);
void move(struct player *ply, char side);
void print(void);
int seeds(int n);
char next_move(struct player *ply, char ch);
void SetColor(int ForgC);
int random(int lower, int upper);
void game_over(char *winner);
void delay(unsigned int mseconds);
void print2();


#endif //INC_1_GAME_CONSOLE_H
