#********************************************************************************** #
#                                                                                   #
#                                                      #   # #### #### ####         #
#     Created by : Fares BENLAKEHAL                    #   # #  # #    #            #
#      			                                       #   # #### ###  #            #
#                                                      #   # #    #    #            #
#                  2017                                 ###  #    #### ####         #
#                                           										#
#                                          										    #
#                                                                                   # 
#***********************************************************************************#

EXEC = bomberman
SOURCES = bomberman.c map.c player.c run_game.c powerup.c manage_game.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -g -Werror -std=gnu99
 
.PHONY: default clean
 
default: $(EXEC)
 
manage_game.o: manage_game.c manage_game.h
run_game.o: run_game.c run_game.h
map.o: map.c map.h
powerup.o:powerup.c powerup.h
player.o: player.c player.h
%.o: %.c
	$(CC) $< $(CFLAGS) -o $@ -c 
 
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^
 
clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~