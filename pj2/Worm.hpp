/* Diego Rivera Project 2 */
#include <iostream>
#include <string>
#include <array>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include "Cell.hpp"
using namespace std;

#ifndef PJ2_WORM_HPP
#define PJ2_WORM_HPP
const int MAX_QSIZE = 2000;
class Worm{
    
    public:

    Worm();
    
    ~Worm() { delete [] array; }
    bool addHead(Cell valToPush);
    Cell removeTail();
    bool empty() { return (size == 0); }
    Cell head() {return array[backIndex]; } // Return the cell representing the position of the worm’s head without modifying the worm
    Cell tail() {return array[frontIndex]; }

    private:

    int size;    
    Cell* array; // pointer for the array itself
    int frontIndex, backIndex; // indices for the front and back elements of queue

    protected:

    void exitIfEmpty() {
          if (empty()) {
              std::cerr << "Can't do this operation on an empty queue\n";
              exit(1);
          } 
      }
};
#endif