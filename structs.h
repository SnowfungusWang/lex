//
// Created by mush on 2019/12/10.
//

#ifndef LEX_STRUCTS_H
#define LEX_STRUCTS_H

#include<string>
#include<map>
#include<vector>
#include<set>
#include <unordered_map>


using std::string;
using std::vector;
using std::map;
using std::unordered_multimap;
using std::set;




struct FAnode{
    int id;
    bool isFinal=false;
    string symbol;
    unordered_multimap<char,FAnode*> edges ;
};

struct RE{
    string symbol;
    string re;
};

typedef vector<FAnode*> NFA;

struct DFA{
    int id;
    set<FAnode*> core;
    set<FAnode*> ext;
    unordered_multimap<char,DFA*> edges;
    vector<string> sym;
};

struct minDFA{
    int id;
    unordered_multimap<char,int> edge;
    bool isFinal;
    string sym;
};

#endif //LEX_STRUCTS_H
