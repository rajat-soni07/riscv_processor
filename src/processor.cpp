#include <iostream>
#include <map>
#include "registers.cpp"
#include "memory.cpp"
#include "instructions.cpp"
#include "input.cpp"

struct IF{
    int pc;
    long long int machinecode;
};

struct ID{
    int pc;
    long long int machinecode;
    Instruction* inst;
    int source1;
    int source2;
};

struct EX{
    int pc;
    long long int machinecode;
    Instruction* inst;
    int data;
    int store_value;
};


struct MEM{
    long long int machinecode;
    Instruction* inst;
    int pc;
    int data;
};



class Processor{
private:
    std::map <int,Instruction> inst;
    std::vector<std::vector<std::string>> input;
    Memory mem;
    Register reg;

public:
    int pc_global;
    IF if_out;
    IF id_in;
    ID id_out;
    ID ex_in;
    EX ex_out;
    EX mem_in;
    MEM mem_out;
    MEM wb_in;
    

    Processor(std::vector<std::vector<std::string>> inp){
        input = inp;
        int pc = 0;
        for (auto& instruction : inp) {
            Instruction inst_obj(std::stoll("0x" + instruction[0], nullptr, 16));
            inst[pc] = inst_obj;
            pc+=4;
        }

        pc_global = 0;
        if_out.pc = 0;
        id_in.pc = 0;
        id_out.pc = 0;
        ex_out.pc = 0;
        mem_in.pc = 0;
        mem_out.pc = 0;
        wb_in.pc =0;

    }

    void instruction_fetch(){
        if_out.machinecode=std::stoll("0x" + input[pc_global/4][0],nullptr,16);
        if_out.pc=pc_global;
        return;
    }

    void instruction_decode(){
        id_out.pc = id_in.pc;
        id_out.machinecode = id_in.machinecode;
        id_out.inst = &inst[id_in.pc];
        id_out.source1 = reg.fetch_from_ind(id_out.inst->reg1);
        id_out.source2 = reg.fetch_from_ind(id_out.inst->reg2);
        return;
    }

    void execution_stage(){
        int opcode = extract(ex_in.machinecode,0,6);
        ex_out.machinecode = ex_in.machinecode;
        ex_out.inst = ex_in.inst;
        std::string op = ex_in.inst->operation;
        int dest = ex_in.inst -> rd;
        int a = ex_in.source1;
        int b = ex_in.source2;
        int im = ex_in.inst ->imm;
        switch (opcode)
        {
        case 51:
            if (op=="add"){ex_out.data = a+b;}
            else if (op=="add"){ex_out.data = a+b;}
            else if (op=="sub"){ex_out.data = a-b;}
            else if (op=="sll"){ex_out.data = a<<b;}
            else if (op=="slt"){ex_out.data = a<b;}
            else if (op=="sltu"){unsigned int c = ((unsigned int) a);
                                unsigned int d = ((unsigned int) b);
                                ex_out.data = c<d;}
            else if (op=="xor"){ex_out.data = a^b;}
            else if (op=="srl"){unsigned int c = ((unsigned int) a);
                                unsigned int d = ((unsigned int) b);
                                ex_out.data = c>>d;}
            else if (op=="sra"){ex_out.data = a>>b;}
            else if (op=="or"){ex_out.data = a|b;}
            else if (op=="rem"){ex_out.data = a%b;}
            else if (op=="and"){ex_out.data = a&b;}
            break;
        
        case 19:
            if (op=="addi"){ex_out.data = a+im;}
            else if (op=="slli"){ex_out.data = a<<im;}
            else if (op=="slti"){ex_out.data = a<im;}
            else if (op=="sltiu"){unsigned int c = ((unsigned int) a);
                                ex_out.data = c<im;}
            else if (op=="xori"){ex_out.data = a^im;}
            else if (op=="srli"){unsigned int c = ((unsigned int) a);
                                ex_out.data = c>>im;}
            else if (op=="srai"){ex_out.data = a>>im;}
            else if (op=="ori"){ex_out.data = a|im;}
            else if (op=="andi"){ex_out.data = a&im;}
        
        case 3:
            if (op=="lb"){ex_out.data = a+im;}
            else if (op=="lh"){ex_out.data =a+im;}
            else if (op=="lw"){ex_out.data = a+im;}
            else if (op=="lbu"){ex_out.data = a+im;}
            else if (op=="lhu"){ex_out.data = a+im;}
            break;

        case 35:
            if (op=="sb"){ex_out.data = a+im;
                            ex_out.store_value = b;}
            else if (op=="sh"){ex_out.data = a+im;
                            ex_out.store_value = b;}
            else if (op=="sw"){ex_out.data = a+im;
                            ex_out.store_value = b;}
            break;

        case 111:
            if (op=="jal"){ex_out.data = im;}
            break;
        case 103:
            if (op=="jalr"){ex_out.data = a+im;}
            break;
        default:
            break;
        }

        return;
    }

    void memory_operation(){
        mem_out.machinecode = mem_in.machinecode;
        mem_out.pc = mem_in.pc;
        mem_out.inst = mem_in.inst;
        std::string op = mem_in.inst->operation;
        int opcode = extract(mem_in.machinecode,0,6);
        switch (opcode)
        {
        case 3:
            if (op=="lb"){mem_out.data = mem.read_byte(mem_in.data);}
            else if (op=="lh"){mem_out.data = mem.read_half(mem_in.data);}
            else if (op=="lw"){mem_out.data = mem.read_word(mem_in.data);}
            else if (op=="lhu"){mem_out.data = mem.read_half(mem_in.data);}
            break;
        case 35:
            if (op=="sb"){mem.save_byte(mem_in.data,mem_in.store_value);}
            else if (op=="sh"){mem.save_half(mem_in.data,mem_in.store_value);}
            else if (op=="sw"){mem.save_word(mem_in.data,mem_in.store_value);}
        default:
            break;
        }
        return;
    }

    void write_back(){
        std::string op = wb_in.inst->operation;
        int opcode = extract(wb_in.machinecode,0,6);
        int dest = wb_in.inst->rd;
        if (opcode==51|opcode==19|opcode==3|opcode==103|opcode==111){reg.update_from_ind(dest,wb_in.data);}
        return;
    }

    std::vector<int> simulate_clock_cycle_nonforwarding(){
        instruction_fetch();

        // WB is written before ID because it occurs in the first half of cycle where as ID occurs in second half.
        write_back();
        instruction_decode();

        execution_stage();
        memory_operation();


        // This function should return the program counter of operation at which the stage is currently on.
    }
};
