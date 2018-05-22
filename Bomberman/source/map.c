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




/*###################################### MAP #######################################*/

#include "map.h"
#include "run_game.h"


/*##############################
 *Symbol definition :
 *##############################
 */

#define HEART ("❤")
#define BOMB  ("õ")
#define POWER_SYMBOLE ("☼")
#define PLAYER_1 ("¥")
#define PLAYER_2 ("♣")
#define EMPTY_BOX "\u2759"
#define FILLED_BOX "\u275A"
#define CHAFFER "\u2620"
#define DEFAULT_SPEED 200

/*##############################
 *Color definition :
 *##############################
 */

#define DEFAULT  "\x1B[0m"
#define RED      "\x1B[31m"
#define GREEN    "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE     "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN     "\x1B[36m"
#define WHITE    "\x1B[37m"
#define SIGNED      "\x1B[5m"




/*###########################################################################
 * get_dimension : function that retrieves the size of the terminal
 *###########################################################################
 */

void get_dimension(){
  ioctl(0, TIOCGWINSZ, &win);
}

/*##########################################################
 * current_position : position the cursor to center the map in the terminal
 * Arguments :  
 * - map = of type map_map, contains the map as a matrix
 *##########################################################
 */

void current_position(game_map map){
  if(map.width > win.ws_col || map.height > win.ws_row)exit(EXIT_FAILURE);

  cur.x = (win.ws_col/4) - (map.width/2);
  cur.y = (win.ws_row/2) - (map.height/2);
}

/*##########################################################
 * display_icon : write-function that displays the icons in the terminal
 * Arguments : 
 * - icon_nbr1 = number of player 1 icon's
 * - icon_nbr2 = number of player 1 icon's
 * - mwidth = matrix width
 * - icon = icon to display
 * - color = color of icon 
 *##########################################################
 */



void display_icon(int icon_nbr1, int icon_nbr2, int mwidth, char * icon, char * color){
  int i;

  write(1,color,strlen(color));
  for(i=0; i<icon_nbr1; i++){
    write(STDOUT_FILENO, icon, strlen(icon));
  }

  for(i= 0; i<mwidth - (icon_nbr1 + icon_nbr2); i++){
    write(STDOUT_FILENO, " ", 1);
  }

  for(i=0; i<icon_nbr2; i++){
    write(STDOUT_FILENO, icon, strlen(icon));
  }

  write(STDOUT_FILENO, "\n\r", 2);
}



/*##########################################################
 * display_map : write-function of the matrix associated with the map in the stdout
 * Arguments : 
 * - map = of type game_map, contains the map as a matrix
 * - player1 = information about player1
 * - player2 = information about player2
 * Return value: 0 if successful and -1 for errors 
 *##########################################################
 */



