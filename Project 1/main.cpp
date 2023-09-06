#include <iostream>
#include "htmlout.hpp"
#include "readjson.hpp"

int main() {
    readjson a;
    a.readfile();
    //cout << a.objlist.size() << "me!!" <<endl;
    //cout << a.objlist.at(2).getlocatioon() << endl;
    a.objmakeindexhtml(a.objlist);
    //cout << a.mapfollowlist.size();
    a.objmakehtml(a.objlist);
    return 0;
}

