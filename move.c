//
// Created by Tr on 6/27/2019.
//
#include "game_console.h"

extern char solidblock;
extern char deathblock;
extern char moveblock;
extern char wall;
extern char up;
extern char right;
extern char down;
extern char left;
extern char character;
extern int game_time;
extern char target;
extern char object;
extern char opp[];
extern char put[];
extern int put_limit;
extern char rpoint_char;
extern int rpoint_score;
extern int rpoint_num;
extern int attack;
extern int raindb;
extern int map_len;
extern int map_wid;
extern char game_exit;

extern char *game[MAXLINES];
extern char **map;
extern int flag;


void objects(struct player *ply , char side){
    int i = ply->i;
    int j = ply->j;
    if (side == up) {

        if (map[i - 2][j] == wall || map[i - 2][j] == solidblock || map[i-2][j]==deathblock) {
            return;
        }
        else if(map[i-2][j]==moveblock && map[i-3][j]==' ' ){
            map[i-1][j] = ply->ch;
            map[i][j] = ' ';
            map[i-2][j]= object;
            map[i-3][j] = moveblock;
            ply->i = i-1;
            ply->j = j;
        }
        else if(map[i-2][j] == moveblock && (map[i-3][j] == wall || map[i-3][j] == solidblock || map[i-3][j]==deathblock || map[i-3][j]==target)){
            return;
        }
        else if (map[i-2][j]==moveblock && map[i-3][j] == rpoint_char ){
            map[i-1][j] = ply->ch;
            map[i-2][j] = object;
            map[i-3][j]= moveblock;
            map[i][j] = ' ';
            seeds(1);
            ply->i = i-1;
            ply->j;
        }
        else if(map[i-2][j]==rpoint_char){
            map[i-1][j]=ply->ch;
            map[i-2][j]=object;
            map[i][j] = ' ';
            ply->i = i-1;
            ply->j = j;
            seeds(1);
        }
        else if(map[i-2][j]==target){
            game_over(ply->name);
        }

        else {
            map[i - 1][j] = ply->ch;
            map[i][j] = ' ';
            map[i - 2][j] = object;
            ply->i = i - 1;
            ply->j = j;
        }

    }
    else if(side == right){
        if (map[i][j + 2] == wall || map[i][j + 2] == solidblock || map[i][j+2]==deathblock) {
            return;
        }
        else if(map[i][j+2]==moveblock && map[i][j+3]==' ' ){
            map[i][j+1] = ply->ch;
            map[i][j] = ' ';
            map[i][j+2]= object;
            map[i][j+3] = moveblock;
            ply->i = i;
            ply->j = j+1;
        }
        else if(map[i][j+2] == moveblock && (map[i][j+3] == wall || map[i][j+3] == solidblock || map[i][j+3]==deathblock|| map[i][j+3]==target)){
            return;
        }
        else if (map[i][j+2]==moveblock && map[i][j+3] == rpoint_char ){
            map[i][j+1] = ply->ch;
            map[i][j+2] = object;
            map[i][j+3]= moveblock;
            map[i][j] = ' ';
            seeds(1);
            ply->i = i;
            ply->j+1;
        }
        else if(map[i][j+2]==rpoint_char){
            map[i][j+1]=ply->ch;
            map[i][j+2]=object;
            map[i][j] = ' ';
            ply->i = i;
            ply->j = j+1;
            seeds(1);
        }
        else if(map[i][j+2]==target){
            game_over(ply->name);
        }

        else {
            map[i][j + 1] = ply->ch;
            map[i][j] = ' ';
            map[i][j + 2] = object;
            ply->i = i;
            ply->j = j + 1;
        }
    } else if(side == down){
        if (map[i + 2][j] == wall || map[i + 2][j] == solidblock|| map[i+2][j]== object) {
            return;
        }
        else if(map[i+2][j]==moveblock && map[i+3][j]==' ' ){
            map[i+1][j] = ply->ch;
            map[i][j] = ' ';
            map[i+2][j]= object;
            map[i+3][j] = moveblock;
            ply->i = i+1;
            ply->j = j;
        }
        else if(map[i+2][j] == moveblock && (map[i+3][j] == wall || map[i+3][j] == solidblock || map[i+3][j]== deathblock || map[i+3][j]==target)){
            return;
        }
        else if (map[i+2][j]==moveblock && map[i+3][j] == rpoint_char ){
            map[i+1][j] = ply->ch;
            map[i+2][j] = object;
            map[i+3][j]= moveblock;
            map[i][j];
            map[i][j] = ' ';
            seeds(1);
            ply->i = i+1;
            ply->j;
        }
        else if(map[i+2][j]==rpoint_char){
            map[i+1][j]=ply->ch;
            map[i+2][j]=object;
            map[i][j] = ' ';
            ply->i = i+1;
            ply->j = j;
            seeds(1);
        }
        else if(map[i+2][j]==target){
            game_over(ply->name);
        }

        else {
            map[i + 1][j] = ply->ch;
            map[i][j] = ' ';
            map[i + 2][j] = object;
            ply->i = i + 1;
            ply->j = j;
        }
    } else if(side == left){
        if (map[i][j - 2] == wall || map[i][j - 2] == solidblock || map[i][j-2] == deathblock) {
            return;
        }
        else if(map[i][j-2]==moveblock && map[i][j-3]==' ' ){
            map[i][j-1] = ply->ch;
            map[i][j] = ' ';
            map[i][j-2]= object;
            map[i][j-3] = moveblock;
            ply->i = i;
            ply->j = j-1;
        }
        else if(map[i][j-2] == moveblock && (map[i][j-3] == wall || map[i][j-3] == solidblock || map[i][j-3]== deathblock || map[i][j-3]==target)){
            return;
        }
        else if (map[i][j-2]==moveblock && map[i][j-3] == rpoint_char ){
            map[i][j-1] = ply->ch;
            map[i][j-2] = object;
            map[i][j-3]= moveblock;
            map[i][j] = ' ';
            seeds(1);
            ply->i = i;
            ply->j = j-1;
        }
        else if(map[i][j-2]==rpoint_char){
            map[i][j-1]=ply->ch;
            map[i][j-2]=object;
            map[i][j] = ' ';
            ply->i = i;
            ply->j = j-1;
            seeds(1);
        }
        else if(map[i][j-2]==target){
            game_over(ply->name);
        }

        else {
            map[i][j - 1] = ply->ch;
            map[i][j] = ' ';
            map[i][j - 2] = object;
            ply->i = i;
            ply->j = j - 1;
        }
    }

}

