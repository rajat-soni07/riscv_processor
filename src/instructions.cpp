#include <bits/stdc++.h>
using namespace std;
int extract(int n, int i, int j) {
    return (((1 << (j - i + 1)) - 1) & (n >> i));
}
class Instruction{

public:
    int reg1;
    int reg2;
    int rd;
    string operation;
    int imm;
    int avl; // for forwarding (Rd value) 0-available after IF, 1-available after ID, 2-available after EX, 3-available after MEM, 4-available after WB



    Instruction(long long int code){
        int opcode=extract(code,0,6);
        if(opcode==51){
            //R type
            int funct7=extract(code,25,31);
            int rs2=extract(code,20,24);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            rd=extract(code,7,11);
            reg1=rs1;
            reg2=rs2;
            if(funct3==0){
                if(funct7==0){
                    operation="add";
                }
                else{
                    operation="sub";
                }
            }
            else if(funct3==1){
                operation="sll";
            }
            else if(funct3==2){
                operation="slt";
            }
            else if(funct3==3){
                operation="sltu";
            }
            else if(funct3==4){
                operation="xor";
            }
            else if(funct3==5){
                if(funct7==0){
                    operation="srl";
                }
                else{
                    operation="sra";
                }
            }
            else if(funct3==6){
                if(funct7==0){
                    operation="or";
                }
                else{
                    operation="rem";
                }
            }
            else if(funct3==7){
                operation="and";
            }
            avl=2;
        }
        else if(opcode==19){
            //I type
            int imm11_0=extract(code,20,31);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            rd=extract(code,7,11);
            reg1=rs1;
            reg2=-1;
            imm=imm11_0;
            if(funct3==0){
                operation="addi";
            }
            else if(funct3==1){
                operation="slli";
            }
            else if(funct3==2){
                operation="slti";
            }
            else if(funct3==3){
                operation="sltiu";
            }
            else if(funct3==4){
                operation="xori";
            }
            else if(funct3==5){
                if(imm11_0==0){
                    operation="srli";
                }
                else{
                    operation="srai";
                }
            }
            else if(funct3==6){
                operation="ori";
            }
            else if(funct3==7){
                operation="andi";
            }
            avl=2;
        }
        else if(opcode==3){
            //I type
            int imm11_0=extract(code,20,31);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            rd=extract(code,7,11);
            reg1=rs1;
            reg2=-1;
            imm=imm11_0;
            if(funct3==0){
                operation="lb";
            }
            else if(funct3==1){
                operation="lh";
            }
            else if(funct3==2){
                operation="lw";
            }
            else if(funct3==4){
                operation="lbu";
            }
            else if(funct3==5){
                operation="lhu";
            }
            avl=3;
        }
        else if(opcode==35){
            //S type

            // sw stores two reg in r1 and r2(No rd)
            int imm11_5=extract(code,25,31);
            int rs2=extract(code,20,24);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            int imm4_0=extract(code,7,11);
            rd=-1;
            reg1=rs1;
            reg2=rs2;
            imm=(imm11_5<<5)+imm4_0;
            if(funct3==0){
                operation="sb";
            }
            else if(funct3==1){
                operation="sh";
            }
            else if(funct3==2){
                operation="sw";
            }
            avl=-1; //there is no rd, so doesn't matter
        }
        else if(opcode==99){
            //B type
            int imm12=extract(code,31,31);
            int imm10_5=extract(code,25,30);
            int rs2=extract(code,20,24);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            int imm4_1=extract(code,8,11);
            rd=-1;
            reg1=rs1;
            reg2=rs2;
            imm=(imm12<<12)+(imm10_5<<5)+imm4_1;
            if(funct3==0){
                operation="beq";
            }
            else if(funct3==1){
                operation="bne";
            }
            else if(funct3==4){
                operation="blt";
            }
            else if(funct3==5){
                operation="bge";
            }
            else if(funct3==6){
                operation="bltu";
            }
            else if(funct3==7){
                operation="bgeu";
            }
            avl=1; //The new PC is available after ID stage
        }
        else if(opcode==111){
            // J type
            int imm20=extract(code,31,31);
            int imm10_1=extract(code,21,30);
            int imm11=extract(code,20,20);
            int imm19_12=extract(code,12,19);
            rd=extract(code,7,11);
            reg1=-1;
            reg2=-1;
            imm=(imm20<<19)+(imm19_12<<11)+(imm11<<10)+(imm10_1);
            imm*=2; // since the incremeent can only be even, bits are shifted left by 1
            operation="jal";

        }
        else if(opcode==103){
            int imm11_0=extract(code,20,31);
            int rs1=extract(code,15,19);
            int funct3=extract(code,12,14);
            rd=extract(code,7,11);
            reg1=rs1;
            reg2=-1;
            imm=imm11_0;
            operation="jalr";
        }
    }



};


int main(){
    Instruction ins(0x00030303);
    cout<<ins.operation<<endl;
    cout<<ins.reg1<<endl;
    cout<<ins.reg2<<endl;
    cout<<ins.rd<<endl;
    cout<<ins.imm<<endl;
    return 0;
}
