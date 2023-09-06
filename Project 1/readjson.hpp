//
// Created by Diego Rivera. This file reads through the user input data and calls
// functions from htmlout.hpp to output HTML for each user read.
//
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "htmlout.hpp"
#include <map>
#include <unordered_map>


#ifndef PJ1_CS315_READJSON_HPP
#define PJ1_CS315_READJSON_HPP

#endif //PJ1_CS315_READJSON_HPP

class readjson {
public:
    readjson();
    void readfile(); //reads through the whole json file and creates a list of users

    void objmakehtml(vector<htmlout>users); /* calls HTML function from htmlout.hpp in a for loop
                                           to create a html file for each user (from vector of users) */

    void objmakeindexhtml(vector<htmlout> users); /* calls HTMLINDEX function from htmlout.hpp. Uses the first user in the list of objects
                                                 to call the function  */
    vector <htmlout> objlist; //list of objects (users)
private:
    string id_str;
    string name;
    string location;
    string url;
    string follows;
    vector <int> followlist;
};