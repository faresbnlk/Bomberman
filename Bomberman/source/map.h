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
/* IF "_MAP_H_" is not defined */
/* Definition of "_MAP_H_" */
#ifndef _MAP_H_ 									
#define _MAP_H_ 									


/* includes */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>	
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <poll.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/ioctl.h>


/* the constants */
#define SIZE 1024
#define MAX_BOMBE 10
#define TRUE 1
#define FALSE 0



/*##########################################################
 * Position structure: structure translating a coordinate
 * Fields :
 * - x 
 * - y 
 *##########################################################
 */

typedef struct{
  int x;
  int y;
}position;

/*##########################################################
 * Explosion structure: structure reflecting the use of bombs
 * Fields :
 * - flag_expl = If there is a free slot in our bomb array
 * - explose =  position of bombe
 * - rayonement = extended from the blast
 * - ttexpl = time to explose (temps avant explosion)
 *##########################################################
 */

typedef struct {
	bool flag_expl;
	position explose;
	int rayonement;
	struct timeval* ttexpl;
	
}explosion;

/*##########################################################
 * game_map structure  : structure translating a map as a matrix
 * Fields :
 * - height = line number
 * - width =  column number
 * - map = associated map
 * - blast = contains the bombs posed by the players
 *##########################################################
 */

typedef struct{
	int height; 
	int width; 
	char** map;
	explosion blast[MAX_BOMBE];	
}game_map;


/* terminal global variable */
struct termios old_term;
struct winsize win;
position cur; /* cursor position */

							
void get_dimension();
void current_position(game_map map);                /* Move the cursor to the center of the terminal */
int extract_map(int mapdesc, game_map map);			/* Extract the map from a file */
game_map allocate_map(game_map mapalloc);           /* Allocate memory to a matrix */
game_map desallocate_map(game_map mapdesalloc); 	/* Desallocation of matrix memory */
game_map construct(const char* map_file);			/* Build the map in the terminal */
int restor(void);                                   /* Canonical mode */
int change(void);			                        /* Non-canonical mode */


#endif 											    /* End of conditionnel bloc "_MAP_H_" */


