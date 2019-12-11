//
// Created by mush on 2019/12/10.
//

#include "structs.h"
#include <stack>

using std::stack;
using std::pair;


void re2NFA(vector<RE> rules){
    vector<NFA> singleNFA;
    int count=1;
    for (int i = 0; i < rules.size(); ++i) {
        //对每个RE进行分析，全部分析完后拿边连起来；
        //建立栈，放生成的小自动机，记录起点和终点
        //单目运算符：单个字符，*
        //双目运算符：`  |
        stack<NFA> temp_res;
        RE cur= rules[i];
        for (char & j : cur.re) {
            FAnode* start;
            FAnode* end;
            NFA last1,last2,curNFA;
            switch (j){
                case '*':
                    last1=temp_res.top();
                    temp_res.pop();
                    last1[1]->edges.insert(pair<char,FAnode*>{'#',last1[0]});
                    start=new FAnode;
                    end=new FAnode;
                    start->id=count++;
                    end->id=count++;
                    start->edges.insert(pair<char,FAnode*>{'#',end});
                    start->edges.insert(pair<char,FAnode*>{'#',last1[0]});
                    last1[1]->edges.insert(pair<char,FAnode*>{'#',end});
                    curNFA={start,end};
//                    last1=temp_res.top();
//                    temp_res.pop();
//                    last1[1].edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    start=new FAnode;
//                    end=new FAnode;
//                    start->id=count++;
//                    end->id=count++;
//                    start->edges.insert(pair<char,FAnode&>{'#',*end});
//                    start->edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    last1[1].edges.insert(pair<char,FAnode&>{'#',*end});
//                    curNFA={*start,*end};
//                    start.id=count++;
//                    end.id=count++;
//                    start.edges.insert(pair<char,FAnode&>{'#',end});
//                    start.edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    last1[1].edges.insert(pair<char,FAnode&>{'#',end});
//                    curNFA={start,end};
                    temp_res.push(curNFA);
                    break;
                case '`':
                    last1=temp_res.top();
                    temp_res.pop();
                    last2=temp_res.top();
                    temp_res.pop();
                    last2[1]->edges.insert(pair<char,FAnode*>{'#',last1[0]});
                    curNFA={last2[0],last1[1]};
                    temp_res.push(curNFA);

//                    last1=temp_res.top();
//                    temp_res.pop();
//                    last2=temp_res.top();
//                    temp_res.pop();
//                    last2[1].edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    curNFA={last2[0],last1[1]};
//                    temp_res.push(curNFA);
                    break;
                case '|':
                    last1=temp_res.top();
                    temp_res.pop();
                    last2=temp_res.top();
                    temp_res.pop();
                    start=new FAnode;
                    end=new FAnode;
                    start->id=count++;
                    end->id=count++;
                    start->edges.insert(pair<char,FAnode*>{'#',last1[0]});
                    start->edges.insert(pair<char,FAnode*>{'#',last2[0]});
                    last1[1]->edges.insert(pair<char,FAnode*>{'#',end});
                    last2[1]->edges.insert(pair<char,FAnode*>{'#',end});
                    curNFA={start,end};



//                    last1=temp_res.top();
//                    temp_res.pop();
//                    last2=temp_res.top();
//                    temp_res.pop();
//                    start=new FAnode;
//                    end=new FAnode;
//                    start->id=count++;
//                    end->id=count++;
//                    start->edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    start->edges.insert(pair<char,FAnode&>{'#',last2[0]});
//                    last1[1].edges.insert(pair<char,FAnode&>{'#',*end});
//                    last2[1].edges.insert(pair<char,FAnode&>{'#',*end});
//                    curNFA={*start,*end};


//                    start.id=count++;
//                    end.id=count++;
//                    start.edges.insert(pair<char,FAnode&>{'#',last1[0]});
//                    start.edges.insert(pair<char,FAnode&>{'#',last2[0]});
//                    last1[1].edges.insert(pair<char,FAnode&>{'#',end});
//                    last2[1].edges.insert(pair<char,FAnode&>{'#',end});
//                    curNFA={start,end};
                    temp_res.push(curNFA);
                    break;
                default:
                    start=new FAnode;
                    end=new FAnode;
                    start->id=count++;
                    end->id=count++;
//                    start->edges.insert(pair<char,FAnode&>{j,*end});
                    start->edges.insert(pair<char,FAnode*>{j,end});
                    curNFA={start,end};
//                    start.id=count++;
//                    end.id=count++;
//                    start.edges.insert(pair<char,FAnode&>{j,end});
//                    curNFA={start,end};
                    temp_res.push(curNFA);
            }

        }
        singleNFA.push_back(temp_res.top());
    }

}