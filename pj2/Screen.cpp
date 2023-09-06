/* Diego Rivera Project 2 */
#include "Cell.hpp"
#include "Screen.hpp"
#include "Worm.hpp"
#include <iostream>
#include <vector>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>

//A constructor that initializes the vectors
/*
Assuming that the user does provide valid inputs, here’s a more detailed breakdown of the interactive screen:

The very top row is a message row. It should contain the name of the game on its left side and the score on the right. 
The second row from the top is a wall (a row of asterisks), as is the very bottom row.
The leftmost and rightmost columns should also be asterisks.
The playing field is the empty space within the walls. The user’s command-line inputs are the dimensions of this empty rectangle.
*/
ScreenDS::ScreenDS(int row, int column){ 
    vector<Cell>insertv;//
    Cell emptyC;
    
    int rowmiddle = (row/2)+1;
    int columnmiddle = (column/2)-3;
    Worm wormthing;
    Cell wormcell;
    wormcell.row = rowmiddle;
    wormcell.column = columnmiddle;
    wormcell.free = false;

    startup();
    mvaddstr(0,0,"Worm");
    mvaddstr(0,column-3,"Score: ");
    mvaddch(0, column+4, '0');
    
    for (int i = 0; i < row+2; ++i){
        //cout << i << endl;
        for (int j = 0; j <column+2; ++j){
            
           if(i == 0 || i == row+1){
                emptyC.free = false;
                emptyC.row = i;
                emptyC.column = j;
                insertv.push_back(emptyC);
                mvaddch(i+1, j, '*');
            }
            //cout << "NEW@@:" <<  screenlist.at(i).at(j).size() << endl;
            else if((j == 0 && (i != 0 && i != row+1)) || (j == column+1 && (i != 0 && i != row+1))){
                emptyC.free = false;
                emptyC.row = i;
                emptyC.column = j;
                insertv.push_back(emptyC);
                mvaddch(i+1, j, '*');
            }
            else{
                emptyC.free = true;
                emptyC.row = i;
                emptyC.column = j;
                insertv.push_back(emptyC);
                freeCells.push_back(emptyC);
            }            
            	  
        }
        
        screenlist.push_back(insertv);
        insertv.clear();
    }

    for(int i = 0; i < 8; ++i){
        
        wormcell.column++;
        wormthing.addHead(wormcell);

        wormOccupy(wormcell);

        if(i == 7){

            mvaddch(wormcell.row+1,wormcell.column,'@');
        }
        else{
            mvaddch(wormcell.row+1,wormcell.column,'o');
        }
                
    }
    

    
    Cell head;
    head = wormthing.head();
    Cell tail;
    
    bool check = true;
    Cell snack = getRandomFreeCell();
    snack.snack = true;

    wormOccupy(snack);
    srand(time(nullptr));
    int num = rand() % 9+1;
    stringstream ss;
    ss << num;
    string str = ss.str();
    mvaddch(snack.row+1,snack.column,str[0]);
    ss.clear();
    refresh();

    while (check){
        
	    char cc = get_char();
        while (cc!= 'a' && cc!= 's' && cc!= 'd' && cc!= 'w'){
            cc = get_char();
            
        }
        Cell b4head = wormthing.head();
        if (cc == 'a'){
             //move the worm left
            wormcell.column --;
         }
         if (cc == 'd'){
             //move the worm right
            wormcell.column++;
             
         }
         if (cc == 'w'){
             //move the worm up
            wormcell.row --;
             
         }
         if (cc == 's'){
             //move the worm down
             
             wormcell.row ++;
            
             
         }
        
        if(isFree(wormcell) == false){
            if(wormcell.row != snack.row || wormcell.column != snack.column){
                check = false;
                break;
            }
            
            
        }
        if(wormcell.row == snack.row && wormcell.column == snack.column){
        
            grow += num;
            score += num;
            stringstream stringscore;
            stringscore << score;
            string scored = stringscore.str();
            for (int i = 0 ; i< scored.size(); ++i){
                mvaddch(0, column+4+i, scored[i]);
            }

            makeFree(snack);
            snack = getRandomFreeCell();
            snack.snack = true;
            
            num = rand() % 9+1;
            stringstream ss;
            ss << num;
            string str = ss.str();
            mvaddch(snack.row+1,snack.column,str[0]);
            ss.clear();
            str.clear();
            wormOccupy(snack);
            refresh();
            

        }
        if (grow == 0){
            wormOccupy(wormcell);
            tail = wormthing.removeTail();
            wormthing.addHead(wormcell);
                    
            makeFree(tail);
            head = wormthing.head();
            mvaddch(b4head.row+1,b4head.column,'o');
            mvaddch(wormcell.row+1,wormcell.column,'@');
            mvaddch(tail.row+1,tail.column,' ');
            refresh();
        }
        else{
            wormOccupy(wormcell);
            
            wormthing.addHead(wormcell);
                    
            
            head = wormthing.head();
            mvaddch(b4head.row+1,b4head.column,'o');
            mvaddch(wormcell.row+1,wormcell.column,'@');
            grow--;
            refresh();


        }
        
}
    terminate();
    cout << "GAME OVER  SCORE: " << score << endl;
}
void ScreenDS::makeFree(Cell c){

    screenlist.at(c.row).at(c.column).free = true; // Sets screenlist cell to free
    c.free = true; //sets given cell to free
    freeCells.push_back(c); //pushes back freed cell into freecell list
    
}
void ScreenDS::wormOccupy(Cell c){
    screenlist.at(c.row).at(c.column).free = false;
    c.free = false;
    //c.snack = 

    for (auto& cell:freeCells){
        if (cell.row == c.row && cell.column == c.column){
            cell.row = freeCells.back().row;
            cell.column = freeCells.back().column;
            cell.snack = c.snack;
            freeCells.pop_back();
            break;
        }
    }
}

bool ScreenDS::isFree(Cell c){
    if((screenlist.at(c.row).at(c.column).free == true) || (screenlist.at(c.row).at(c.column).snack == true)){
        return true;
    }
    return false;
    
}



void ScreenDS::startup( void )
{
     initscr();	    /* activate the curses */
     curs_set(0);   /* do not display the cursor */
     clear();	    /* clear the screen that curses provides */
     noecho();	    /* prevent the input chars to be echoed to the screen */
     cbreak();	    /* change the stty so that characters are delivered to the
		       program as they are typed--no need to hit the return key!*/
}
void ScreenDS::terminate(void)
{
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}

const int SEC_DELAY = 0;
const int USEC_DELAY = 800000;
static char lastc = ' ';

char ScreenDS::get_char( void )
{
     char	c;
     struct timeval tvec;
     fd_set rfds;

     tvec.tv_sec = SEC_DELAY;
     tvec.tv_usec = USEC_DELAY;
     FD_ZERO(&rfds);
     FD_SET(0, &rfds);

     int retval = select(1, &rfds, NULL, NULL, &tvec);

     if ( retval < 0 )
	 die();

     if ( retval ) {
         if ( read(0, &c, 1) < 0)
             die();
         //if( c == LEFT || c == RIGHT || c == UP || c == DOWN ) 

         
         lastc = c;
     }
     return( lastc );
}

void ScreenDS::die( void )
{
     signal( SIGINT, SIG_IGN );
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     endwin();
     exit( 1 );
}

Cell ScreenDS::getRandomFreeCell(){
    srand(time(nullptr));
    int num = rand() % freeCells.size(); 
    
    return freeCells.at(num);
}