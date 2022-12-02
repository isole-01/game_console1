
#include "game_console.h"

#define default '~'


//map stuff
char solidblock = default;
char deathblock = default;
char moveblock = default;
char wall = default;
char up = default;
char right = default;
char down = default;
char left = default;
char character = default;
char target = default;
char object = default;
int game_time = 60;
char opp[] = "~~";
char put[] = "~~";
int put_limit = 5;
char rpoint_char = default;
int rpoint_score = 5;
int rpoint_num = 10;
int attack = 1;
int raindb = 10;
int map_len = 50;
int map_wid = 50;
char game_exit = default;
int flag = 1;
clock_t beginning;

struct rain_d **arr;
struct game_variables *is_in_game;
extern struct player *player1;
extern struct player *opponent;
struct bullet *shot;


extern char **map;


void move(struct player *ply, char side);

int seeds(int n);

void print(void);

void print2();

void stuff(struct player *ply, char side, char prev_side);

void deathblock_rain();


int random(int lower, int upper) {
    int res;
    int i;
    return (rand() % (upper - lower + 1)) + lower;
}

void hidedcursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize=100;
    info.bVisible=FALSE;
    SetConsoleCursorInfo(consoleHandle,&info);
}

int main() {
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
    extern char **map;
    extern char game_exit;
    hidedcursor();
    srand(time(NULL));
    is_in_game = (struct game_variables *) malloc(sizeof(struct game_variables));
    char game_file_name[20];
    char map_file_name[20];
    SetColor(3);
    printf("Enter game file name:\n");
    scanf("%s", game_file_name);
    printf("Enter map file name:\n");
    scanf("%s", map_file_name);
    read_game(game_file_name);
    read_map(map_file_name);
    system("cls");
    printf("Choose speed:\n"
           "1. slow\n"
           "2. fast\n"
           "Input: ");

    int speed = 0;
    scanf("%d", &speed);
    system("cls");
    printf("1. easy\n"
           "2. normal\n"
           "3. hard\n"
           "Input: ");
    int dif;
    scanf("%d", &dif);
    printf("enter your name please: ");
    scanf("%s" , player1->name);


    if (is_in_game->attack) {
        shot = (struct bullet *) malloc(sizeof(struct bullet));
        shot->life_time = attack;
        shot->shape = '+';
    }
    if (is_in_game->raindb) {
        arr = (struct rain_d **) malloc(sizeof(struct rain_d *) * raindb);
        int i = 0;

        for (i; i < raindb; i++) {
            arr[i] = (struct rain_d *) malloc(sizeof(struct rain_d));
            arr[i]->i = 2;
            arr[i]->j = random(1, map_len - 2);

        }
    }
    int k=1;
    if (is_in_game->rpoint)
        seeds(rpoint_num);

    char action = 'g';
    char prev_action = 'g';
    int counter;

    beginning = clock();
    clock_t temp_beginning = beginning;
    game_time *= 1000;

    while (((clock() - beginning) < game_time) && (flag)) {
        if (speed == 2) {
            if (kbhit()) {
                Beep(500, 100);
                action = getch();

                if (action == up || action == right || action == left || action == down) {
                    move(player1, action);
                    if (is_in_game->opp) {
                        if(dif == 1){
                            if(k%2 == 0){
                                move(opponent, next_move(opponent, opp[1]));
                            }
                            k++;
                        }

                        else if(dif == 2) {
                            move(opponent, next_move(opponent, opp[1]));
                        }
                        if(dif == 3){
                            move(opponent, next_move(opponent, opp[1]));
                            move(opponent, next_move(opponent, opp[1]));
                        }
                    }
                    if (is_in_game->raindb)
                        deathblock_rain();

                } else {
                    stuff(player1, action, prev_action);
                    ///move(player1 , prev_action);
                    if (is_in_game->opp) {
                        if (dif == 1) {
                            if (k % 2 == 0) {
                                move(opponent, next_move(opponent, opp[1]));
                            }
                            k++;
                        } else if (dif == 2) {
                            move(opponent, next_move(opponent, opp[1]));
                        }
                        if (dif == 3) {
                            move(opponent, next_move(opponent, opp[1]));
                            move(opponent, next_move(opponent, opp[1]));
                        }
                    }
                    if (is_in_game->raindb)
                        deathblock_rain();
                    action = prev_action;


                }
            } else if (clock() - temp_beginning > 200) {
                system("cls");
                move(player1, action);
                if (is_in_game->opp){
                    if(dif == 1){
                        if(k%2 == 0){
                            move(opponent, next_move(opponent, opp[1]));
                        }
                        k++;
                    }

                    else if(dif == 2) {
                        move(opponent, next_move(opponent, opp[1]));
                    }
                    if(dif == 3){
                        move(opponent, next_move(opponent, opp[1]));
                        move(opponent, next_move(opponent, opp[1]));
                    }
                }

                if (is_in_game->raindb)
                    deathblock_rain();
                print();
                temp_beginning = clock();
                prev_action = action;
            }
        } else if (speed == 1) {
            if ((clock() - temp_beginning) > 200) {
                if (!kbhit()) {
                    system("cls");
                    move(player1, action);
                    if (is_in_game->opp){
                        if(dif == 1){
                            if(k%2 == 0){
                                move(opponent, next_move(opponent, opp[1]));
                            }
                            k++;
                        }

                        else if(dif == 2) {
                            move(opponent, next_move(opponent, opp[1]));
                        }
                        if(dif == 3){
                            move(opponent, next_move(opponent, opp[1]));
                            move(opponent, next_move(opponent, opp[1]));
                        }
                    }

                    if (is_in_game->raindb)
                        deathblock_rain();
                    print();
                    temp_beginning = clock();
                    prev_action = action;
                } else {
                    Beep(500, 100);
                    action = getch();

                    if (action == up || action == right || action == left || action == down) {
                        move(player1, action);
                        if (is_in_game->opp){
                            if(dif == 1){
                                if(k%2 == 0){
                                    move(opponent, next_move(opponent, opp[1]));
                                }
                                k++;
                            }

                            else if(dif == 2) {
                                move(opponent, next_move(opponent, opp[1]));
                            }
                            if(dif == 3){
                                move(opponent, next_move(opponent, opp[1]));
                                move(opponent, next_move(opponent, opp[1]));
                            }
                        }

                        if (is_in_game->raindb)
                            deathblock_rain();

                    } else
                        stuff(player1, action, prev_action);
                    ///move(player1 , prev_action);
                    if (is_in_game->opp){
                        if(dif == 1){
                            if(k%2 == 0){
                                move(opponent, next_move(opponent, opp[1]));
                            }
                            k++;
                        }

                        else if(dif == 2) {
                            move(opponent, next_move(opponent, opp[1]));
                        }
                        if(dif == 3){
                            move(opponent, next_move(opponent, opp[1]));
                            move(opponent, next_move(opponent, opp[1]));
                        }
                    }

                    if (is_in_game->raindb)
                        deathblock_rain();
                    action = prev_action;
                }


            }


        }
    }
    game_over("time");
    return 0;

}

