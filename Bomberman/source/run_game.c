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


/*###################################### RUN_GAME #######################################*/

#include "run_game.h"
#include <sys/time.h>
#include "player.h"
#define TEMP_EXPLOSION 2000
#define TEMP_BLAST 100
#define TEMP_UNTOUCHABLE 1500
#define TEMP_RAJOUT 6000
#define SPEED_MAX 50
#define BLAST_SYMBOL 'y'
#define INBREAKABLE_WALL '0'
#define BREAKABLE_WALL '1'
#define POWER_UP_RADIUS '*'
#define POWER_UP_SPEED '+'
#define POWER_UP_BOMB '#'
/*##########################################################
 * clock: the following clock-functions are used to calculate a time interval
 * Arguments : 
 * - tmv = the time recorded each time the polls are unblocked
 * - delay = value representing the speed of the player 
 * Return value: 1 if successful and -1 for errors
 *##########################################################
 */

int clock_game(struct timeval* tmv, speedd* delay){
	long ms = 0;
		ms = (tmv->tv_sec-delay->tvsp->tv_sec)*1000 + (tmv->tv_usec-delay->tvsp->tv_usec)/1000; /* We calculate a time interval */
		if(ms > delay->speed) return 1; /* If the time interval is respected we return 1 */

	return -1;
}

int clock_powerup(struct timeval* tmv1, struct timeval* tmv2,int TEMP){
	long ms = 0;
		ms = (tmv1->tv_sec-tmv2->tv_sec)*1000+ (tmv1->tv_usec-tmv2->tv_usec)/1000;  /* We calculate a time interval */
		if(ms > TEMP) return 1; /* If the time interval is respected we return 1 */

	return -1;
}

/*##########################################################
 * Fonction remove_life : remove one life of a player
 * Arguments :  
 * - player = informations about palyer
 * - tmv = time interval recorded at poll deblocking
 *##########################################################
 */

void remove_life(player* player,struct timeval* tmv){
	if(clock_powerup(tmv,player->life->ttmv,TEMP_UNTOUCHABLE)>0){
		player->life->life = player->life->life - 1;
		gettimeofday(player->life->ttmv,NULL);
	}
}

/*##########################################################
 * Fonction move_cursor: moving the cursor only in the terminal
 * Arguments :  
 * - x = 
 * - y = 
 *##########################################################
 */

void move_cursor(int x,int y){
    char buf[10];
    int i=sprintf(buf, "\x1b[%d;%dH", x, y);
    write(1, buf, i);
  }

/*##########################################################
 * Fonctions to_up/left/right/down : the player's move function
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 * - player = retrieves position information on the player
 * - tmv = recorded time to unblock polls
 * Return value: -1 in case of errors and we do a simple break otherwise
 *##########################################################
 */

