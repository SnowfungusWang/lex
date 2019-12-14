//
// Created by mush on 2019/12/10.
//

#include"structs.h"
#include<string>
#include<set>
#include<stack>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iostream>
#include <cstring>


using std::string;
using std::stack;
using std::set;
using std::vector;
using std::iostream;
using std::map;
using std::fstream;
//using std::algorithm;
string addDot(string in);
string infix2Shuffix(string in);

void getREs(vector<RE>& reFinal){
    fstream in("./re",std::ios::in);
    while(!in.eof()){
        string cur;
        getline(in,cur);
        char* buffer;
        char* token;
        char *curC = new char[cur.size()];
        strcpy(curC,cur.c_str());
        token= strtok_r(curC, " ", &buffer);
        RE* curRE=new RE;
        curRE->symbol=token;
        token= strtok_r(NULL," ",&buffer);
        string tempRe=token;
        tempRe=infix2Shuffix(addDot(tempRe));
        curRE->re=tempRe;
        reFinal.push_back(*curRE);
        delete curC;
    }
}


string addDot(string in){
    set<char> symbolList={'|','*','(',')'};
    char* temp=new char[in.size()*2];
    int pos=0;
    temp[0]=in[0];
    for (int i = 1; i < (int)in.size(); ++i) {
        if((symbolList.find(in[i])==symbolList.end()&&symbolList.find(temp[pos])==symbolList.end())
        ||(temp[pos]==')'&&in[i]=='(')
        ||(temp[pos]==')'&&symbolList.find(in[i])==symbolList.end())
        ||((in[i]=='('&&symbolList.find(temp[pos])==symbolList.end())
        ||(temp[pos]=='*'&&symbolList.find(in[i])==symbolList.end()))
        ){
            temp[++pos]='`';
            temp[++pos]=in[i];
        }else{
            temp[++pos]=in[i];
        }
    }
    string res(temp);
    delete temp;
    return res;
}

string infix2Shuffix(string in){
    set<char> symbolList={'|','*','(',')','`'};
    stack<char> _operandStack;
    _operandStack.push('@');
    map<char,int>outStack;
    outStack['@']=0;
    outStack['(']=0;
    outStack[')']=0;
    outStack['|']=1;
    outStack['`']=2;
    outStack['*']=3;


    int t=in.size();
    char* resC=new char[in.size()];
    int pos=0;
    int i=0;
    while (i<in.size()){
        if(symbolList.find(in[i])==symbolList.end()){
            resC[pos]=in[i];
            pos++;
            i++;
        }
        else{
            char temp=in[i];
            if (temp=='('){
                _operandStack.push(temp);
                i++;
            }
            else if(temp==')'){
                while (_operandStack.top()!='('){
                    resC[pos]=_operandStack.top();
                    _operandStack.pop();
                    pos++;
                }
                _operandStack.pop();
                i++;
            }
            else {
                while(outStack[_operandStack.top()]>=outStack[in[i]]){
                    resC[pos]=_operandStack.top();
                    _operandStack.pop();
                    pos++;
                }
                _operandStack.push(in[i]);
                i++;
            }
        }
    }
    while(_operandStack.top()!='@'){
        resC[pos]=_operandStack.top();
        _operandStack.pop();
        pos++;
    }
    string res(resC);
    return res;
}