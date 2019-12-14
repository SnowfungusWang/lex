//
// Created by mush on 2019/12/12.
//
#include "structs.h"
#include <stack>
#include<iterator>


using std::stack;
using std::pair;
using std::iterator;

void getExtend(DFA* cur,FAnode* curNode);
DFA* isNew(DFA* cur,vector<DFA*>& inner);

void NFA2DFA(NFA& finalNFA,set<char>& edgeName,vector<DFA*>& resDFA){
    //求DFA
    //建立点集合，深度优先找@-闭包
    int count=0;
    DFA* start=new DFA;
    start->core.insert(finalNFA[0]);
    start->id=count++;
    FAnode* s =finalNFA[0];
    getExtend(start,s);

    vector<DFA*> innerStatus;
    innerStatus.push_back(start);
    int pos=0;
    
    while(pos<innerStatus.size()){
        //对集合中每个找结束边，建立新的点集合
        for (set<char>::iterator i=edgeName.begin();i!=edgeName.end();i++) {
            DFA* next=new DFA;
            for (auto curNode : innerStatus[pos]->core) {
                for (auto & edge : curNode->edges) {
                    if (edge.first == *i) {
                        next->core.insert(edge.second);
                        if (edge.second->isFinal){
                            next->sym.push_back(edge.second->symbol);
                        }
                    }
                }
            }
            for (auto curNode : innerStatus[pos]->ext) {
                for (auto & edge : curNode->edges) {
                    if (edge.first == *i) {
                        next->core.insert(edge.second);
                        if (edge.second->isFinal){
                            next->sym.push_back(edge.second->symbol);
                        }
                    }
                }
            }
            //有发出边
            if (next->core.size()!=0){
                DFA* real=isNew(next,innerStatus);
                //DFA是新的
                if (real==nullptr) {
                    real = next;
                    for (auto &node: real->core) {
                        getExtend(real, node);
                    }
                    real->id = count++;
                    innerStatus.push_back(real);
                }
                innerStatus[pos]->edges.insert(pair<char,DFA*>{*i,real});

            }
        }
        pos++;
    }
    for (int j = 0; j < innerStatus.size(); ++j) {
        resDFA.push_back(innerStatus[j]);
    }
//    resDFA=innerStatus;
//    resDFA=*innerStatus[0];
    //点集合分为core和extend
    //新的点集合和core对比，完全一致的话直接copy
    //建立vector bool，标记每个点集合是否找完
}


void getExtend(DFA* cur,FAnode* curNode){
    for(auto & edge : curNode->edges){
        if (edge.first=='#'){
            cur->ext.insert(edge.second);
            if (edge.second->isFinal){
                cur->sym.push_back(edge.second->symbol);
            }
            getExtend(cur,edge.second);
        }
    }
}

DFA* isNew(DFA* cur,vector<DFA*>& inner){
    for (int i = 0; i < inner.size(); ++i) {
        if (inner[i]->core.size()==cur->core.size()){
            bool res=true;
            for (auto & node:cur->core) {
                if (inner[i]->core.find(node)==inner[i]->core.end()){
                    res=false;
                    break;
                }
            }
            if (res){
                return inner[i];
            }
        }
    }
    return nullptr;
}


