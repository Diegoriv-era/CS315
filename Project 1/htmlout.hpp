//
// Created by Diego Rivera. This file outputs HTML for each user from the data that the
// readjson.hpp had read and organized
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

#ifndef PJ1_CS315_READFILE_HPP
#define PJ1_CS315_READFILE_HPP



class htmlout{
public:
    htmlout();

    //simple inserts to populate values into the private member variables
    void idinsert(int id_int){this->id_int = id_int;}
    void nameinsert(string name){this->name = name;}
    void locationinsert(string location){this->location = location;}
    void urlinsert(string pic_url){this->pic_url = pic_url;}
    void followsinsert(vector<int> vfollows){this->vfollows = vfollows;}

    //These are used to return the values of the private member variables
    int getidint(){return id_int;}
    string getname(){return name;}
    string getlocatioon(){return location;}
    string getpicurl(){return pic_url;}

    //outputs Index.html and uses the vector parameter to create the list of users in the 'network'
    void HTMLINDEX(vector<htmlout> users);

    //outputs one user.html and uses the vector parameter to create the list of follows/followers/mutuals.
    void HTML(vector<htmlout> users);

    //one for loop to iterate through follows list and outputs the list into the file
    void createfollowslist(ofstream& out, vector<htmlout> users);

    /* double for loop to iterate through the user list and uses each users follow list to
       figure out if they follow the current user. When it finds a user who follows the current
       user it inserts that users ID into the objects vfollowing list */
    void createfollowerslist(ofstream& out, vector<htmlout> users); //outputs list of the users followers as HTML

    /* double for loop to iterate through follows and vfollowing lists. If ID's exist in both list
       then both users follows each other and */
    void createmutualslist(ofstream& out, vector<htmlout> users); //outputs list of the users mutual followers as HTML

    vector <htmlout> vusers;
private:
    int id_int;
    string id_str;
    string name;
    string location;
    string pic_url;
    string follows;
    vector<int> vfollowing;
    vector <int> vfollows;

};
#endif //PJ1_CS315_READFILE_HPP