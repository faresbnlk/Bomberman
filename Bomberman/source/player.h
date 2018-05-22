/********************************************************************************** #
#                                                                                   #
#                                                      #   # #### #### ####         #
#     Created by : Fares BENLAKEHAL                    #   # #  # #    #            #
#                                                  #   # #### ###  #            #
#                                                      #   # #    #    #            #
#                  2017                                 ###  #    #### ####         #
#                                                               #
#                                                                 #
#                                                                                   # 
#***********************************************************************************/

/* IF "_player_H_" is not defined */
/* Definition of "_player_H_" */

#ifndef _player_H_ 								                
#define _player_H_                                  

#include "map.h"
#include <sys/time.h>
#include "powerup.h"




/*##########################################################
 * speedd structure : structure relative to the speed of the player
 * Fields :
 * - speed = virtual speed of the playe
 * - tvsp = time interval relative to the speed of the player (interval limiting the displacement of the player)
 *##########################################################
 */

typedef struct {
	int speed;
	struct timeval* tvsp;
}speedd;

/*##########################################################
 * bombe structure  :structure relative to the bombs of the player
 * Fields :
 * - bombe = numbrer of the bombs which contain the player
 * - bonus = if the player has a bonus
 * - ttmv = time interval for adding bomb to the player
 *##########################################################
 */

typedef struct{
  int bomb;
  bool bonus;
  struct timeval* ttaj;
}bombe;

/*##########################################################
 * vitality structure: structure relative to player's life
 * Fields :
 * - life = how many life has the player
 * - ttmv = time during which the player is untouchable
 *##########################################################
 */

typedef struct {
  int life;
  struct timeval* ttmv;
}vitality;

/*##########################################################
 * player structure :
 * Fields :
 * - pos = player position 
 * - life = life structure 
 * - b = bomb structure 
 * - rayonement = extended of the explosion
 * - name = player name
 * - v = speed structure 
 * - queue = structure queue
 *##########################################################
 */

typedef struct{
  position pos;
  vitality* life;
  bombe* b;
  int rayonement;
  char name;
  speedd* v;
  queue* queue;
}player;

int display_map(game_map map,player* player1,player* player2);        /* display the map */
player creat_player( game_map map,int num);                           /* creating players */
player* deallocate_player(player *player);                            /* memory release */

#endif