void moveBlock(struct player *ply, char side) {
    int i = ply->i;
    int j = ply->j;
    if (side == up) {

        if (map[i - 2][j] == wall || map[i - 2][j] == solidblock || map[i-2][j] == deathblock) {
            return;
        }
        else if(map[i-2][j]==object && map[i-3][j]==' ' ){
            map[i-1][j] = ply->ch;
            map[i][j] = ' ';
            map[i-2][j]= moveblock;
            map[i-3][j] = object;
            ply->i = i-1;
            ply->j = j;
        }
        else if(map[i-2][j] == object && (map[i-3][j] == wall || map[i-3][j] == solidblock || map[i-3][j]==deathblock)){
            return;
        }
        else if (map[i-2][j]== object && map[i-3][j] == rpoint_char ){
            map[i-1][j] = ply->ch;
            map[i-2][j] = moveblock;
            map[i-3][j]= object;
            seeds(1);
            map[i][j]= ' ';
            ply->i = i-1;
            ply->j;
        }
        else if(map[i-2][j]==rpoint_char){
            map[i-1][j]=ply->ch;
            map[i-2][j]=moveblock;
            map[i][j] = ' ';
            ply->i = i-1;
            ply->j = j;
            seeds(1);
        }
        else if(map[i-2][j]==target){
            map[i-2][j]=target;
            map[i][j]=ply->ch;
            map[i-1][j]=moveblock;
        }
        else if(map[i-2][j]==object && map[i-3][j]==target){
            game_over(ply->name);
        }

        else {
            map[i - 1][j] = ply->ch;
            map[i][j] = ' ';
            map[i - 2][j] = moveblock;
            ply->i = i - 1;
            ply->j = j;
        }

    }
    else if(side == right){
        if (map[i][j + 2] == wall || map[i][j + 2] == solidblock || map[i][j+2]==deathblock) {
            return;
        }
        else if(map[i][j+2]==object && map[i][j+3]==' ' ){
            map[i][j+1] = ply->ch;
            map[i][j] = ' ';
            map[i][j+2]= moveblock;
            map[i][j+3] = object;
            ply->i = i;
            ply->j = j+1;
        }
        else if(map[i][j+2] == object && (map[i][j+3] == wall || map[i][j+3] == solidblock || map[i][j+3]==deathblock)){
            return;
        }
        else if (map[i][j+2]==object && map[i][j+3] == rpoint_char ){
            map[i][j+1] = ply->ch;
            map[i][j+2] = moveblock;
            map[i][j+3]= object;
            map[i][j]=' ';
            seeds(1);
            ply->i = i;
            ply->j+1;
        }
        else if(map[i][j+2]==rpoint_char){
            map[i][j+1]=ply->ch;
            map[i][j+2]=moveblock;
            map[i][j] = ' ';
            ply->i = i;
            ply->j = j+1;
            seeds(1);
        }
        else if(map[i][j+2]==target){
            map[i][j+2]=target;
            map[i][j]=ply->ch;
            map[i][j+1]=moveblock;
        }
        else if(map[i][j+2]==object && map[i][j+3]==target){
            game_over(ply->name);
        }
        else {
            map[i][j + 1] = ply->ch;
            map[i][j] = ' ';
            map[i][j + 2] = moveblock;
            ply->i = i;
            ply->j = j + 1;
        }
    } else if(side == down){
        if (map[i + 2][j] == wall || map[i + 2][j] == solidblock || map[i+2][j]== deathblock) {
            return;
        }
        else if(map[i+2][j]==object && map[i+3][j]==' ' ){
            map[i+1][j] = ply->ch;
            map[i][j] = ' ';
            map[i+2][j]= moveblock;
            map[i+3][j] = object;
            ply->i = i+1;
            ply->j = j;
        }
        else if(map[i+2][j] == object && (map[i+3][j] == wall || map[i+3][j] == solidblock || map[i+3][j]==deathblock)){
            return;
        }
        else if (map[i+2][j]==object && map[i+3][j] == rpoint_char ){
            map[i+1][j] = ply->ch;
            map[i+2][j] = moveblock;
            map[i+3][j]= object;
            map[i][j] = ' ';
            seeds(1);
            ply->i = i+1;
            ply->j;
        }
        else if(map[i+2][j]==rpoint_char){
            map[i+1][j]=ply->ch;
            map[i+2][j]=moveblock;
            map[i][j] = ' ';
            ply->i = i+1;
            ply->j = j;
            seeds(1);
        }
        else if(map[i+2][j]==target){
            map[i+2][j]=target;
            map[i][j]=ply->ch;
            map[i+1][j]=moveblock;
        }
        else if(map[i+2][j]==object && map[i+3][j]==target){
            game_over(ply->name);
        }

        else {
            map[i + 1][j] = ply->ch;
            map[i][j] = ' ';
            map[i + 2][j] = moveblock;
            ply->i = i + 1;
            ply->j = j;
        }
    } else if(side == left){
        if (map[i][j - 2] == wall || map[i][j - 2] == solidblock || map[i][j-2]==deathblock) {
            return;
        }
        else if(map[i][j-2]==object && map[i][j-3]==' ' ){
            map[i][j-1] = ply->ch;
            map[i][j] = ' ';
            map[i][j-2]= moveblock;
            map[i][j-3] = object;
            ply->i = i;
            ply->j = j-1;
        }
        else if(map[i][j-2] == object && (map[i][j-3] == wall || map[i][j-3] == solidblock || map[i][j-3]==deathblock)){
            seeds(1);
        }
        else if (map[i][j-2]==object && map[i][j-3] == rpoint_char ){
            map[i][j-1] = ply->ch;
            map[i][j-2] = moveblock;
            map[i][j-3]= object;
            map[i][j] = ' ';
            seeds(1);
            ply->i = i;
            ply->j-1;
        }
        else if(map[i][j-2]==rpoint_char){
            map[i][j-1]=ply->ch;
            map[i][j-2]=moveblock;
            map[i][j] = ' ';
            ply->i = i;
            ply->j = j-1;
            seeds(1);
        }
        else if(map[i][j-2]==target){
            map[i][j-2]=target;
            map[i][j]=ply->ch;
            map[i][j-1]=moveblock;
        }
        else if(map[i][j-2]==object && map[i][j-3]==target){
            game_over(ply->name);
        }

        else {
            map[i][j - 1] = ply->ch;
            map[i][j] = ' ';
            map[i][j - 2] = moveblock;
            ply->i = i;
            ply->j = j - 1;
        }
    }




}

