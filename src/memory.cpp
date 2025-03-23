#include <bits/stdc++.h>

class Memory {
private:
    std::map<int, int> mem;

public:
    void write(int address, int value) {
        mem[address] = value;
    }

    int read(int address) {
        auto tmp = mem.find(address);
        if (tmp != mem.end()) {
            return tmp->second;
        } else{
            return 0;
            // As garbage value is returned for non updated adresses
        }
    }

    bool exists(int address) {
        return mem.find(address) != mem.end();
    }
};