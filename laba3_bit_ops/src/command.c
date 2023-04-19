#include "coder.h"
#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *in;
    FILE *out;
    in = fopen(in_file_name,"r");
    if(!in){
        printf("in isnt open");
        return -1;
    }
    out = fopen(out_file_name,"wb");
    if(!out){
        printf("out isnt open");
        return -1;
    }

    uint32_t code_point;
    // for(int i=0;i<4;i++){
    while(!feof(in)){
        fscanf(in, "%" SCNx32, &code_point);
        printf("%" PRIx32 "\n", code_point);

        CodeUnit code_unit;
        if(encode(code_point, &code_unit) ==  -1){
            printf("encode error\n ");
            return -1;
        }

        write_code_unit(out, &code_unit);
    }
    fclose(in);
    fclose(out);

    return 0;
}