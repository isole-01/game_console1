//
// Created by Tr on 6/29/2019.
//
#include "game_console.h"

extern char **map;
extern char up;
extern char right;
extern char down;
extern char left;

char helper(char side, int i, int j) {
    if (side == up)
        return map[i - 1][j];
    if (side == right)
        return map[i][j + 1];
    if (side == down)
        return map[i + 1][j];
    if (side == left)
        return map[i][j - 1];
}

int is_block(char a) {
    extern char solidblock;
    extern char wall;
    extern char deathblock;

    if ((a == solidblock) || (a == wall) || (a == deathblock))
        return 1;
    return 0;
}

char next_move(struct player *ply, char ch) {
    extern int map_len;
    extern int map_wid;


    extern int flag;
    int condition_2 = 1;
    char res;
    int i, j;
    for (i = 0; (condition_2) && (i < map_wid); i++)
        for (j = 0; j < map_len; j++)
            if (map[i][j] == ch) {
                condition_2 = 0;
                break;
            }
    if (condition_2 == 1) {
        printf("next move: target not found");
        return 0;
    }
    condition_2 = rand() % 2;

    int i_distance = i - (ply->i);
    int j_distance = j - (ply->j);
    if ((!i_distance) && (!j_distance)) {
        game_over("computer");
    }
    if (!i_distance) {
        if (j_distance > 0) {
            res = right;
            if (is_block(helper(res, ply->i, ply->j))) {
                if (condition_2) {
                    res = up;
                } else {
                    res = down;
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    if (condition_2) {
                        res = down;
                    } else {
                        res = up;
                    }
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    res = left;
                }
            }
        } else {
            res = left;
            if (is_block(helper(res, ply->i, ply->j))) {
                if (condition_2) {
                    res = up;
                } else {
                    res = down;
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    if (condition_2) {
                        res = down;
                    } else {
                        res = up;
                    }
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    res = right;
                }
            }
        }

    } else if (!j_distance) {
        if (i_distance > 0) {
            res = down;
            if (is_block(helper(res, ply->i, ply->j))) {
                if (condition_2) {
                    res = right;
                } else {
                    res = left;
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    if (condition_2) {
                        res = left;
                    } else {
                        res = right;
                    }
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    res = up;
                }
            }
        } else {
            res = up;
            if (is_block(helper(res, ply->i, ply->j))) {
                if (condition_2) {
                    res = right;
                } else {
                    res = left;
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    if (condition_2) {
                        res = left;
                    } else {
                        res = right;
                    }
                }
                if (is_block(helper(res, ply->i, ply->j))) {
                    res = down;
                }
            }
        }
    }
        /*
        if (i_distance > 0)
            res = down;
        else { res = up;
        }*/
    else {
        if (condition_2) {
            if (i_distance > 0)
                res = down;
            else
                res = up;
        } else {
            if (j_distance > 0)
                res = right;
            else
                res = left;
        }
        if (is_block(helper(res, ply->i, ply->j))) {
            if (condition_2) {
                if (j_distance > 0)
                    res = right;
                else
                    res = left;
            } else {
                if (i_distance > 0)
                    res = down;
                else
                    res = up;
            }
        }
        if (is_block(helper(res, ply->i, ply->j))) {
            if(condition_2){
                if (j_distance > 0)
                    res = left;
                else
                    res = right;
            } else{
                if (i_distance > 0)
                    res = up;
                else
                    res = down;
            }
        }
        if (is_block(helper(res, ply->i, ply->j))){
            if(condition_2){
                if (i_distance > 0)
                    res = up;
                else
                    res = down;
            } else{
                if (j_distance > 0)
                    res = left;
                else
                    res = right;
            }
        }
    }
    return res;
}



