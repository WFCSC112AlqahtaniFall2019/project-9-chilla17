#include <iostream>
#include "Data.h"
#pragma once
using namespace std;

Data::Data() {
    state = "";
    year = "";
    vicAge = 0;
    perpAge = "";

}

// at least 4 data members, match data attributes in data set
Data::Data(string st, string yr, int vAge, string pAge) {
     state = st;
     year = yr;
     vicAge = vAge;
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
    out << "state: " << print.state << endl;
    out << "year: " << print.year << endl;
    out << "victim age: " << print.vicAge << endl;
    out << "perp age: " << print.perpAge << endl;

    return out;

}