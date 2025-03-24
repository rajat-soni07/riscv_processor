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
    Instruction inst;
    int source1;
    int source2;
};

struct EX{
    int pc;
    long long int machinecode;
    Instruction inst;
    int data;
    int store_value;
};


struct MEM{
    long long int machinecode;
    Instruction inst;
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
            Instruction inst_obj;
            inst_obj.build_instruction(std::stoll("0x" + instruction[0], nullptr, 16));
            inst[pc] = inst_obj;
            pc+=4;
        }

        pc_global = 0;
        if_out.pc = -1;
        id_in.pc = -1;
        id_out.pc = -1;
        ex_out.pc = -1;
        mem_in.pc = -1;
        mem_out.pc = -1;
        wb_in.pc =-1;
        

    }

    void instruction_fetch(){
        if_out.machinecode=std::stoll("0x" + input[pc_global/4][0],nullptr,16);
        if_out.pc=pc_global;
        return;
    }

    void instruction_decode(){
        id_out.pc = id_in.pc;
        id_out.machinecode = id_in.machinecode;
        id_out.inst = inst[id_in.pc];
        if (id_out.inst.reg1!=-1){
            id_out.source1 = reg.fetch_from_ind(id_out.inst.reg1);
        }
        if (id_out.inst.reg2!=-1){
            id_out.source2 = reg.fetch_from_ind(id_out.inst.reg2);
        }
        return;
    }

    void execution_stage(){
        int opcode = extract(ex_in.machinecode,0,6);
        ex_out.machinecode = ex_in.machinecode;
        ex_out.inst = ex_in.inst;
        ex_out.pc = ex_in.pc;
        std::string op = ex_in.inst.operation;
        int dest = ex_in.inst . rd;
        int a = ex_in.source1;
        int b = ex_in.source2;
        int im = ex_in.inst .imm;
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
        std::string op = mem_in.inst.operation;
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
        std::string op = wb_in.inst.operation;
        int opcode = extract(wb_in.machinecode,0,6);
        int dest = wb_in.inst.rd;
        if (opcode==51|opcode==19|opcode==3|opcode==103|opcode==111){reg.update_from_ind(dest,wb_in.data);}
        return;
    }

    std::vector<int> simulate_clock_cycle_nonforwarding(){
        // stall only possible in ID stage
        // Reg values fetched by ID are always used in nonforwarding
        wb_in.pc=-1;mem_in.pc=-1;ex_in.pc=-1;id_in.pc=-1;
        if(mem_out.pc!=-1){
            wb_in = mem_out; 
        }
        if(ex_out.pc!=-1){
            mem_in = ex_out;
        }
        bool stalled=false;
        if(id_out.pc!=-1){
            int rs1 = id_out.inst.reg1;
            int rs2 = id_out.inst.reg2;
            if(ex_out.pc!=-1 && (rs1==ex_out.inst.rd||rs2==ex_out.inst.rd)){
                stalled = true;
            }
            if(mem_out.pc!=-1 && (rs1==mem_out.inst.rd||rs2==mem_out.inst.rd)){
                stalled = true;
            }
            if(stalled==false){
            if(wb_in.pc!=-1 && (rs1==wb_in.inst.rd||rs2==wb_in.inst.rd)){
                if(rs1==wb_in.inst.rd){id_out.source1=mem_out.data;}
                else{id_out.source2=mem_out.data;}
            }}
        }

        if(mem_out.pc!=-1){
            mem_out.pc=-1; 
        }
        if(ex_out.pc!=-1){
            ex_out.pc=-1;
        }
        if(stalled==false){
            if(id_out.pc!=-1){
                ex_in = id_out;id_out.pc=-1;
            }
            if(if_out.pc!=-1){
                id_in = if_out;if_out.pc=-1;
            }
        }
        else{
            id_in.machinecode=id_out.machinecode;
            id_in.pc=id_out.pc;
        }
        std::vector<int> temp;

        if(4*inst.size()>pc_global){
            temp.push_back(pc_global);
            
            instruction_fetch();
            pc_global+=4;
        }
        else{
            temp.push_back(-1);
        }

        if(id_in.pc!=-1){instruction_decode();temp.push_back(id_in.pc);}else{id_out.pc=-1;temp.push_back(-1);}
        if(ex_in.pc!=-1){execution_stage();temp.push_back(ex_in.pc);}else{ex_out.pc=-1;temp.push_back(-1);}
        if(mem_in.pc!=-1){memory_operation();temp.push_back(mem_in.pc);}else{mem_out.pc=-1;temp.push_back(-1);}
        if(wb_in.pc!=-1){write_back();temp.push_back(wb_in.pc);}else{wb_in.pc=-1;temp.push_back(-1);}

        return temp;
    }

    std::vector<int> simulate_clock_cycle_forwarding(){return simulate_clock_cycle_nonforwarding();}
    
};


// int main(){

//     Processor p(read_file("../inputfiles/strlen.txt"));
//     std::vector<int> temp=p.simulate_clock_cycle_nonforwarding();
//     for(auto c:temp){
//         std::cout<<c<<" ";
//     }
//     std::cout<<std::endl;
//     for (int i = 0; i < 8; i++)
//     {
//         temp=p.simulate_clock_cycle_nonforwarding();
//         for(auto c:temp){
//             std::cout<<c<<" ";
//         }
//         std::cout<<std::endl;
//     }
    
    
// }