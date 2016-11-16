#include <stdio.h>
#include <string.h>
#define LIVE 1
#define DEAD 0

char takeinput();
void printboard(char board[41][41]);
void initializeboard(char board[41][41]);
void addlivecell(int x, int y, char board[41][41]); 
void killcell(int x, int y, char board[41][41]);
void checkneighbors(char board[41][41], int neighbors[41][41]);
void nextiteration(char board[41][41], int neighbors[41][41]);

   //Rules of life:
   //1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
   //2. Any live cell with two or three live neighbours lives on to the next generation.
   //3. Any live cell with more than three live neighbours dies, as if by over-population.
   //4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
   
int main() {

   char board[41][41], choice;
   int loop=1;
   int x, y;
   char d; //dummy character that prevents new line character from being read as input 
   int neighbors[41][41];

   initializeboard(board);

   while (loop) {

      choice=takeinput();
      switch (choice) {
	 case 'a':
	    //add new live cell
	    system("clear");
	    printf("Please enter an x and y position between 0 and 40: \n");
	    scanf("%d %d", &x, &y);
	    scanf("%c", &d);
	    system("clear");
	    addlivecell(x, y, board);
	    checkneighbors(board, neighbors);
	    printboard(board);
	    break;
	 case 'r':
	    //remove live cell
	    system("clear");
	    printf("Please enter an x and y position between 0 and 40: \n");
	    scanf("%d %d", &x, &y);
	    scanf("%c", &d);
	    system("clear");
	    killcell(x, y, board);
	    checkneighbors(board, neighbors);
	    printboard(board);
	    break;
	 case 'n':
	    //advance to next iterations
	    system("clear");
	    scanf("%c", &d);
	    nextiteration(board, neighbors);
	    checkneighbors(board, neighbors);
	    break;
	 case 'q':
	    //quit program
	    loop=0; 
	    system("clear");
	    break;
	 case 'p':
	    //play game forever, no more inputs taken
	    while (1) {
	       nextiteration(board, neighbors);
	       checkneighbors(board, neighbors);
	       usleep(100000);
	       system("clear");
	    }
      }

   }
}


char takeinput() {

   char c;

   printf("MENU \n");
   printf("a: add a new live cell\n");  
   printf("r: remove a live cell \n");
   printf("n: advance to next iteration \n");      
   printf("q: quit the program \n");      
   printf("p: play game forever, no more inputs will be taken \n\n");      
   printf("Please enter menu choice:   \n");      
   scanf("%c", &c);

   return c;

}

void printboard(char board[41][41]) {

   int i, j;


   printf("----------------------------------------\n");
   for (i=0; i<41; i++) {
      for (j=0; j<41; j++) {
	 if (board[i][j] == DEAD) {
	    printf("%c", '.');
	 }
	 else if (board[i][j] == LIVE) {
	    printf("%c", 'X');
	 }
	 if (j==40) {
	    printf("\n");
	 }
      }
   }
   printf("----------------------------------------\n");
}

void initializeneighbors(int neighbors[41][41]) {

    int i, j;

    for (i=0; i<41; i++) {
	for (j=0; j>41; j++) {
	    neighbors[i][j]=0;
	}
    }

}

void initializeboard(char board[41][41]) {

   int i, j;

   for (i=0; i<41; i++) {
      for (j=0; j<41; j++) {
	board[i][j]=0;
      }
   }

}

void addlivecell(int x, int y, char board[41][41]) {

   board[y][x]=LIVE;

}

void killcell(int x, int y, char board[41][41]) {

   board[y][x]=DEAD;

}

//This function returns how many neighbors each cell has
void checkneighbors(char board[41][41], int neighbors[41][41]) {  

   int n, x, y;

   for (y=0; y<41; y++) {
      for (x=0; x<41; x++) {
	 n=0;
	 if (y-1>=0) {
            if (board[y-1][x]==LIVE) { 
               n++;
            }
         }

         if (y+1<41) {
            if (board[y+1][x]==LIVE) {
               n++;
            }
         }

         if (x-1>=0) {
            if (board[y][x-1]==LIVE) {
               n++;
            }
         }

         if (x+1<41) {
            if (board[y][x+1]==LIVE) {
               n++;
            }
         }

         if (y-1>=0 && x-1>=0) {
            if (board[y-1][x-1]==LIVE) {
               n++;
            }
         }

         if (y+1<41 && x-1>=0) {
            if (board[y+1][x-1]==LIVE) {
               n++;
            }
         }

         if (y-1>=0 && x+1<41) {
            if (board[y-1][x+1]==LIVE) {
               n++;
            }
         }

         if (y+1<41 && x+1<41) {
            if (board[y+1][x+1]==LIVE) {
               n++;
            }
         }

	 neighbors[y][x]=n;

	 //print neighbors
	 //printf("%d", neighbors[y][x]);
	 //if (y==40) {
	 //   printf("\n");
	 //}

      }
   }
}

void nextiteration(char board[41][41], int neighbors[41][41]) {

   int row, col, n;

   for (row=0; row<41; row++) {
      for (col=0; col<41; col++) {
	 if (board[row][col]==LIVE) {  //position is alive
	    if (neighbors[row][col]==0 || neighbors[row][col]==1) {
	       killcell(col, row, board);
	    }
  	    if (neighbors[row][col]>3) {
	       killcell(col, row, board);
	    }
	 }
	 else { //position is dead
	    if (neighbors[row][col]==3) {
		addlivecell(col, row, board);
	    }
	 }
      }
   }

   printboard(board);

}
