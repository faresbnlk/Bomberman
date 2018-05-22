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

/*####################################  BOMBERMAN  ###################################*/

#include "manage_game.h"

#define BUF_MINIMUM 256
#define BUFSIZE 1024

ssize_t all_write(int fdesc, const char* buff, size_t towrite);
int file_content(char mode[]);
void char_get();
void mode_menu_2 (int mode,const char* path);
void mode_menu_1();
void menu();

/*###################################################################################
 * all_write : rewrite all the contents of a file
 * Arguments : 
 * fdesc : the file descriptor to rewrite
 * buff : buffer to rewrite the fdesc file
 * towrite : buffer relative size
 * Return value size_t, returns the size of what was read and -1 if an error occurred
 *###################################################################################
 */

ssize_t all_write(int fdesc, const char* buff, size_t towrite){
  int nwrite, length = 0;
  
  while(length < towrite){ /* read as long as there are things to read in the file */
    nwrite = write(fdesc, buff + length, towrite - length);  /* write in the descriptor fdesc the contents of the buff buffer */             
    if(nwrite == -1)return -1;
    length += nwrite; /* increment length as we go along with everything written in nwrite  */
  }
  return length;
}

/*##########################################################
 * file_content : take the contents of a file
 * Arguments : 
 * file : chosen file
 * Return value int, returns 0 on success and -1 on error
 *##########################################################
 */

int file_content(char file[]){
  int fdesc;
  ssize_t nread;
  char buff[BUFSIZE];
  
  fdesc = open(file, O_RDONLY); /* Open the file in a fdesc descriptor */
  if(fdesc == -1){
    perror(file); 
    return -1;
  }
  while((nread = read(fdesc, buff,sizeof(buff)))){  /* Loop as long as there are things to read */     
    if(all_write(STDOUT_FILENO, buff, nread) == -1){perror(file); return -1;} /* call the function all_write */     
  }

  close(fdesc); /* Close the file descriptor */ 
  return 0;
}

/*##############################################################
 * Fonction char_get : retrieve information from standard input
 *##############################################################
 */

void char_get(){
  char buff[BUF_MINIMUM];
  write(STDOUT_FILENO, "Press any Key to Exit : ", 23); 
  read(STDIN_FILENO, buff, BUF_MINIMUM); /* read what entered on the keyboard */
}

/*###################################################################
 * mode_menu_2 : display the menu interface for each modes
 * Arguments : 
 * mode : chosen game mode
 *###################################################################
 */

void mode_menu_2 (int mode, const char * path){
  int choice, nread;
  char buff[BUF_MINIMUM];

  do{
    system("clear"); /*clear the terminal to display the mode 2 menu */
    write(STDOUT_FILENO, "\n\n", 2);
    switch(mode){
        case 1: write(STDOUT_FILENO, "#############################[ EASY MODE ]#############################\n\n\n\n\t\t\t\t", 79); break;
        case 2: write(STDOUT_FILENO, "#############################[ MEDDIUM MODE ]#############################\n\n\n\n\t\t\t\t", 82); break;
        case 3:write(STDOUT_FILENO, "##############################[ MODE advenced ]#############################n\n\n\n\t\t\t\t", 85); break;
        default : exit(EXIT_FAILURE);                 
    }
    /* display the menu mode 2 interface */
    write(STDOUT_FILENO, "1- Play\n\n\t\t\t\t", 13);
    write(STDOUT_FILENO, "2- Select Mode\n\n\t\t\t\t", 20);
    write(STDOUT_FILENO, "Put your choice here : ", 23);
   
    nread = read(STDIN_FILENO, buff, BUF_MINIMUM); /* read what is entered on the keyboard */
    buff[nread] = 0; /* end the buff with a / 0 */
    choice = atoi(buff); /* convert buff contenent to int */

    switch(choice){
        /* redirect to different choices */
        case 1: game(path); /* redirect the management of the game in all the maps of the chosen mod */
        case 2: break;
        default : write(STDOUT_FILENO, "Wrong puts ! \n\n",14);
    }
  }while(choice != 2);
}

