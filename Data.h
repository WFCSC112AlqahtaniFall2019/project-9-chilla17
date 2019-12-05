#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H
#include <iostream>
using namespace std;


class Data {
public:
    Data(); // default constructor
    Data(string recordID, string city, string state, string year, string solved, string vicSex, int vicAge, string perpSex, string perpAge);
    friend ostream& operator<<(ostream &out, const Data& print);
    bool operator< (const Data& rhs);
    bool operator<= (const Data& rhs);

protected:
    string recordID;
    string city;
    string state;
    string year;
    string solved;
    string vicSex;
    int vicAge;
    string perpSex;
    string perpAge;
};


#endif //PROJECT9_DATA_H
