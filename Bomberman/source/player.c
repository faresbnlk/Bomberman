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




/*###################################### PLAYER #######################################*/
#define FARES 'A'
#define YANI 'N'
#define life_MAX 5
#define BOMBE_MAX 4
#define RAYON_INITIALE 3
#include "player.h"
#define DEFAULT_SPEED 200

/*##########################################################
 * creat_player : create game players
 * Arguments :  
 * - map = structure representing a matrix relative to the map that will be executed
 * - num = player number
 * Return value , player, returns a player structure
 *##########################################################
 */

player creat_player( game_map map,int num){
	player player; /* Create the same player structure for the both players*/

	/* Alloucate  memory , fill the Fields relative to the player and record the times relative to the Fields */
	player.v=malloc(sizeof(speedd));
	player.v->tvsp=malloc(sizeof(struct timeval));
	gettimeofday(player.v->tvsp,NULL);
	player.v->speed=DEFAULT_SPEED;

	player.b=malloc(sizeof(bombe));
	player.b->ttaj = malloc(sizeof(struct timeval));
	gettimeofday(player.b->ttaj,NULL);
	player.b->bomb=BOMBE_MAX;
	player.b->bonus = FALSE;

	player.life=malloc(sizeof(vitality));
	player.life->ttmv=malloc(sizeof(struct timeval));
	gettimeofday(player.life->ttmv,NULL);
	player.life->life=life_MAX;

	player.rayonement=RAYON_INITIALE;

	player.queue=malloc(sizeof(queue));
	player.queue->ffirst=NULL;

	/* We have our two players on the map with their icon */
	if(num == 1){
		player.name = YANI;
		for (player.pos.x=1;player.pos.x<map.height;player.pos.x++){
    		for(player.pos.y=1;player.pos.y<map.width;player.pos.y++){
    			if(map.map[player.pos.x][player.pos.y]==' '){
    				map.map[player.pos.x][player.pos.y]= player.name;
    				return player;
    			}
    		}
  		}
	}else{
		player.name = FARES;
		for (player.pos.x = map.height-1; player.pos.x > 0 ; player.pos.x--){
	    	for(player.pos.y = map.width-1; player.pos.y>0 ; player.pos.y--){
	    		if(map.map[player.pos.x][player.pos.y]==' '){
	    			map.map[player.pos.x][player.pos.y]=player.name;
	    			return player;   		
		    	}
    		}
  		}
	}

	return player;
}

/*##########################################################
 * deallocate_player : deallocate players memory 
 * Arguments :  
 * - player = informations about player structure 
 * Return value : returns a player structure
 *##########################################################
 */

player* deallocate_player(player *player){

	free(player->v->tvsp);
	free(player->v);

	free(player->b->ttaj);
	free(player->b);

	free(player->life->ttmv);
	free(player->life);

	free(player->queue);

	return player;
}
