#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!= 4){
        printf("err\n");
        return 0;
    }
    const char *command = argv[1];
    const char *in_file_name = argv[2];
    const char *out_file_name = argv[3];

    if(strcmp(command, "encode") ==0){
        encode_file(in_file_name, out_file_name);
    }
    else{
        return 1;
    }

    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}