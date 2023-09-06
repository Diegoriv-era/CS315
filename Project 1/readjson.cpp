//
// Created by Diego Rivera. This file reads through the user input data and calls
// functions from htmlout.hpp to output HTML for each user read.
//
#include "readjson.hpp"
#include "htmlout.hpp"
#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

readjson::readjson() {
}

//reads through the whole json file and creates a list of users
void readjson::readfile() {
    htmlout obj;
    int id_int= 0;
    int newid_int = 0;
    string traverse;
    string throwawayword;
    ifstream jsonfile("input.json");

    if(jsonfile.is_open()){

        while(!jsonfile.eof()) {

            jsonfile >> traverse;

            if (traverse == "\"id_str\"") {
                jsonfile >> throwawayword;
                jsonfile >> id_str;
                id_str.erase(remove(id_str.begin(), id_str.end(), '\"'), id_str.end());
                id_int = stoi(id_str);
                obj.idinsert(id_int);
                id_str = "";
            }

            if (traverse == "\"name\"") {
                jsonfile >> throwawayword;
                getline(jsonfile, name);
                name.erase(remove(name.begin(), name.end(), '\"'), name.end());
                name.erase(remove(name.begin(), name.end(), ','), name.end());
                stringstream space(name);
                string str, str2;
                space >> str;
                space >> str2;

                if(str2==""){
                    name = str;
                }

                else{
                    name = str + " " + str2;
                }
            obj.nameinsert(name);
            name = "";
            }

            if(traverse == "\"location\""){
                jsonfile >> throwawayword;
                location = "";
                assert(location=="");
                traverse = "";
                getline(jsonfile,location);
                location.erase(remove(location.begin(), location.end(), ','), location.end());
                location.erase(remove(location.begin(), location.end(), '\"'), location.end());
                stringstream space(location);
                string str, str2;
                space >> str;
                space >> str2;

                if(str2==""){
                    location = str;
                    obj.locationinsert(location);
                }

                else{
                    location = str + " " + str2;
                    obj.locationinsert(location);
                }

                space.clear();
                str.clear();
                str2.clear();
                location.clear();
                location="";
            }

            if(traverse == "\"pic_url\""){
                jsonfile >> throwawayword;
                jsonfile >> url;
                url.erase(remove(url.begin(), url.end(), '\"'), url.end());
                obj.urlinsert(url);
                url = "";
            }

            if(traverse == "\"follows\""){
                jsonfile >> throwawayword;
                jsonfile >> follows;
                follows.erase(remove(follows.begin(), follows.end(), '\"'), follows.end());
                follows.erase(remove(follows.begin(), follows.end(), '['), follows.end());
                follows.erase(remove(follows.begin(), follows.end(), ']'), follows.end());
                stringstream test(follows);

                while(test.good()){
                    string element;
                    getline(test,element, ',');

                    if(!element.empty()){
                        newid_int = stoi(element);
                        followlist.push_back(newid_int);
                    }
                }
                obj.followsinsert(followlist);
                follows = "";
                followlist.clear();
            }

            if(traverse== "},"){
                objlist.push_back(obj);
                obj.locationinsert("");
                obj.urlinsert("");
            }
            traverse.clear();

        }
        objlist.push_back(obj);
        jsonfile.close();
    }

    else{
        cout << "bad read!!!" << endl;
    }

}

/* calls HTML function from htmlout.hpp in a for loop to create a html file for each user (from vector of users) */
void readjson::objmakehtml(vector<htmlout>users) {
    for (int i = 0; i < users.size(); ++i) {
        users.at(i).HTML(users);
    }
}

/* calls HTMLINDEX function from htmlout.hpp. Uses the first user in the list of objects to call the function  */
void readjson::objmakeindexhtml(vector<htmlout> users){
    users[0].HTMLINDEX(users);
}
