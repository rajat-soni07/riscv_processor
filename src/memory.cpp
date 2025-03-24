#include <iostream>
#include <map>

class Memory {
private:
    std::map<int, int> mem;

public:
    void save_word(int address, int value) {
        unsigned int val = (unsigned int) value;
        mem[address] = val&0xFF;
        mem[address+1] = (val>>8)&0xFF;
        mem[address+2] = (val>>16)&0xFF;
        mem[address+3] = (val>>24)&0xFF;
    }

    void save_byte(int address, int value) {
        mem[address] = value&0xFF;
    }

    void save_half(int address, int value) {
        mem[address] = value&0xFF;
        mem[address+1] = (value>>8)&0xFF;
    }

    int read_byte(int address) {
        auto tmp = mem.find(address);
        if (tmp != mem.end()) {
            return tmp->second;
        } else{
            return 0;
            // As garbage value is returned for non updated adresses
        }
    }

    int read_half(int address) {
        return (read_byte(address+1)<<8) + read_byte(address);
    }

    unsigned int read_word(int address) {
        return (read_half(address+2)<<16) + read_half(address);
    }

    bool exists(int address) {
        return mem.find(address) != mem.end();
    }
};