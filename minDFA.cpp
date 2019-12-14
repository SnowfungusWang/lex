//
// Created by mush on 2019/12/12.
//
#include "structs.h"
#include <set>
#include <vector>


using std::set;
using std::vector;
using std::pair;

bool split(vector<set<DFA*>>& curSet,set<char>& edge);

void getDFAmin(vector<DFA*>& finalDFA,set<char>& edge,vector<set<DFA*>>& finalDFAmin){
    set<DFA*> notFinal;

    //终态分开放，非终态先放在一起
    for (int i = 0; i < finalDFA.size(); ++i) {
        //终态
        if (finalDFA[i]->sym.size()!=0){
            set<DFA*> temp;
            temp.insert(finalDFA[i]);
            finalDFAmin.push_back(temp);
        }
        else{
            notFinal.insert(finalDFA[i]);
        }
    }
    if (notFinal.size()!=0) finalDFAmin.push_back(notFinal);
    bool res= true;
    do{
        res=split(finalDFAmin,edge);
    }while(res);

}

bool split(vector<set<DFA*>>& curSet,set<char>& edge){
    bool isSplit=false;

    for (int i = 0; i < curSet.size(); ++i) {
        if (curSet[i].size()==1){
            continue;
        }
        //有多个子集
        else{
            DFA* standard=*curSet[i].begin();
            set<DFA*> possibleSplit;
            for (const char& j:edge){
                int pos=-1;
                for (auto& lastDFA:curSet[i]) {
                    pos++;
                    auto standardEdge=standard->edges.find(j);
                    auto otherEdge=lastDFA->edges.find(j);
                    //是否有这条边
                    if ((standardEdge==standard->edges.end()&&otherEdge!=lastDFA->edges.end())
                    ||(standardEdge!=standard->edges.end()&&otherEdge==lastDFA->edges.end())){
                        possibleSplit.insert(lastDFA);
                        curSet[i].erase(lastDFA);
                        isSplit=true;
                    }
                    else{
                       //均有
                        if(standardEdge!=standard->edges.end()&&otherEdge!=lastDFA->edges.end()){
                            //但是不等价
                            for (int k = 0; k <curSet.size() ; ++k) {
                                if (curSet[k].find(standardEdge->second)!=curSet[k].end()
                                &&curSet[k].find(otherEdge->second)==curSet[k].end()){
                                    isSplit=true;
                                    possibleSplit.insert(lastDFA);
                                    curSet[i].erase(lastDFA);
                                }
                            }
                        }
                    }
                }
                if (isSplit) {
                    curSet.push_back(possibleSplit);
                    break;
                }
            }
            if (isSplit) break;
        }
    }
    return isSplit;
}

