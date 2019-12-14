//
// Created by mush on 2019/12/13.
//
#include <fstream>
#include <string>
#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;

void printSym(string token,vector<char>& cur);
void reportErr(vector<char>& cur);
void getTable(vector<unordered_multimap<char,int>>& transTable,vector<string>& tokenList);
int main(){
    vector<unordered_multimap<char,int>> transTable;
    vector<string> tokenList;
    getTable(transTable,tokenList);
    fstream in("./input",ios::in);
    char cur = 0;
    int state=0;
    vector<char> curStr;
    bool isFinal=false;
    string token;

    while(true){
//        in>>cur;
        in.get(cur);
        //分隔符

        if (cur=='\n'||cur=='\t'||cur==' '||in.eof()){
            state=0;
            if (isFinal){
                printSym(token,curStr);
                isFinal=false;
                curStr.clear();
            }
            else{
                if (curStr.size()!=0){
                    reportErr(curStr);
                    curStr.clear();
                }
            }
            if (in.eof()){
                break;
            }
        }
        else{
            unordered_multimap<char,int> curState=transTable[state];
            //当前没有这个边
            if (curState.empty()||curState.find(cur)==curState.end()){
                do{
                    curStr.push_back(cur);
                    in.get(cur);
                }
                while (cur!='\n'&&cur!='\t'&&cur!=' '&&!in.eof());
                reportErr(curStr);
                isFinal=false;
                curStr.clear();
                state=0;
                if (in.eof()){
                    break;
                }
                //还回去
                in.seekg(-1,ios::cur);
            }
            else{
                state=curState.find(cur)->second;
                curStr.push_back(cur);
                //当前状态为终态
                if (tokenList[state].length()!=0){
                    isFinal=true;
                    token=tokenList[state];
                }
            }
        }
    }
}

void printSym(string token,vector<char>& cur){
    char* str=new char[cur.size()+1];
    cout<<token<<" ";
    for (int i = 0; i < cur.size(); ++i) {
        cout<<cur[i];
    }
    cout<<endl;
}

void reportErr(vector<char>& cur){
    for (int i = 0; i < cur.size(); ++i) {
        cout<<cur[i];
    }
    cout<<" is not legal."<<endl;
}