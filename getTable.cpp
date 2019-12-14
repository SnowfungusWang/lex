#include <iostream>
#include<string>
#include <vector>
#include<fstream>
#include "structs.h"


//using std::string;
//using std::iostream;
//using std::vector;
//using std::fstream;

using namespace std;

void getREs(vector<RE>& reFinal);
void re2NFA(vector<RE>& rules,NFA& finalNFA,set<char>& edgeName);
void NFA2DFA(NFA& finalNFA,set<char>& edgeName,vector<DFA*>& resDFA);
void getDFAmin(vector<DFA*>& finalDFA,set<char>& edge,vector<set<DFA*>>& finalDFAmin);
void getTransTable(vector<set<DFA*>>& minDFA,vector<unordered_multimap<char,int>>& transTable,
                   vector<string>& tokenList);

void getTable(vector<unordered_multimap<char,int>>& transTable,vector<string>& tokenList) {
    std::cout << "Hello, World!" << std::endl;
    set<char> edge;
    vector<RE> rule;
    getREs(rule);
    NFA finalNFA;
    re2NFA(rule,finalNFA,edge);
    vector<DFA*> finalDFA ;
    NFA2DFA(finalNFA,edge,finalDFA);
    vector<set<DFA*>> finalDFAmin;
    getDFAmin(finalDFA,edge,finalDFAmin);
    getTransTable(finalDFAmin,transTable,tokenList);

}