void game_over(char *winner){
    extern struct game_variables *is_in_game;
    extern struct player *player1;
    if(!strcmp(winner,"computer")){
        flag=0;
        system("cls");
        Beep(600,200);
        SetColor(12);
        delay(250);
        printf("Press any key to exit:\n");
        printf("Game over!\n"
               "computer won\n");
        while(!kbhit());
        flag = 0;

    } else if(!strcmp("time",winner)){
        Beep(600,200);
        SetColor(12);
        system("cls");
        delay(250);
        printf("Time up!\n");
        printf("Press any key to exit:\n");
        while(!kbhit());
        flag = 0;

    }
    else{
        system("cls");
        Beep(600,200);
        SetColor(3);
        printf("Well done!\n"
               "%s has won!\n",winner);
        printf("Press any key to exit:\n");
        delay(250);
        while(!kbhit());
        flag = 0;
    }
}

void move(struct player *ply, char inp) {
    char nextpos = EOF;
    int next_i, next_j;
    if (inp == up) {
        next_i = (ply->i) - 1;
        next_j = ply->j;
        nextpos = map[next_i][next_j];
    } else if (inp == right) {
        next_i = (ply->i);
        next_j = (ply->j) + 1;
        nextpos = map[next_i][next_j];
    } else if (inp == down) {
        next_i = (ply->i) + 1;
        next_j = (ply->j);
        nextpos = map[next_i][next_j];
    } else if (inp == left) {
        next_i = (ply->i);
        next_j = (ply->j) - 1;
        nextpos = map[next_i][next_j];
    }
    else if(inp == game_exit){
        flag = 0;
    }
    if (nextpos == EOF)
        return;
    else if (nextpos == ' ') {
        map[next_i][next_j] = ply->ch;
        map[ply->i][ply->j] = ' ';
        ply->i = next_i;
        ply->j = next_j;
        return;
    } else if ((nextpos == wall) || (nextpos == solidblock))
        return;
    else if (nextpos == deathblock) {
        game_over("computer");
    } else if (nextpos == moveblock ) {
        moveBlock(ply, inp);
    } else if(nextpos == rpoint_char){
        map[next_i][next_j] = ply->ch;
        map[ply->i][ply->j] = ' ';
        ply->i = next_i;
        ply->j = next_j;
        (ply->score)= (ply->score) + (rpoint_score);
        seeds(1);
    }
    else if(nextpos == object){
        objects(ply , inp);
    }
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}