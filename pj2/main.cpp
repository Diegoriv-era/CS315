#include "Worm.hpp"

#include "Screen.hpp"


#include "Cell.hpp"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <array>
using namespace std;

int main(int argc, char *argv[]){
    int row = stoi(argv[1]);
    int column = stoi(argv[2]);
    if(argc == 1){
        cerr<< "need parameters" << endl;
        exit(1);
    }
    // The number of rows can be between 9 and 25 (inclusive), and the number of columns can be between 9 and 80 (inclusive).
    if (row<9 || row >25){
        cerr<< "ROWS NEED TO BE BETWEEN 9-25 (INCLUSIVE)" << endl;
        exit(1);
    }
    if(column < 9 || column > 80){
        cerr <<"COLUMNS NEED TO BE BETWEEN 9-80 (INCLUSIVE)" << endl;
        exit(1);
    }

    
    ScreenDS(row, column);
    
    


    return 0;
}