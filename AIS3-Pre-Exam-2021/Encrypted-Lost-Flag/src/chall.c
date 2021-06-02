#include "matrix.h"
#include "config.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix* decrypt(const unsigned char* enc, char* key) {
    int pow = *(int*)(key+strlen(key)-sizeof(int)/sizeof(char));
    Matrix* enc_m = InitMatrixString(size,enc);
    Matrix* key_m = InitMatrixString(size,key);
    Matrix* dec = MatrixMultipy(enc_m,fpowM(key_m,pow));
    return dec;
}

int main() {
    char* key = (char*)malloc(sizeof(char)*(size*size+5));
    scanf("%s", key);
    Matrix* banner_m = InitMatrixString(size, banner);
    Matrix* banner_dec = decrypt(banner_enc, key);
    if (!MatrixSame(banner_m, banner_dec)) {
        puts(fail_banner);
    } else {
        puts(GetStr(banner_dec));
        printf("flag is: %s\n", GetStr(decrypt(flag_enc, key)));
    }
    return 0;
}
