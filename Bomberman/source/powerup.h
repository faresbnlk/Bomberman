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
/* if "_POWERUP_H_" not defined */
/* Definition of "_POWERUP_H_" */


#ifndef _POWERUP_H_ 									
#define _POWERUP_H_ 									

#include "map.h"

#define EMPTY (queue_game(NULL))

/*##########################################################
 * Element Structure : structure of an element
 * Fields :
 * - pos : position
 * - tmpb = time saves to the put of the bomb
 * - nextt =  nextt element in the queue
 *##########################################################
 */

typedef struct Element_{
	position pos;
	struct timeval* tmpb;
	struct Element_ *nextt;
}Element;

/*##########################################################
 * queue structure 
 * Fields :
 * - ffirst : ffirst element of the queue
 *##########################################################
 */

typedef struct queue_ {
	Element *ffirst;
}queue;


void put_on(queue *queue, position bomb_position,struct timeval *tmv); 						/* put on the bombs in a queue */
void put_out(queue *queue);                           										/* put out the bombs */
void display_queue(queue *ffile);                   									    /* display queue */

#endif