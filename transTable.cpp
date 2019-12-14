//
// Created by mush on 2019/12/13.
//

#include"structs.h"
#include<vector>
#include <set>
#include <string>
#include<algorithm>
#include<iostream>


using std::set;
using std::vector;
using std::string;
using std::pair;

void getTransTable(vector<set<DFA*>>& minDFA,vector<unordered_multimap<char,int>>& transTable,
        vector<string>& tokenList){
    //找到首部
    for (int i = 0; i < minDFA.size(); ++i) {
        set<DFA*> cur=minDFA[i];
        for (auto& curDFA:cur) {
            if (curDFA->id==0){
                set<DFA*> fir=minDFA[i];
                minDFA.erase(minDFA.begin()+i);
                minDFA.insert(minDFA.begin(),fir);
            }
        }
    }
    //开始迭代
    for (int j = 0; j < minDFA.size(); ++j) {
        unordered_multimap<char,int> cur;
        transTable.push_back(cur);
        DFA* first=*minDFA[j].begin();
        for (auto& edge:first->edges) {
            bool hasFound=false;
            for (int i = 0; i < minDFA.size(); ++i) {
                if (minDFA[i].find(edge.second)!=minDFA[i].end()){
                    transTable[j].insert(pair<char,int>{edge.first,i});
                    break;
                }
            }
        }
        bool hasT=false;
        tokenList.push_back("");
        for (auto& node:minDFA[j]) {
            if(node->sym.size()!=0){
                tokenList[j]=node->sym[0];
                if (hasT){
                    std::cout<<"multi token";
                }
                hasT=true;
            }
        }
    }
}
