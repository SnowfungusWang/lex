//
// Created by mush on 2019/12/10.
//

#ifndef LEX_STRUCTS_H
#define LEX_STRUCTS_H

#include<string>
#include<map>
#include<vector>
#include <unordered_map>


using std::string;
using std::vector;
using std::map;
using std::unordered_multimap;

struct RE{
    string symbol;
    string re;
};

struct FAnode{
    int id;
    char type;
    unordered_multimap<char,FAnode*> edges ;
};

typedef vector<FAnode*> NFA;


#endif //LEX_STRUCTS_H