int seeds(int n) {
    int s, seed_i, seed_j;
    for (s = 0; s < n;) {
        seed_i = random(2, map_wid-2);
        seed_j = random(2, map_len-2);
        if (map[seed_i][seed_j] == ' ') {
            map[seed_i][seed_j] = rpoint_char;
            s++;
        } else;
    }
}


void stuff(struct player *ply, char side, char prev_side) {
    int attack2;
    if (side == put[0] && put_limit > 0) {
        if (prev_side == up) {
            move(player1, prev_side);
            map[ply->i + 1][ply->j] = put[1];
            put_limit -= 1;
        } else if (prev_side == right) {
            move(player1, prev_side);
            map[ply->i][ply->j - 1] = put[1];
            put_limit -= 1;

        } else if (prev_side == left) {
            move(player1, prev_side);
            map[ply->i][ply->j + 1] = put[1];
            put_limit -= 1;

        } else if (prev_side == down) {
            move(player1, prev_side);
            map[ply->i - 1][ply->j] = put[1];
            put_limit -= 1;
        }
    } else {
        if ((side) == 75) {
            shot->i = ply->i;
            shot->j = ply->j - 1;
            int z;
            for (z = 0; z < attack; z++) {
                if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                    map[shot->i][shot->j] = ' ';
                shot->j = shot->j - 1;
            }
        } else if ((side) == 80) {
            shot->i = ply->i + 1;
            shot->j = ply->j;
            int z;
            if (map_wid - shot->i < attack) {
                attack2 = map_wid - shot->i;
                for (z = 0; z < attack2; z++) {
                    if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                        map[shot->i][shot->j] = ' ';
                    shot->i = shot->i + 1;
                }
            } else

                for (z = 0; z < attack; z++) {
                    if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                        map[shot->i][shot->j] = ' ';
                    shot->i = shot->i + 1;

                }
        } else if ((side) == 77) {
            shot->i = ply->i;
            shot->j = ply->j + 1;
            int z;
            for (z = 0; z < attack; z++) {
                if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                    map[shot->i][shot->j] = ' ';
                shot->j = shot->j + 1;

            }
        } else if ((side) == 72) {
            shot->i = ply->i - 1;
            shot->j = ply->j;
            int z;
            if (shot->i < attack) {
                attack2 = shot->i;
                for (z = 0; z < attack2; z++) {
                    if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                        map[shot->i][shot->j] = ' ';
                    shot->i = shot->i - 1;
                }

            } else

                for (z = 0; z < attack; z++) {
                    if (map[shot->i][shot->j] == deathblock || map[shot->i][shot->j] == opp[0])
                        map[shot->i][shot->j] = ' ';
                    shot->i = shot->i - 1;
                }
        }

    }

}


