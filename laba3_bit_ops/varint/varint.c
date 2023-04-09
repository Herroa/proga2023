#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#define SIZE 10

/*
 * Диапазон             Вероятность
 * -------------------- -----------
 * [0; 128)             90%
 * [128; 16384)         5%
 * [16384; 2097152)     4%
 * [2097152; 268435455) 1%
 */
uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

void print_bin(unsigned char x){
    for(int i=0;i<8;i++){
        printf("%d", (x >> (7-i)) & 1);
    }
    printf("\n");
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int main()
{
    FILE *uncompressed;
    uncompressed = fopen("uncompressed.dat", "wb");
    uint32_t values[SIZE];
    for(int i = 0; i<SIZE; i++){
        values[i] = generate_number();
    }//fill array

    fwrite(values,sizeof(uint32_t),SIZE,uncompressed);
    //write file
    fclose(uncompressed);


    FILE *compressed;

    compressed = fopen("compressed.dat","wb");

    uint8_t buf[4];
    size_t size = 0;

    for (int i = 0; i<SIZE;i++){
        size = encode_varint(values[i], buf);
        fwrite(buf,sizeof(uint8_t),size,compressed);
    }
    fclose(compressed);
    return 0;
}