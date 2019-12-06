#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H
#include <iostream>
using namespace std;


class Data {
public:
    Data(); // default constructor
    Data(string st, string yr, int vAge, string pAge);
    friend ostream& operator<<(ostream &out, const Data& print);
    bool operator< (const Data& rhs);
    bool operator<= (const Data& rhs);

protected:
    string state;
    string year;
    int vicAge;
    string perpAge;
};


#endif //PROJECT9_DATA_H