int display_map(game_map map, player* player1, player* player2){
  int i,j;
  move_cursor(1,0); /* Move the cursor to the top right of the terminal */
  
  if(map.map == NULL)return -1;

  /* display the players' icons on the map */
  display_icon(player1->life->life, player2->life->life, map.width, HEART, RED);
  display_icon(player1->b->bomb, player2->b->bomb, map.width,BOMB,BLUE);
  display_icon(player1->rayonement, player2->rayonement, map.width,"\u2605",BLUE);

  if(player1->v->speed < DEFAULT_SPEED && player2->v->speed < DEFAULT_SPEED){
    display_icon(3, 3, map.width,">",GREEN);
  }else if(player1->v->speed < DEFAULT_SPEED){
    display_icon(3, 0, map.width,">",GREEN);
  }else if(player2->v->speed < DEFAULT_SPEED){
    display_icon(0, 3, map.width,">",GREEN);
  }else{
    display_icon(0, 0, map.width,">",GREEN);
  }
 
  /* Displays the colors and animations of the map */ 
  for(i = 0; i < map.height ; i++){
        move_cursor(i+5,0);
        write(1,"\x1b[?25l", strlen("\x1b[?25l"));
      for (j = 0; j < map.width; j++){
          switch(map.map[i][j]){
            case 'N': write(1,GREEN, strlen(GREEN));                     
                      write(1,PLAYER_1 ,strlen(PLAYER_1));
                      break;
            case 'A': write(1,GREEN, strlen(GREEN));
                      write(1,PLAYER_2 ,strlen(PLAYER_2));
                      break;
            case '@': write(1,RED, strlen(RED));
                      write(1,SIGNED,strlen(SIGNED)); 
                      write(1,BOMB,strlen(BOMB));  
                      break;
            case '0': write(1,MAGENTA, strlen(MAGENTA));
                      write(1,FILLED_BOX,strlen(FILLED_BOX));
                      break;
            case '1': write(1,YELLOW,strlen(YELLOW));
                      write(1,EMPTY_BOX,strlen(EMPTY_BOX));                     
                      break;
            case '2': write(1,CYAN, strlen(CYAN));
                      write(1,FILLED_BOX,strlen(FILLED_BOX));                     
                      break;
            case ' ': write(1,"\x1B[33m", strlen("\x1B[33m"));
                      write(1," ",1);                     
                      break;
            case '+': write(1,BLUE, strlen(BLUE));
                      write(1,"+",strlen("+"));
                      break;
            case '#': write(1,BLUE, strlen(BLUE));
                      write(1,POWER_SYMBOLE,strlen(POWER_SYMBOLE));
                      break;
            case 'x': write(1,RED, 5);
                      write(1,CHAFFER,strlen(CHAFFER));
                      break;
            case '*': write(1,BLUE, strlen(BLUE));
                      write(1,BOMB,strlen(BOMB));
                      break;          
            default : 
                  write(1,CYAN, strlen(CYAN));
                      write(1,FILLED_BOX,strlen(FILLED_BOX));                     
                      break;
          }
          write(1,"\x1B[0m", 4);
        
      }
  }
  return 0;
}




/*#######################################################################################
 * extract_map : function that transposes the map resulting from a descriptor into a matrix
 * Arguments : 
 * - mapdesc = descriptor associated with the file.txt containing the map
 * - map = map_map, contains the map as a matrix 
 * Return value: 0 if successful and -1 for errors 
 *#######################################################################################
 */

int extract_map(int mapdesc, game_map map){
  int i=0,j=0;
  ssize_t lread = 0;
  int length;
  char* bufextra = malloc(sizeof(char) * map.width + 1);
 
  if(mapdesc == -1)return -1;

    length=2*((map.width*map.height)+map.height);
  
  while((lread = read(mapdesc, bufextra, map.width + 1)) && length > 0){ /*Loop until mapdesc has been fully read */
    bufextra[lread] = 0;
    for(j = 0; j <= lread; j++){ /* create a single loop and we write in each memory box the string associated with the line*/
      map.map[i][j] = bufextra[j];
    }
    map.map[i][j + 1] = 0;
    i++;
    length-=lread; 
  }

  map.map[i] = NULL;
  free(bufextra);

  return 0;
}



/*##########################################################
 * allocate_map : function that allocates dynamically a memory to a matrix
 * Arguments : 
 * - mapalloc = map_map, contains the map as a matrix, the length and mwidth of the matrix is ​​in the structure 
 * Return value: returns the array with the allocated memory space
 *##########################################################
 */

game_map allocate_map(game_map mapalloc){
  int i;

  mapalloc.map = (char**)malloc(((mapalloc.height)*2 + 1) * sizeof(char*)); /* allocate for each memory space a space of size height + 1 */

  for (i = 0; i <= mapalloc.height*2; i++){
     
    mapalloc.map[i]=(char*)malloc((mapalloc.width + 1) * sizeof(char)); /* allocate in each memory sub-slot a space of size width + 1 */
  }
  //allocates to record the position of the bomb "the time"

  for(i=0 ; i<MAX_BOMBE ;i++){
    mapalloc.blast[i].ttexpl = malloc(sizeof(struct timeval));
    mapalloc.blast[i].flag_expl = FALSE;
  }

  return mapalloc;
}




