#include <ncurses.h>
#include <string.h>

/* Declare our window  */ 
   WINDOW *mywin;  

/* Number of rows and cols */ 
int r, c, nrows, ncols,ch;  

void backspace()
{ 
  noecho();  
  nocbreak();  
  getyx(mywin, r, c);
  move(r, c-1);   
  delch(); 
  cbreak();  
  refresh();               
}     


/*  Handle the keyboard input  */ 
int keyhandler(char *word) 
{
	int i = 0;
	while( 1 ) {
		ch = getch(); 
		if(ch == '\n') return 1; //search mode

		if(ch == '\t') return 2; //auto complete mode
		getyx(mywin, r, c);  
		     
		if (ch == KEY_BACKSPACE) {
			backspace();
			word[strlen(word) - 1] = '\0';
		}    
		else {
		  	addch(ch);
		  	word[i] = ch;
		  	word[i+1] = '\0';
		  	i++;
		}                         
	}
	return 1;
}


int get_word(char *word)
{     
	int mode;        
   /* Initialise the screen  */    
   mywin = initscr();
   noecho();
   raw();  
   keypad(stdscr, TRUE);   
       
   scrollok(mywin,1);    
   idcok(mywin, 1); 
   idlok(mywin, 1);   
   getmaxyx(mywin, nrows, ncols); 
   clear(); 
   refresh();          
   /*  Set row and col */ 
   r=0; c=0; 
    
    mode = keyhandler(word);                 
                
   echo(); 
   keypad(mywin, 0); 
   endwin();
   return mode;   
}