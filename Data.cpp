#include <iostream>
#include "Data.h"
#pragma once
using namespace std;

Data::Data() {
    recordID = "";
    city = "";
    state = "";
    year = "";
    solved = "";
    vicSex = "";
    vicAge = 0;
    perpSex = "";
    perpAge = "";

}

// at least 4 data members, match data attributes in data set
Data::Data(string ID, string c, string st, string yr, string solv, string vSex, int vAge, string pSex, string pAge) {
    recordID = ID;
     city = c;
     state = st;
     year = yr;
     solved = solv;
     vicSex = vSex;
     vicAge = vAge;
     perpSex = pSex;
     perpAge = pAge;

}

// overload comparison operator, height will be comparison attribute
bool Data::operator< (const Data& rhs) {
    return this->vicAge < rhs.vicAge;

}

bool Data::operator<= (const Data& rhs) {
    return this->vicAge <= rhs.vicAge;

}

// overload output stream operator, will be used to print
ostream& operator<< (ostream& out, const Data& print) {
    out << "record ID: " << print.recordID << endl;
    out << "city: " << print.city << endl;
    out << "state: " << print.state << endl;
    out << "year: " << print.year << endl;
    out << "solved?: " << print.solved << endl;
    out << "victim sex: " << print.vicSex << endl;
    out << "victim age: " << print.vicAge << endl;
    out << "perp sex: " << print.perpSex << endl;
    out << "perp age: " << print.perpAge << endl;

    return out;

}