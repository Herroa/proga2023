#include <stdio.h>
#include <string.h>
#include <inttypes.h>

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnit;

int encode_file(const char *in_file_name, const char *out_file_name);
int encode(uint32_t code_point, CodeUnit *code_unit);
int write_code_unit(FILE *out, const CodeUnit *code_unit);

int encode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *in;
    FILE *out;
    in = fopen(in_file_name,"r");
    if(!in){
        return -1;
    }
    out = fopen(out_file_name,"wb");
    if(!out){
        return -1;
    }

    uint32_t code_point;
    fscanf(in, "%" SCNx32, &code_point);
    printf("%" PRIx32 "\n", code_point);

    CodeUnit code_unit;
    if(encode(code_point, &code_unit) ==  -1){
        printf("encode error\n ");
        return -1;
    }

    write_code_unit(out, &code_unit);
    fclose(in);
    fclose(out);

    return 0;
}

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
    else if(code_point < 0x1000){
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

int main(int argc, char *argv[])
{
    if(argc!= 4){
        printf("err\n");
        return 0;
    }
    const char *command = argv[1];
    const char *in_file_name = argv[2];
    const char *out_file_name = argv[3];

    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    if(strcmp(command, "encode") == 0){
        encode_file(in_file_name, out_file_name);
    }
    else{
        return 1;
    }


    return 0;
}