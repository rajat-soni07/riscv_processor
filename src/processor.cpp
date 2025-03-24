#include <iostream>
#include <map>
#include "registers.cpp"
#include "memory.cpp"
#include "instructions.cpp"
#include "input.cpp"

struct IF_OUT{
    int pc;
};

struct ID_OUT{
    int data;
};

struct EX_OUT{
    int data;
};

struct MEM_OUT{
    int data;
};

struct WB_OUT{
    int data;
};

class Processor{
private:
    std::map <int,Instruction> inst;
    Memory mem;
    Register reg;
public:
    IF_OUT if_out;
    ID_OUT id_out;
    EX_OUT ex_out;
    MEM_OUT mem_out;
    WB_OUT wb_out;

    Processor(std::vector<std::vector<std::string>> inp){
        int pc = 0;
        for (auto& instruction : inp) {
            Instruction inst_obj(std::stoll("0x" + instruction[1], nullptr, 16));
            inst[pc] = inst_obj;
            pc+=4;
        }

        if_out.pc = 0;
        id_out.data = 0;
        ex_out.data = 0;
        mem_out.data = 0;
        wb_out.data = 0;
    }

    void instruction_fetch(){
        // if_out.inst=inst[if_out.pc];
        if_out.pc+=4;
        return;
    }

    void instruction_decode(){
        return;
    }

    void execution_stage(){
        return;
    }

    void memory_operation(){
        return;
    }

    void write_back(){
        return;
    }

    void simulate_clock_cycle(){
        instruction_fetch();

        // WB is written before ID because it occurs in the first half of cycle where as ID occurs in second half.
        write_back();
        instruction_decode();

        execution_stage();
        memory_operation();
        return;

        // This function should return the program counter of operation at which the stage is currently on.
    }
};
