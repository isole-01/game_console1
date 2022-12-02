//
// Created by Tr on 6/10/2019.
//

#include "game_console.h"

struct player *player1;
struct player *opponent;
extern struct game_variables *is_in_game;

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

static int set_variable(char *line);


char **map;

int read_game(char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("*invalid file_name*");
        fclose(fptr);
        return 0;
    }
    is_in_game->solidblock = 0;
    is_in_game->raindb = 0;
    is_in_game->attack = 0;
    is_in_game->rpoint = 0;
    is_in_game->put = 0;
    is_in_game->object = 0;
    is_in_game->target = 0;
    is_in_game->game_time = 0;
    is_in_game->character = 0;
    is_in_game->deathblock = 0;
    is_in_game->left = 0;
    is_in_game->up = 0;
    is_in_game->wall = 0;
    is_in_game->opp = 0;
    is_in_game->moveblock = 0;
    is_in_game->right = 0;
    is_in_game->down = 0;
    is_in_game->game_exit = 0;
    int i = 0;
    char current_line[MAXLEN];
    while (fgets(current_line, MAXLEN, fptr)) {
        current_line[strlen(current_line) - 1] = '\0';
        i++;
        set_variable(current_line);
    }
    fclose(fptr);
    return i;
}


int read_map(char *filename) {
    extern int map_len;
    extern int map_wid;


    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("*invalid file_name*");
        fclose(fptr);
        return 0;
    }
    fscanf(fptr, "%d x %d\n", &map_len, &map_wid);
    map = (char **) malloc(sizeof(char *) * (map_wid));
    char *hoy = NULL;

    char temp[2];
    temp[0] = character;
    temp[1] = '\0';
    char temp2[2];
    temp2[0] = opp[0];
    temp2[1] = '\0';
    int i;
    char *current_line=(char *)malloc(sizeof(char) * (map_len+1));
    /*map[map_wid]=NULL;
    for(i=0;(map[i]!=NULL)&&((map[i])=(char *)malloc(sizeof(char) * (map_len+1)));i++){
        fgets(current_line,map_len+100,fptr);
        fgetc(fptr);
        strcpy(map[i],current_line);
        printf("%s",map[i]);
    }
     */
    for(i=0;(i < map_wid)  ;i++){

        map[i] = (char *) malloc(sizeof(char) * (map_len+10));
        fgets(map[i], MAXLEN, fptr);
        map[i][map_len] = '\0';

        if ((hoy = strstr(map[i], temp))) {
            player1->i = i;
            player1->j = hoy - map[i];
        }
        if ((hoy = strstr(map[i], temp2))) {
            opponent->i = i;
            opponent->j = hoy - map[i];
        }
        //printf("%s",map[i]);

    }
    map[i] = NULL;
    fclose(fptr);
    return i;
}


static int set_variable(char *line) {
    char *var;



    if ((var = strstr(line, "solidblock=")) != NULL) {
        solidblock = var[11];
        is_in_game->solidblock = 1;
    } else if ((var = strstr(line, "deathblock=")) != NULL) {
        deathblock = var[11];
        is_in_game->deathblock = 1;
    } else if ((var = strstr(line, "moveblock=")) != NULL) {
        moveblock = var[10];
        is_in_game->moveblock = 1;
    } else if ((var = strstr(line, "wall=")) != NULL) {
        wall = var[5];
        is_in_game->wall = 1;
    } else if ((var = strstr(line, "up=")) != NULL) {
        up = var[3];
        is_in_game->up = 1;
    } else if ((var = strstr(line, "right=")) != NULL) {
        right = var[6];
        is_in_game->right = 1;
    } else if ((var = strstr(line, "down=")) != NULL) {
        down = var[5];
        is_in_game->down = 1;
    } else if ((var = strstr(line, "Exit=")) != NULL) {
        game_exit = var[5];
        is_in_game->game_exit = 1;
    } else if ((var = strstr(line, "left=")) != NULL) {
        left = var[5];
        is_in_game->left = 1;
    } else if ((var = strstr(line, "character=")) != NULL) {
        player1 = (struct player *) malloc(sizeof(struct player));
        player1->score = 0;
        player1->ch = var[10];
        player1->computer = 0;
        character = var[10];
        is_in_game->character = 1;
    } else if ((var = strstr(line, "time=")) != NULL) {
        game_time = atoi(var + 5);
        is_in_game->game_time = 1;
    } else if ((var = strstr(line, "target=")) != NULL) {
        target = var[7];
        is_in_game->target = 1;
    } else if ((var = strstr(line, "object=")) != NULL) {
        object = var[7];
        is_in_game->object = 1;
    } else if ((var = strstr(line, "opp=")) != NULL) {
        opp[0] = var[4], opp[1] = var[6];
        opponent = (struct player *) malloc(sizeof(struct player));
        opponent->score = 0;
        strcpy(opponent->name, "computer");
        opponent->ch = var[4];
        opponent->computer = 1;
        is_in_game->opp = 1;
    } else if ((var = strstr(line, "put=")) != NULL) {
        put[0] = var[4], put[1] = var[6], put_limit = atoi(var + 8);
        is_in_game->put = 1;
    } else if ((var = strstr(line, "rpoint=")) != NULL) {
        /*rpoint_char = var[7], rpoint_score = atoi(var+9), rpoint_num = atoi(var+11);*/
        rpoint_char = strtok(line, ",")[7];
        rpoint_score = atoi(strtok(NULL, ","));
        rpoint_num = atoi(strtok(NULL, ","));
        is_in_game->rpoint = 1;
    } else if ((var = strstr(line, "attack=")) != NULL) {
        attack = atoi(var + 7);
        is_in_game->attack = 1;
    } else if ((var = strstr(line, "raindb=")) != NULL) {
        raindb = atoi(var + 7);
        is_in_game->raindb = 1;
    }
}