int to_up(game_map* map,player* player,struct timeval* tmv){
	
	if(clock_game(tmv,player->v)>0){
		gettimeofday(player->v->tvsp,NULL);/* orecord a time */
		remove_flame(map,tmv);
		switch(map->map[player->pos.x-1][player->pos.y]){
			case KEY_SPACE:	
						map->map[player->pos.x-1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE; /* replace his previous position with a space */
						player->pos.x = player->pos.x - 1;
						break ;
			case BLAST_SYMBOL:	
						map->map[player->pos.x-1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x - 1;
						remove_life(player,tmv);
						break ;
			case POWER_UP_RADIUS:	
						map->map[player->pos.x-1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x - 1;
						player->rayonement = player->rayonement + 1;  /* increase the radius of his bombs */
						break ;	
			case POWER_UP_SPEED:	
						map->map[player->pos.x-1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x - 1;
						player->v->speed = SPEED_MAX;  /* increase the speed of the player */
						break ;
			case POWER_UP_BOMB:	
						map->map[player->pos.x-1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x - 1;
						player->b->bonus = TRUE; 
						player->b->bomb = player->b->bomb + 1;  /* add bombs for the player */
						break;				
		}
		/* decrease the speed of the player as and when he took a power up*/
		if(player->v->speed < DEFAULT_SPEED){
			player->v->speed += 1;
		}
	}return -1;
}
int down(game_map* map,player* player,struct timeval* tmv){
	if(clock_game(tmv,player->v)>0){
						gettimeofday(player->v->tvsp,NULL);
						remove_flame(map,tmv);
		switch(map->map[player->pos.x+1][player->pos.y]){
			case KEY_SPACE:
						map->map[player->pos.x+1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE; /* replace his previous position with a space */
						player->pos.x = player->pos.x + 1;
						break ;
			case BLAST_SYMBOL:
						map->map[player->pos.x+1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x + 1;
						remove_life(player,tmv);
						break ;
			case POWER_UP_RADIUS:	
						map->map[player->pos.x+1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x + 1;
						player->rayonement = player->rayonement + 1;
						break;
			case POWER_UP_SPEED:	
						map->map[player->pos.x+1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.x = player->pos.x + 1;
						player->v->speed = SPEED_MAX;
						break;
			case POWER_UP_BOMB:	
						map->map[player->pos.x+1][player->pos.y]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;						
						player->pos.x = player->pos.x + 1;
						player->b->bonus = TRUE; 
						player->b->bomb = player->b->bomb + 1; 
						break;
		}
		if(player->v->speed < DEFAULT_SPEED){
			player->v->speed += 1;
		}
	}

	return -1;
}

int right(game_map* map,player* player,struct timeval* tmv){
	if(clock_game(tmv,player->v)>0){
						gettimeofday(player->v->tvsp,NULL);
						remove_flame(map,tmv);
		switch(map->map[player->pos.x][player->pos.y+1]){
			
			case KEY_SPACE:
						map->map[player->pos.x][player->pos.y+1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE; /* replace his previous position with a space */
						player->pos.y = player->pos.y+1;
						break ;
			
			case BLAST_SYMBOL:
						map->map[player->pos.x][player->pos.y+1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						remove_life(player,tmv);
						break ;
			
			case POWER_UP_RADIUS:
						map->map[player->pos.x][player->pos.y+1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y+1;
						player->rayonement = player->rayonement + 1;
						break ;
			
			case POWER_UP_SPEED:
						map->map[player->pos.x][player->pos.y+1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y+1;
						player->v->speed = SPEED_MAX;
						break ;
			
			case POWER_UP_BOMB:
						map->map[player->pos.x][player->pos.y+1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y + 1;
						player->b->bonus = TRUE; 
						player->b->bomb = player->b->bomb + 1; 
						break;
		}
		if(player->v->speed < DEFAULT_SPEED){
			player->v->speed += 1;
		}
	}
	return -1;
}
int left(game_map* map,player* player,struct timeval* tmv){
	if(clock_game(tmv,player->v)>0){
						gettimeofday(player->v->tvsp,NULL);
						remove_flame(map,tmv);
		switch(map->map[player->pos.x][player->pos.y-1]){
			case KEY_SPACE:
						map->map[player->pos.x][player->pos.y-1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE; /* replace his previous position with a space */
						player->pos.y = player->pos.y-1;
						break ;
			case BLAST_SYMBOL:	
						map->map[player->pos.x][player->pos.y-1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y-1;
						
						remove_life(player,tmv);
						break ;
			case POWER_UP_RADIUS:
						map->map[player->pos.x][player->pos.y-1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y-1;
						player->rayonement = player->rayonement + 1;
						break ;
			case POWER_UP_SPEED:
						map->map[player->pos.x][player->pos.y-1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y-1;
						player->v->speed = SPEED_MAX;
						break ;
			case POWER_UP_BOMB:
						map->map[player->pos.x][player->pos.y-1]=map->map[player->pos.x][player->pos.y]; /* move the player*/
						map->map[player->pos.x][player->pos.y]=KEY_SPACE;
						player->pos.y = player->pos.y - 1;
						player->b->bonus = TRUE; 
						player->b->bomb = player->b->bomb + 1; 
						break;
		}
		if(player->v->speed < DEFAULT_SPEED){
			player->v->speed += 1;
		}
	}
	return 1;

}

/*##########################################################
 * Fonctions update_map : put for the player the second virtual map
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 * Return value: 1 if successful
 *##########################################################
 */

int update_map(game_map *map){
	int i,j;
	for(i=0;i<map->height;i++){ /* browse the map with a double loop  */
		for(j=0;j<map->width;j++){
			if(map->map[i][j]==KEY_SPACE){ /* test if there is a space  */
				map->map[i][j]=map->map[i+map->height][j]; 
				map->map[i+map->height][j]=KEY_SPACE; /* put a space in the seconde virtual map */
			}
		}
	}
	return 1;

}

/*##########################################################
 * Fonctions manage_queue : allows to manage the bombs of the player contained in a queue
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 * - player1 = retrieves position information on the player1
 * - player2 = retrieves position information on the player2
 * - tmv = recorded time to unblock polls
 * Return value: -1 in case of errors and we do a simple break otherwise
 *##########################################################
 */

int manage_queue(struct timeval* tmv, game_map *map, player* player1, player* player2){
	int i;
	if(player1->queue->ffirst!=NULL){				
		Element* actuel1=player1->queue->ffirst;
		if(clock_powerup(tmv,actuel1->tmpb,TEMP_EXPLOSION)==1){ /* if the interval relative to the bomb is respected, enter the condition */
			for(i=0;i<MAX_BOMBE;i++){
				if(map->blast[i].flag_expl==FALSE){  /* if a table location is free, we put a bomb */
					map->blast[i].flag_expl=TRUE;
					/* how much will be the blast */
					map->blast[i].rayonement=player1->rayonement;
					/* put the coordinates of the bomb */
					map->blast[i].explose.x =player1->queue->ffirst->pos.x;
					map->blast[i].explose.y =player1->queue->ffirst->pos.y;
					map->blast[i].ttexpl->tv_sec =tmv->tv_sec;
					map->blast[i].ttexpl->tv_usec =tmv->tv_usec;
					break;
				}
			}
			display_flame(map,map->blast[i].explose,player1,player2,tmv,player1->rayonement);
			put_out(player1->queue);
			
		}
	}
	if(player2->queue->ffirst!=NULL){				
		Element* actuel2=player2->queue->ffirst;
		if(clock_powerup(tmv,actuel2->tmpb,TEMP_EXPLOSION)==1){
			for(i=0;i<MAX_BOMBE;i++){
				if(map->blast[i].flag_expl==FALSE){
					map->blast[i].flag_expl=TRUE;
					map->blast[i].rayonement=player2->rayonement;
					map->blast[i].explose.x =player2->queue->ffirst->pos.x;
					map->blast[i].explose.y =player2->queue->ffirst->pos.y;
					map->blast[i].ttexpl->tv_sec =tmv->tv_sec;
					map->blast[i].ttexpl->tv_usec =tmv->tv_usec;
					break;
				}
			}
			display_flame(map,map->blast[i].explose ,player1,player2,tmv,player2->rayonement);
			put_out(player2->queue);
			
		}
	}

	remove_flame(map,tmv);

	return 1;
}

/*##########################################################
 * Fonctions remove_flame : remove the flames from the map
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 * - tmv = recorded time to unblock polls
 * Return value: -1 in case of errors and we do a simple break otherwise
 *##########################################################
 */

int remove_flame(game_map *map,struct timeval* tmv){
	int n,i;

	for (n = 0; n < MAX_BOMBE; n++){
		if(map->blast[n].flag_expl==TRUE && clock_powerup(tmv,map->blast[n].ttexpl,TEMP_BLAST)>0){
			map->blast[n].flag_expl=FALSE;
			/* Path loop of the map at the blast level */
			for (i = -map->blast[n].rayonement ; i <= map->blast[n].rayonement ; i++){
				if(map->blast[n].explose.x + i < 0){
					continue;
				}
				/* loop and put spaces where there were bombs*/
				if(map->map[map->blast[n].explose.x+i][map->blast[n].explose.y]==BLAST_SYMBOL){
					if(i==0){
						map->map[map->blast[n].explose.x+i+map->height][map->blast[n].explose.y]=KEY_SPACE;
					}
					map->map[map->blast[n].explose.x+i][map->blast[n].explose.y]=KEY_SPACE;
					
				}
				if(map->map[map->blast[n].explose.x+i][map->blast[n].explose.y]=='N' || map->map[map->blast[n].explose.x+i][map->blast[n].explose.y]=='A'){
						map->map[map->blast[n].explose.x+i+map->height][map->blast[n].explose.y]=KEY_SPACE;

				}
			}
			/* Path loop of the map at the blast level */
			for (i = -map->blast[n].rayonement ; i <= map->blast[n].rayonement ; i++){
				if(map->blast[n].explose.y + i < 0)
					continue;
				/* loop and put spaces where there were bombs*/
				if(map->map[map->blast[n].explose.x][map->blast[n].explose.y + i] == BLAST_SYMBOL){
					if(i==0){
						map->map[map->blast[n].explose.x+map->height][map->blast[n].explose.y + i] = KEY_SPACE;
					}
					map->map[map->blast[n].explose.x][map->blast[n].explose.y + i] = KEY_SPACE;
				}


			}
		}
	}
	return 1;
}

/*##########################################################
 * display_flame : display the flames
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 * - player1 = retrieves position information on the player1
 * - player2 = retrieves position information on the player2
 * - bomb_position = coordinates of the bomb
 * - rayonement = legth of bomb rayonement
 * Return value: -1 in case of errors and we do a simple break otherwise
 *##########################################################
 */

int display_flame(game_map *map,position bomb_position ,player* player1,player* player2,struct timeval* tmv,int rayonement){
	int i;
	int height=map->height;
	if(map->map[bomb_position.x][bomb_position.y]==player1->name || map->map[bomb_position.x][bomb_position.y]==player2->name){
		if(map->map[bomb_position.x + height][bomb_position.y]==KEY_SPACE || map->map[bomb_position.x + height][bomb_position.y]=='@'){
			map->map[bomb_position.x +height][bomb_position.y]=BLAST_SYMBOL;
		}
	}else{
			map->map[bomb_position.x][bomb_position.y]=BLAST_SYMBOL;
	}

	for(i = 1; i <= rayonement; i++){
		if(map->map[bomb_position.x + i][bomb_position.y] == player1->name || map->map[bomb_position.x][bomb_position.y] == player1->name){
			remove_life(player1,tmv);
			break;
		}else if(map->map[bomb_position.x + i][bomb_position.y] == player2->name || map->map[bomb_position.x][bomb_position.y] == player2->name){
			remove_life(player2,tmv);
			break;
		}
		switch(map->map[bomb_position.x + i][bomb_position.y]){
			case KEY_SPACE: map->map[bomb_position.x + i][bomb_position.y] = BLAST_SYMBOL;continue;
			case BREAKABLE_WALL:map->map[bomb_position.x + i][bomb_position.y] = BLAST_SYMBOL;break;
			case BLAST_SYMBOL:map->map[bomb_position.x + height + i][bomb_position.y] = BLAST_SYMBOL;continue;
			case '@':break;
			case INBREAKABLE_WALL:break;
			case POWER_UP_SPEED:map->map[bomb_position.x + i][bomb_position.y] = BLAST_SYMBOL;break;
			case POWER_UP_RADIUS:map->map[bomb_position.x + i][bomb_position.y] = BLAST_SYMBOL;break;
			case POWER_UP_BOMB:map->map[bomb_position.x + i][bomb_position.y] = BLAST_SYMBOL;break;
			default: map->map[bomb_position.x + i][bomb_position.y] = map->map[bomb_position.x + i][bomb_position.y]-1;break;
		}
		break;
	}

		for(i = 1; i <= rayonement; i++){
			if(bomb_position.x-i < 0) break;
			if(map->map[bomb_position.x - i][bomb_position.y] == player1->name || map->map[bomb_position.x][bomb_position.y] == player1->name){
			remove_life(player1,tmv);
			break;
			}else if(map->map[bomb_position.x - i][bomb_position.y] == player2->name || map->map[bomb_position.x][bomb_position.y] == player2->name){
				remove_life(player2,tmv);
				break;
			}
			switch(map->map[bomb_position.x - i][bomb_position.y]){
				case KEY_SPACE: map->map[bomb_position.x - i][bomb_position.y] = BLAST_SYMBOL;continue;
				case BREAKABLE_WALL:map->map[bomb_position.x - i][bomb_position.y] = BLAST_SYMBOL;break;
				case BLAST_SYMBOL:map->map[bomb_position.x + height - i][bomb_position.y] = BLAST_SYMBOL;continue;
				case '@':break;
				case INBREAKABLE_WALL:break;
				case POWER_UP_SPEED:map->map[bomb_position.x - i][bomb_position.y] = BLAST_SYMBOL;break;
				case POWER_UP_RADIUS:map->map[bomb_position.x - i][bomb_position.y] = BLAST_SYMBOL;break;
				case POWER_UP_BOMB:map->map[bomb_position.x - i][bomb_position.y] = BLAST_SYMBOL;break;
				default: map->map[bomb_position.x - i][bomb_position.y] = map->map[bomb_position.x - i][bomb_position.y] -1;break;
			}
			break;
		}
	
	
	for(i = 1; i <= rayonement; i++){
		if(map->map[bomb_position.x][bomb_position.y + i] == player1->name || map->map[bomb_position.x][bomb_position.y] == player1->name){
			remove_life(player1,tmv);
			break;
		}else if(map->map[bomb_position.x][bomb_position.y + i] == player2->name || map->map[bomb_position.x][bomb_position.y] == player2->name){
			remove_life(player2,tmv);
			break;
		}
		switch(map->map[bomb_position.x][bomb_position.y + i]){
			case KEY_SPACE: map->map[bomb_position.x][bomb_position.y + i] = BLAST_SYMBOL;continue;
			case BREAKABLE_WALL:map->map[bomb_position.x][bomb_position.y + i] = BLAST_SYMBOL;break;
			case BLAST_SYMBOL:map->map[bomb_position.x + height][bomb_position.y + i]=BLAST_SYMBOL;continue;
			case '@':break;
			case INBREAKABLE_WALL:break;
			case POWER_UP_SPEED:map->map[bomb_position.x][bomb_position.y + i] = BLAST_SYMBOL;break;
			case POWER_UP_RADIUS:map->map[bomb_position.x][bomb_position.y + i] = BLAST_SYMBOL;break;
			case POWER_UP_BOMB:map->map[bomb_position.x][bomb_position.y + i] = BLAST_SYMBOL;break;
			default: map->map[bomb_position.x][bomb_position.y + i] = map->map[bomb_position.x][bomb_position.y + i]-1;break;
		}
		break;
	}

	for(i = 1; i <= rayonement; i++){
		if(bomb_position.y-i < 0) break;
		if(map->map[bomb_position.x][bomb_position.y - i] == player1->name || map->map[bomb_position.x][bomb_position.y] == player1->name){
			remove_life(player1,tmv);
			
			break;
		}else if(map->map[bomb_position.x][bomb_position.y - i] == player2->name || map->map[bomb_position.x][bomb_position.y] == player2->name){
			remove_life(player2,tmv);
			
			break;
		}
		switch(map->map[bomb_position.x][bomb_position.y - i]){
			case KEY_SPACE: map->map[bomb_position.x][bomb_position.y - i] = BLAST_SYMBOL;continue;
			case BREAKABLE_WALL:map->map[bomb_position.x][bomb_position.y - i] = BLAST_SYMBOL;break;
			case BLAST_SYMBOL:map->map[bomb_position.x+height][bomb_position.y - i] = BLAST_SYMBOL;continue;
			case '@':break;
			case INBREAKABLE_WALL:break;
			case POWER_UP_SPEED:map->map[bomb_position.x][bomb_position.y - i] = BLAST_SYMBOL;break;
			case POWER_UP_RADIUS:map->map[bomb_position.x][bomb_position.y - i] = BLAST_SYMBOL;break;
			case POWER_UP_BOMB:map->map[bomb_position.x][bomb_position.y - i] = BLAST_SYMBOL;break;
			default: map->map[bomb_position.x][bomb_position.y - i] = map->map[bomb_position.x][bomb_position.y - i] -1;break;
		}
		break;
	}
return 0;
}

/*##########################################################
 * Fonction display_bomb : display the bomb on the map
 * Arguments :  
 * - player = informations about the player
 * - map = map matrix
 * - tmv = recorded time each time poll unblocks 
 *Return value: TRUE if game ended and FALSE otherwise
 *##########################################################
 */

int display_bomb(game_map* map,player* player,struct timeval* tmv){
	if(player->b->bomb <= 0){
		return -1;//can not put a bomb
	}
	map->map[player->pos.x+map->height][player->pos.y]='@';
	player->b->bomb=player->b->bomb-1;
	put_on(player->queue,player->pos,tmv);
	return 1;
}

/*##########################################################
 * Fonction add_bomb : add bombs to the player after a defined time
 * Arguments :  
 * - player1 = informations about the player1
 * - player2 = informations about the player2
 * - tmv = recorded time each time poll unblocks 
 *Return value: TRUE if game ended and FALSE otherwise
 *##########################################################
 */

void add_bomb(player* player1, player* player2,struct timeval* tmv){

	if( clock_powerup(tmv,player1->b->ttaj,TEMP_RAJOUT)>0 ){
			if(player1->b->bonus == TRUE && player1->b->bomb< 5){
				player1->b->bomb = player1->b->bomb + 1;	
				player1->b->ttaj->tv_sec=tmv->tv_sec;
				player1->b->ttaj->tv_usec=tmv->tv_usec;
			}else if( player1->b->bomb< 3 ){
				player1->b->bomb = player1->b->bomb + 1;	
				player1->b->ttaj->tv_sec=tmv->tv_sec;
				player1->b->ttaj->tv_usec=tmv->tv_usec;			
			}
			
		}

		if( clock_powerup(tmv,player2->b->ttaj,TEMP_RAJOUT)>0 ){
			if(player2->b->bonus == TRUE && player2->b->bomb< 5){
				player2->b->bomb = player2->b->bomb + 1;	
				player2->b->ttaj->tv_sec=tmv->tv_sec;
				player2->b->ttaj->tv_usec=tmv->tv_usec;
			}else if( player2->b->bomb< 3 ){
				player2->b->bomb = player2->b->bomb + 1;	
				player2->b->ttaj->tv_sec=tmv->tv_sec;
				player2->b->ttaj->tv_usec=tmv->tv_usec;			
			}
			
		}

}

/*##########################################################
 * Fonction game_over : function that ends the game
 * Arguments :  
 * - player1 = informations about the player1
 * - player2 = informations about the player2 
 *Return value: TRUE if game ended and FALSE otherwise
 *##########################################################
 */

bool game_over(player* player1,player* player2){
	if(player1->life->life==0){
		write(1,"\n\t\r player 2 Won",18);
		return TRUE;
	}else if(player2->life->life<=0){
		write(1,"\n\t\r player 1 A Won",18);
		return TRUE;
	}
	return FALSE;
}



/*##########################################################
 * Fonction game_manage : function that moves players on the map
 * Arguments :  
 * - map_queue = queue that contain the map
 * Return value: 0 if successful and -1 for errors
 *##########################################################
 */

int game_manage(game_map map,player player[]){
	char c[10]={0};
	struct pollfd fds[1];
	int timeout=100;
	struct timeval tmv;
	nfds_t nfds=1;
	fds[0].fd=0;
	fds[0].events=POLLIN;
	
	while(1){
		update_map(&map);
		display_map(map,&player[0],&player[1]);		
		int p=poll(fds,nfds,timeout);
		gettimeofday(&tmv,NULL);

		if(p > 0){
			if(fds[0].revents & POLLIN){
				memset(c,0,10);
				read(STDIN_FILENO, c, 4);
				if(strcmp(c,"\x1B") == 0)return -1;
					switch(c[0]){
							case '\x1b' :switch(c[2]){
										case KEY1_UP: to_up(&map,&player[0],&tmv);break;
										case KEY1_RIGHT: right(&map,&player[0],&tmv);break;
										case KEY1_DOWN: down(&map,&player[0],&tmv);break;
										case KEY1_LEFT: left(&map,&player[0],&tmv);break;
										case '\0':return 2;
										default : continue;
										}
										break;


							case KEY2_UP: to_up(&map,&player[1],&tmv);break;
							case KEY2_DOWN: down(&map,&player[1],&tmv);break;
							case KEY2_LEFT: left(&map,&player[1],&tmv);break;
							case KEY2_RIGHT: right(&map,&player[1],&tmv);break;
							case KEY_SPACE: display_bomb(&map,&player[0],&tmv);break;	
							case KEY_ENTRER: display_bomb(&map,&player[1],&tmv);break;
							default : continue;
						}

			}
		}else if(p < 0){
			return -1;
		}

			manage_queue(&tmv,&map,&player[0],&player[1]);
			add_bomb(&player[0], &player[1],&tmv);
			if(game_over(&player[0], &player[1])==TRUE){
						display_map(map,&player[0],&player[1]);		
				sleep(2);
				return 3;
			}
	}
	return 1;
}	
