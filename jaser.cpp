//
// Created by izhakmo@wincs.cs.bgu.ac.il on 23/11/2019.
//
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "jaser.h"
using namespace std;
using json=nlohmann::json;

void jaser:: useJson() {
    ifstream i("../config.json");
    json j;
    i >> j;
    string s=j.dump(1);
    i.close();
    int g=1;
    for(auto &x: j["movies"].items()){
        cout<<g<<"Movie"<<endl;
        string name=x.value()["name"];
        int k=x.value()["length"];
        cout<<name<<endl;
        cout<<k<<endl;
        vector<string> tags;
        for(auto tag:x.value()["tags"].items()){
            tags.push_back(tag.value());
        }
        for(int u=0;u<tags.size();u++)
            cout<<tags.at(u)<<endl;
        g++;
    }
        cout<< j["movies"][x]["name"] <<endl;
    ofstream o("../plox.json");
    o<<setw(4)<<j<<endl;

}