void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        //Mask out all but the background attribute, and add in the forgournd     color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void print(void) {
    int i, j;
    SetColor(14);
    printf("\nRemaining Time: %ld\n", (game_time - (clock() - beginning)) / 1000);
    printf("\n%s score: %d\n",player1->name , player1->score);
    for (i = 0; i < map_wid; i++) {
        for (j = 0; j < map_len; j++) {
            if (map[i][j] == ' ') {
                printf(" ");
            }
            if (is_in_game->wall) {
                if (map[i][j] == wall) {
                    SetColor(4);
                    printf("%c", wall);
                }
            }
            if (is_in_game->character) {
                if (map[i][j] == character) {
                    SetColor(3);
                    printf("%c", map[i][j]);
                }
            }
            if (is_in_game->solidblock) {
                if (map[i][j] == solidblock) {
                    SetColor(4);
                    printf("%c", solidblock);
                }
            }
            if (is_in_game->moveblock) {
                if (map[i][j] == moveblock) {
                    SetColor(15);
                    printf("%c", moveblock);
                }
            }
            if (is_in_game->deathblock) {
                if (map[i][j] == deathblock) {
                    SetColor(7);
                    printf("%c", deathblock);
                }
            }
            if (is_in_game->opp) {
                if (map[i][j] == (opponent->ch)) {
                    SetColor(5);
                    printf("%c", opponent->ch);
                }
            }
            if (is_in_game->rpoint) {
                if (map[i][j] == rpoint_char) {
                    SetColor(14);
                    printf("%c", rpoint_char);

                }
            }
            if (is_in_game->target) {
                if (map[i][j] == target) {
                    SetColor(10);
                    printf("%c", target);
                }
            }
            if (is_in_game->object) {
                if (map[i][j] == object) {
                    SetColor(15);
                    printf("%c", object);
                }
            }
        }
        printf("\n");
    }
}

void print2() {
    int i;
    for (i = 0; map[i] != NULL; i++) {
        printf("%s", map[i]);
        printf("\n");
    }
}

void deathblock_rain() {
    int i;
    int p;
    for (i = 0; i < raindb; i++) {
        if (arr[i]->i + 1 >= map_wid) {

            map[arr[i]->i - 1][arr[i]->j] = ' ';
            arr[i]->i = 2;
            arr[i]->j = random(1, map_len - 3);
        } else if (map[(arr[i]->i)][arr[i]->j] == solidblock) {
            map[arr[i]->i - 1][arr[i]->j] = ' ';
            arr[i]->i = 2;
            arr[i]->j = random(1, map_len - 3);
        } else if (map[(arr[i]->i)][arr[i]->j] == target || map[(arr[i]->i)][arr[i]->j] == object) {
            map[arr[i]->i - 1][arr[i]->j] = ' ';
            arr[i]->i = 2;
            arr[i]->j = random(1, map_len - 3);
        } else if (map[arr[i]->i][arr[i]->j] == character)
            game_over("computer");
        else {
            map[arr[i]->i - 1][arr[i]->j] = ' ';
            map[arr[i]->i][arr[i]->j] = deathblock;
            arr[i]->i = arr[i]->i + 1;
        }
    }
}