/*##########################################################
 * desallocate_map : function that dynamically allocates memory to a matrix
 * Arguments : 
 * - mapalloc = map_map, contains the map as a matrix, the length and mwidth of the matrix is ​​in the structure
 * Return value: returns the array with the allocated memory space
 *##########################################################
 */
game_map desallocate_map(game_map mapdesalloc){ 
  int i;

  for(i = 0 ; i < MAX_BOMBE ; i++){
    free(mapdesalloc.blast[i].ttexpl); /* deallocate in each memory slot a space of size width + 1 */
    mapdesalloc.blast[i].ttexpl=NULL;
  }

  for(i = 0; i <= mapdesalloc.height*2; i++){
    free(mapdesalloc.map[i]); /* allocate in each memory sub-space a space of size width + 1 */
    mapdesalloc.map[i]=NULL;
  }

  free(mapdesalloc.map);
  mapdesalloc.map = NULL;
 
  mapdesalloc.width = 0;
  mapdesalloc.height = 0;
  return mapdesalloc;
}




/*##########################################################
 * construct : function that builds the map in the terminal
 * Arguments : 
 * - map_file = file where the map is 
 * Return value: 0 if successful and -1 for errors
 *##########################################################
 */

game_map construct(const char* map_file){
  int file_desc,lread;
  char buf_file[SIZE];
  char* line_numb;
  char* column_numb;
  game_map map;
  
  if((file_desc = open(map_file, O_RDONLY)) == -1) exit(EXIT_FAILURE);
   
  lread = read(file_desc, buf_file, SIZE);
  if(lread < 0){
    close(file_desc);
      exit(EXIT_FAILURE);
    }
      
  if((line_numb = strpbrk(buf_file, " "))){ /* retrieve the number of lines from our matrix, which is the first piece of information in our file*/
    *line_numb = 0;
    line_numb++;
  }else{
    close(file_desc);
    exit(EXIT_FAILURE);
  }
    
  if((column_numb = strpbrk(line_numb, "\n"))){ /* retrieve the number of lines from our matrix, which is the second piece of information in our file */
    *column_numb = 0;
    column_numb++;
  }else{
    close(file_desc);
    exit(EXIT_FAILURE);
  }

  /* Int conversion of the row and column number */
  map.width = atoi(line_numb);
  map.height = atoi(buf_file);

  /* now move to the first position of the map */
  int prem_pos = strlen(line_numb) + strlen(buf_file) + 2;
  lseek(file_desc, prem_pos, SEEK_SET);
    
  map = allocate_map(map);
 
  if(extract_map(file_desc, map) == -1){
    close(file_desc); 
    exit(EXIT_FAILURE);
  }

  close(file_desc);

  return map;
}




/*##########################################################
 * restor : terminal returns to canonical mode
 *_______________________________________________
 */


int restor(){
  return tcsetattr(STDIN_FILENO,TCSANOW,&old_term);
}

/*##########################################################
 * change : terminal returns to non-canonical mode
 *_______________________________________________
 */
  
int change(){

  struct termios new_stdio;
  
  if(tcgetattr(STDIN_FILENO,&old_term) == -1){ 
    perror("tcgetattr");
    return -1;
  }

  /* instructions for switching to non-canonical mode */
  new_stdio = old_term;
  cfmakeraw(&new_stdio);
  new_stdio.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  new_stdio.c_oflag &= ~OPOST;
  new_stdio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  new_stdio.c_cflag &= ~(CSIZE | PARENB);
  new_stdio.c_cflag |= CS8;

  new_stdio.c_cc[VMIN]=1;
  new_stdio.c_cc[VTIME]=0;

  if(tcsetattr(STDIN_FILENO,TCSANOW,&new_stdio)==-1){
    perror("tcsetattr");
    return -1;
  }
  
  return 0;
}
