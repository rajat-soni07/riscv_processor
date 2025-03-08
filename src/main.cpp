#include <bits/stdc++.h>

typedef struct IF_INPUT {
    int opcode;
} IF_INPUT;

typedef struct IF_OUTPUT {
    int opcode;
} IF_OUTPUT;

typedef struct ID_INPUT {
    int opcode;
} ID_INPUT;

typedef struct ID_OUTPUT {
    int opcode;
} ID_OUTPUT;

typedef struct EX_INPUT {
    int opcode;
} EX_INPUT;

typedef struct EX_OUTPUT {
    int opcode;
} EX_OUTPUT;

typedef struct MEM_INPUT {
    int opcode;
} MEM_INPUT;

typedef struct MEM_OUTPUT {
    int opcode;
} MEM_OUTPUT;

typedef struct WB_INPUT {
    int opcode;
} WB_INPUT;

typedef struct WB_OUTPUT {
    int opcode;
} WB_OUTPUT;

void instruction_fetch(IF_INPUT* inp, IF_OUTPUT* out){
    return;
}

void instruction_decode(ID_INPUT* inp, ID_OUTPUT* out){
    return;
}

void exceutive(EX_INPUT* inp, EX_OUTPUT* out){
    return;
}

void memory_fetch(MEM_INPUT* inp, MEM_OUTPUT* out){
    return;
}

void write_back(WB_INPUT* inp, WB_OUTPUT* out){
    return;
}


int main(int argc, char const *argv[])
{
    return 0;
}
