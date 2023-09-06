/* Diego Rivera Project 2 */
#include <iostream>
#include <string>
#include <vector>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include "Cell.hpp"
#include <string>
using namespace std;

#ifndef PJ2_SCREEN_HPP
#define PJ2_SCREEN_HPP

class ScreenDS {
    public:
    ScreenDS(int row, int column); // A constructor that initializes the vectors
    void makeFree(Cell c);
    void wormOccupy(Cell c);
    bool isFree(Cell c);
    Cell getRandomFreeCell();
    void startup(void);
    void terminate(void);
    void die( void );
    char get_char( void );

    private:

    vector<Cell> freeCells;
    vector<vector<Cell>> screenlist;
    int grow = 0;
    int score = 0;

};


#endif