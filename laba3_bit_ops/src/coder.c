#include "coder.h"

int encode(uint32_t code_point, CodeUnit *code_unit)
{
    if(code_point < 0x80){
        // 1000 0000
        code_unit -> length = 1;
        code_unit -> code[0] = code_point;
    }
    else if(code_point < 0x800){
        // 1000 0000 0000
        code_unit -> length = 2;
        code_unit -> code[0] = 0xc0 | (code_point >> 6);
        // 1100 0000
        code_unit -> code[1] = 0x80 | (code_point & 0x3f); 
    }
    else if(code_point < 0x10000){
        // 1 0000 0000 0000 0000
        code_unit -> length = 3;
        code_unit -> code[0] = 0xe0 | (code_point >> 12);
        // 1110 0000
        code_unit -> code[1] = 0x80 | ((code_point >> 6) & 0x3f);
        code_unit -> code[2] = 0x80 | (code_point & 0x3f);
    }
    else if(code_point < 0x200000){
        // 10 0000 0000 0000 0000
        code_unit -> length = 4;
        code_unit -> code[0] = 0xf0 | (code_point >> 18);
        // 1111 0000
        code_unit -> code[1] = 0x80 | ((code_point >> 12) & 0x3f) ;
        code_unit -> code[2] = 0x80 | ((code_point >> 6) & 0x3f);
        code_unit -> code[3] = 0x80 | (code_point & 0x3f);
    }
    else{
        return -1;
    }
    return 0;
}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
    int result = fwrite(code_unit->code, 1, code_unit->length, out);
    return result;
}

int read_next_code_unit(FILE *in, CodeUnit *code_unit)
{
    uint8_t byte;
    fread(&byte, sizeof(uint8_t), 1, in);

    if(byte<0x80){
        code_unit -> length = 1;
        code_unit -> code[0] = byte;
        return 0;
    }
    else if(byte < 0xe0){
        //111xxxxx
        code_unit -> length = 2;
        code_unit -> code[0] = byte;
        fread(&byte, sizeof(uint8_t), 1, in);
        if(byte < 0xc0){
            //11xxxxxx
            code_unit -> code[1] = byte;
        }
        else{
            printf("bitiy");
        }
        return 0;
    }
    else if(byte < 0xf0){
        //1111xxxx
        code_unit -> length = 3;
        code_unit -> code[0] = byte;
        fread(&byte, sizeof(uint8_t), 1, in);
        if(byte < 0xc0){
            code_unit -> code[1] = byte;
            fread(&byte, sizeof(uint8_t), 1, in);
            if(byte < 0xc0){
                code_unit -> code[2] = byte;
            }
            else{
                printf("bitiy");
            }
        }
        else{
            printf("bitiy");
        }
        return 0;
    }
    else if(byte < 0xf8){
        //11111xxx
        code_unit -> length = 4;
        code_unit -> code[0] = byte;
        fread(&byte, sizeof(uint8_t), 1, in);
        if(byte < 0xc0){
            code_unit -> code[1] = byte;
            fread(&byte, sizeof(uint8_t), 1, in);
            if(byte < 0xc0){
                code_unit -> code[2] = byte;
                fread(&byte, sizeof(uint8_t), 1, in);
                if(byte < 0xc0){
                    code_unit -> code[3] = byte;
                }
                else{
                    printf("bitiy");
                }
            }
            else{
                printf("bitiy");
            }
        }
        else{
            printf("bitiy");
        }
        return 0;
    }
    else{
        read_next_code_unit(in, code_unit);
        return -1;
    }
}