/*##########################################################
 * mode_menu_1 : displays the menu interface for modes
 *##########################################################
 */

void mode_menu_1(){
  int choice, nread;
  char buff[BUF_MINIMUM];

  do{
    system("clear"); /* Clear the terminal to display the mode 1 menu */
    write(STDOUT_FILENO,"\n\n",2);
    /* display the menu mode interface 1 */
    write(STDOUT_FILENO, "##############################[ M  O  D  E  S ]##############################\n\n\n\n\t\t\t\t", 85);
    write(STDOUT_FILENO, "1- Easy\n\n\t\t\t\t", 13);
    write(STDOUT_FILENO, "2- medium \n\n\t\t\t\t", 16);
    write(STDOUT_FILENO, "3- advenced\n\n\t\t\t\t", 17);
    write(STDOUT_FILENO, "4- Main Menu\n\n\t\t\t\t", 19);
    write(STDOUT_FILENO, "Put your choice here : ", 22);
    
    nread = read(STDIN_FILENO, buff, BUF_MINIMUM); /* read what is entered on the keyboard */
    buff[nread] = 0; /* end the buff with a / 0 */
    choice = atoi(buff); /* convert buff contenent to int */

    switch(choice){
        /* redirect to different choices */
        case 1: mode_menu_2(1, "./easy"); break; /* open the menu related to the easy mode */
        case 2: mode_menu_2(2, "./medium"); break; /* open the menu related to the nameal mode */
        case 3: mode_menu_2(3, "./advenced"); break; /* open the menu related to the advenced mode */
        case 4: break;
        default : write(1,"Wrong puts ! \n\n",14); 
                  system("pause");
    }
    system("clear");
  }while(choice != 4);
}

/*##########################################################
 * menu : displays the menu interface
 *##########################################################
 */

void menu(){
  int choice, nread;
  char buff[BUF_MINIMUM];

  do{
    system("clear"); /* clear the terminal to display the menu */
    write(STDOUT_FILENO, "\n\n", 2);
    /* displays the menu interface */
    write(STDOUT_FILENO, "#############################[ Main Menu ]#############################\n\n\n\n\t\t\t\t", 80);
    write(STDOUT_FILENO, "1- Start \n\n\t\t\t\t", 16);
    write(STDOUT_FILENO, "2- Select mode \n\n\t\t\t\t", 22);
    write(STDOUT_FILENO, "3- Multiplayers\n\n\t\t\t\t", 22);
    write(STDOUT_FILENO, "4- About\n\n\t\t\t\t", 14);
    write(STDOUT_FILENO, "5- Exit\n\n\t\t\t\t", 13);
    write(STDOUT_FILENO, "Put your choice here : ", 22);
    
    nread = read(STDIN_FILENO, buff, BUF_MINIMUM); /* read what is entered on the keyboard */
    buff[nread] = 0; /* end the buff with a / 0 */
    choice = atoi(buff); /* convert buff contenent to int */

    switch(choice){ /* make a switch case on the user's choice */
      case 1: game("./all_maps");break; /* redirect game management in all maps */
      case 2: mode_menu_1(); break; /* redirect to the modes menu */
      case 3: write(STDOUT_FILENO, "\n\n\n\n\n\n\n\nOption not available for the moment or connection failed ... try later\n\n\n\n\t\t\t\t", 85);// network part
      case 4: write(STDOUT_FILENO, "##############################[ About ]##############################\n\n\n\n\t\t\t\t", 77);
              file_content("./about"); /* about */
              char_get();
              break;
      case 5: break;
      default : write(STDOUT_FILENO, "Wrong puts ! \n\n",14);          
    }          
  }while(choice != 5);
    write(STDOUT_FILENO, "\x1b[?25h", strlen("\x1b[?25h"));
}

int main(int argc, char** argv){
  menu();
}