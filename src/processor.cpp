#include <iostream>

struct IF_OUT{
    int data;
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
    IF_OUT if_out;
    ID_OUT id_out;
    EX_OUT ex_out;
    MEM_OUT mem_out;
    WB_OUT wb_out;

public:
    Processor(){
        if_out.data = 0;
        id_out.data = 0;
        ex_out.data = 0;
        mem_out.data = 0;
        wb_out.data = 0;
    }

    void instruction_fetch(){
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
        instruction_decode();
        execution_stage();
        memory_operation();
        write_back();
        return;
    }
};
