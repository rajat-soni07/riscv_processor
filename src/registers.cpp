#include <bits/stdc++.h>

class Register {

private:
    int reg[32]; 
    std::map <std::string,int> indexes;
    
public:
    Register(){

        std::fill(std::begin(reg), std::end(reg), 0);

        for (int i = 0; i < 32; i++) {indexes["x" + std::to_string(i)] = i;}
        indexes["zero"] = 0;
        indexes["ra"] = 1;
        indexes["sp"] = 2;
        indexes["gp"] = 3;
        indexes["tp"] = 4;
        
        for (int i = 0; i < 3; i++) {indexes["t" + std::to_string(i)] = i+5;} // For t0-t2 reigsters
        for (int i = 0; i < 2; i++) {indexes["s" + std::to_string(i)] = i+8;} // For s0-s1 registers
        for (int i = 0; i < 8; i++) {indexes["a" + std::to_string(i)] = i+10;} // For a0-a7 registers
        for (int i = 0; i < 10; i++) {indexes["s" + std::to_string(i+2)] = i+18;} // For s2-s11 registers
        for (int i = 0; i < 4; i++) {indexes["t" + std::to_string(i+3)] = i+28;} // For t3-t6 registers

    }

    void update(std::string r,int val){
        auto tmp = indexes.find(r);
        if (tmp!=indexes.end()){
            reg[tmp->second] = val;
        }
        else{
            throw std::out_of_range("No such registers exists");
        }
        return;
    }

    int fetch(std::string r){
        auto tmp = indexes.find(r);
        if (tmp!=indexes.end()){
            return reg[tmp->second];
        }
        else{
            throw std::out_of_range("No such registers exists");
        }
        
    }

};