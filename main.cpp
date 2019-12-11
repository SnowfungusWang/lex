#include <iostream>
#include<string>
#include <vector>
#include "structs.h"


using std::string;
using std::iostream;
using std::vector;


string infix2Shuffix(string in);
string addDot(string in);
NFA& re2NFA(vector<RE> rules);

int main() {
    std::cout << "Hello, World!" << std::endl;
    string res1=addDot("(aa*|bb*)(a|(bb*))");
    string res2=infix2Shuffix(res1);
    vector<RE> rule;
    RE myRE1,re2,re3;
    myRE1.symbol="myRe";
    myRE1.re="a*";
    re2.symbol="2";
    re3.symbol="3";
    re2.re="b*";
    re3.re="a";
    rule.push_back(myRE1);
    rule.push_back(re2);
    rule.push_back(re3);

    NFA finalNFA;
    re2NFA(rule);




    std::cout <<res2;
    return 0;

}