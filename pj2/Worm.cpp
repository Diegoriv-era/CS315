/* Diego Rivera Project 2 */
#include "Worm.hpp"
#include <string>
#include "Cell.hpp"
#include <array>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include <iostream>

using namespace std;

// const int MAX_QSIZE = 2000;

Worm::Worm(){
    size =0;
     array = new Cell[MAX_QSIZE]; // actually allocate the array
     if (array == nullptr) {
         cerr << "Couldn't allocate initial array\n";
         exit(1);
     }
     frontIndex = 0;
     
     backIndex = 0;
}

bool Worm::addHead(Cell valToPush) {
   //makes sure queue isnt full
   
    if(size == MAX_QSIZE){
       return false;
    }
    else if (size == 0){
        array[frontIndex] = valToPush;
        
    }
    else{
        array[(backIndex+1) % MAX_QSIZE] = valToPush;
        backIndex = (backIndex + 1) % MAX_QSIZE;
    }
    //cout << array[frontIndex].row << " " << array[frontIndex].column << endl;
    size++;
    //cout << "SIZE:" << size << endl;
    return true;
}





Cell Worm::removeTail() {
    
    exitIfEmpty(); // call parent function to exit w/ error from empty queue
    if (size == 1){
        Cell value = array[frontIndex];
        size--;

        backIndex = 0;
        frontIndex = 0;
        return value;
    }
    if(size > 1){
        Cell value = array[frontIndex];
        size--;
        frontIndex +=1;
        return value;
    }
    //return 0; // fix!
}
