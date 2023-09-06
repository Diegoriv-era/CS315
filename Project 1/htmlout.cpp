//
// Created by Diego Rivera. This file outputs HTML for each user from the data that the
// readjson.hpp had read and organized
//
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include "htmlout.hpp"
#include <cassert>

htmlout::htmlout() {
}

//outputs Index.html and uses the vector parameter to create the list of users in the 'network'
void htmlout::HTMLINDEX(vector<htmlout> users){

    ofstream out;

    out.open("Index.html");
    assert(out.is_open());

    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" << "My Social Network" << "</title>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<h1>" << "My Social Network: User List" << "</h1>" << endl;
    out << "<ol>" << endl;

    for (int i =-0; i < users.size();++i){
        out << "<li><a href=\"" << "user" << i+1 << ".html" << "\">" << users.at(i).name << "</a></li>" << endl;
    }
    out << "</ol>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;

    out.close();
}

//one for loop to iterate through follows list and outputs the list into the file
void htmlout::createfollowslist(ofstream& out, vector<htmlout> users) {
    bool empty = true;
    for(int i = 0; i<vfollows.size(); ++i){
        empty = false;
        out << "<li><a href="  << "\"user" << users.at(vfollows.at(i)-1).id_int << ".html\">" << users.at(vfollows.at(i)-1).name << "</a></li>" << endl;
    }
    if(empty){
        out << "<p>None</p>" << endl;
    }
}

/* double for loop to iterate through the user list and uses each users follow list to
       figure out if they follow the current user. When it finds a user who follows the current
       user it inserts that users ID into the objects vfollowing list */
void htmlout::createfollowerslist(ofstream& out, vector<htmlout> users) { //outputs list of the users followers as HTML
    bool empty2 = true;
    for(int i =0; i <users.size(); ++i){
        for (int j = 0; j < users.at(i).vfollows.size();++j) {
            if (this->id_int == users.at(i).vfollows[j]) {
                empty2 = false;
                vfollowing.push_back(users.at(i).id_int);
                out << "<li><a href=\"" << "user" << users.at(i).id_int << ".html\">" << users.at(i).name <<"</a></li>" << endl;
            }
        }
    }
    if(empty2){
        out << "<p>None</p>" << endl;
    }
}

/* double for loop to iterate through follows and vfollowing lists. If ID's exist in both list
       then both users follows each other and */
void htmlout::createmutualslist(ofstream &out, vector<htmlout> users) { //outputs list of the users mutual followers as HTML
    bool empty3= true;
    for (int i = 0; i < vfollows.size(); ++i){ //size of user list
        for (int j = 0; j < vfollowing.size(); ++j){ //who the users follow and who current user follows
            if (vfollows.at(i) == vfollowing.at(j)){
                empty3 = false;
                out << "<li><a href=\"" << "user" << vfollows.at(i) << ".html\">" << users.at(vfollows.at(i)-1).name <<"</a></li>" << endl;
            }
        }
    }
    if(empty3){
        out << "<p>None</p>" << endl;
    }
}

//outputs one user.html and uses the vector parameter to create the list of follows/followers/mutuals.
void htmlout::HTML(vector<htmlout> users){
    id_str = to_string(id_int);
    ofstream out;
    string filename = "user" + id_str + ".html";
    out.open(filename);
    assert(out.is_open());

    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" << name << " Profile</title>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<h1>" << name;

    if(location.size() != 0){
       out << " in " << location << "</h1>" << endl;
    }
    else{
        out << "</h1>" << endl;
    }
    if(pic_url.size() != 0) {
        out << "<img alt=" << "\"Profile pic\"" << " src=" << "\"" << pic_url << "\"/>" << endl;
    }
    else{
        out << "<img alt=" << "\"Profile pic\"" << " src=" << "\"" << "https://upload.wikimedia.org/wikipedia/commons/f/f7/Facebook_default_male_avatar.gif" << "\"/>" << endl;
    }

    out << "<h2>Follows</h2>" << endl;
    out << "<ul>" << endl;

    createfollowslist(out,users);
    
    out << "</ul>" << endl;
    out << "<h2>Followers</h2>" << endl;
    out << "<ul>" << endl;

    createfollowerslist(out, users);

    out << "</ul>" << endl;
    out << "<h2>Mutuals</h2>" << endl;
    out << "<ul>" << endl;

    createmutualslist(out, users);

    out << "</ul>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;
    out.close();
}
