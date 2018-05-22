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


/*###################################### MANAGE_GAME #######################################*/

#include "map.h"
#include "player.h"
#include "run_game.h"
#include "manage_game.h"

/*##########################################################
 * game : Launch the game with the chosen map
 * Arguments : 
 * path : path map access tree
 * Return int value, returns 0 if success  
 *##########################################################
 */

int game(const char * path){
  game_map map;
  player player[2];
  DIR * mod_dir;
  int ret;

  chdir("./../mod");
  mod_dir = opendir(path);
  struct dirent* arbo;
  chdir(path);
  while((arbo = readdir(mod_dir))){
    system("reset"); /* clear the terminal to display the game map */
    change(); /* change to non-canonical mode */
    
    if(strcmp(arbo->d_name,".") == 0 || strcmp(arbo->d_name,"..") == 0){ /* avoid "." and ".." directories  */
      continue;
    }

    map = construct(arbo->d_name); /* build the map */
    /* Creating players */
    player[0]= creat_player(map,1);
    player[1]= creat_player(map,2);
   
    display_map(map,&player[0],&player[1]); /* dispaly creating map */
    ret=game_manage(map,player); /* Launch game management */
      
    /* de-allocate memory to player and map */
    deallocate_player(&player[0]);
    deallocate_player(&player[1]);  
    //de-allocate memory(map);
    if(ret==2) break;
  }
  restor(); /* change to canonical mode */
  closedir(mod_dir);
  chdir("./.."); /* get to mode directory */
       
  return 0;
}