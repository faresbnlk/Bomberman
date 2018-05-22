/********************************************************************************** #
#                                                                                   #
#                                                      #   # #### #### ####         #
#     Created by : Fares BENLAKEHAL                    #   # #  # #    #            #
#      			                                       #   # #### ###  #            #
#                                                      #   # #    #    #            #
#                  2017                                 ###  #    #### ####         #
#                                           										#
#                                          										    #
#                                                                                   # 
#***********************************************************************************/

/* Si "_DEPLACEMENT_H_" non défini */
/* Définition "_DEPLACEMENT_H_" */
#ifndef _DEPLACEMENT_H_ 									
#define _DEPLACEMENT_H_ 									

#include "map.h"
#include "player.h"

#define KEY1_UP 'A'//"\x1B[A"''
#define KEY1_DOWN 'B'//"\x1B[B"
#define KEY1_RIGHT 'C'//"\x1B[C"
#define KEY1_LEFT 'D'//"\x1B[D"

#define KEY2_UP 'z'//"\x1B[A"''
#define KEY2_DOWN 's'//"\x1B[B"
#define KEY2_RIGHT 'd'//"\x1B[C"
#define KEY2_LEFT 'q'//"\x1B[D"
#define DEFAULT_SPEED 200
#define KEY_ENTRER 'w'
//#define KEY_ESCAPE ''
#define KEY_SPACE ' '

int display_flame(game_map *map,position bomb_position ,player* player1,player* player2,struct timeval* tmv ,int rayonnement);
int clock_game(struct timeval* tmv,speedd* delay);
int remove_flame(game_map *map,struct timeval* tmv);
void move_cursor(int x,int y);
int game_manage(game_map map,player* player1);
int to_up(game_map* map,player* player,struct timeval *tmv);
int down(game_map* map,player* player,struct timeval *tmv);
int right(game_map* map,player* player,struct timeval *tmv);
int left(game_map* map,player* player,struct timeval *tmv);
int display_bomb(game_map* map,player* player,struct timeval *tmv);
int update_map(game_map *map);

#endif