
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

/* If "_MANAGE_GAME_H_ " not defined */
/* Definition of "_MANAGE_GAME_H_ " */
#ifndef _MANAGE_GAME_H_ 							    	
#define _MANAGE_GAME_H_                               

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <poll.h>
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "manage_game.h"                              

int game(const char * path);						/* Launch the game with the chosen map */
#endif