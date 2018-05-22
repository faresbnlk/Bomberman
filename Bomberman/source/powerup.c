/********************************************************************************** #
#                                                                                   #
#                                                      #   # #### #### ####         #
#     Created by : Fares BENLAKEHAL                    #   # #  # #    #            #
#                                                      #   # #### ###  #            #
#                                                      #   # #    #    #            #
#                  2017                                 ###  #    #### ####         #
#                                                                                   #
#                                                                                   #
#                                                                                   # 
#***********************************************************************************/


/*###################################### POWERUP #######################################*/

#include "powerup.h"

/*##########################################################
 * put_on : add bombs puted in the queue
 * Arguments :  
 * - queue = execution queue
 * - bomb_position = bomb position
 * - tmv = save time with each release of poll
 *##########################################################
 */

void put_on(queue *queue, position bomb_position,struct timeval* tmv){
   
    Element *nnew = malloc(sizeof(*nnew));
    if ( nnew == NULL){
        exit(EXIT_FAILURE);
    }
    nnew->pos = bomb_position;
    nnew->tmpb=malloc(sizeof(struct timeval));
    nnew->tmpb->tv_usec=tmv->tv_usec;
    nnew->tmpb->tv_sec=tmv->tv_sec;
    nnew->nextt = NULL;

    if (queue->ffirst != NULL) /* The queue is not empty */
    {
        /* go to the end of the queue */
        Element *elementActuel = queue->ffirst;
        while (elementActuel->nextt != NULL){
            elementActuel = elementActuel->nextt;
        }
        elementActuel->nextt = nnew;
    }else{ /* The queue is empty, this is the first element*/
        queue->ffirst = nnew;
    }
}

/*##########################################################
 * put_out : remove the bombs puted in a queue
 * Arguments :  
 * - queue = execution of the queue
 *##########################################################
 */

void put_out(queue *queue){
    if (queue == NULL){
        exit(EXIT_FAILURE);
    }
    /*  check if there is something to put out */
    if (queue->ffirst != NULL)
    {
        Element *queueElement = queue->ffirst;

        queue->ffirst = queueElement->nextt;
        free(queueElement); 
    }

}

/*##########################################################
 * display_queue : remove the bombs puted in a queue
 * Arguments :  
 * - queue = execution queue
 *##########################################################
 */

void display_queue(queue *ffile){
    if (ffile == NULL){
        exit(EXIT_FAILURE);
    }
    Element *actuel = ffile->ffirst;
    while (actuel != NULL){
        printf("(%d,%d)\n", actuel->pos.x,actuel->pos.y);
        actuel = actuel->nextt;
    }
}
