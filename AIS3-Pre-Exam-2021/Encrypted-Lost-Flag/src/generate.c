#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int size = 6;
const char* flag   = "AIS3{Matr1x_c4n_encry6t_an9_d3crypt}";
const char* key    = "matrix_multiplication_can_use_everywhere";
const char* banner = "How do you inverse faster pow calc!!";
const char* fail_banner = "Oops, your key is wrong:(";
const char* config_c_fmt = R"(
static int size = %d;
static const char* banner = "%s";
static const char* fail_banner = "%s";
static const unsigned char* banner_enc = "%s";
static const unsigned char* flag_enc   = "%s";
)";

char* ToHex(unsigned char* str, int len) {
    char* out = malloc(sizeof(char)*len*4+1);
    for(int i = 0; i < len; i++)
        sprintf(out+4*i, "\\x%02x", str[i]);
    return out;
}

int main() {
    assert(strlen(banner) <= size*size);
    assert(strlen(flag) <= size*size);
    assert(strlen(key) <= size*size+sizeof(int)/sizeof(char));

    Matrix* flag_m = InitMatrixString(size, flag);
    Matrix* banner_m = InitMatrixString(size, banner);

    Matrix* key_m = InitMatrixString(size, key);
    int pow = *(int*)(key+strlen(key)-sizeof(int)/sizeof(char));
    assert(pow > 0);
    Matrix* keypow = fpowM(key_m,pow);
    Matrix* keypow_inv = MatrixInverse(keypow);
    PrintMatrixPretty(MatrixMultipy(keypow,keypow_inv));

    // flag_enc * keypow = flag
    // flag * keypow_inv = flag_enc
    // banner_enc * keypow = banner
    // banner * keypow_inv = banner_enc
    Matrix* flag_enc_m = MatrixMultipy(flag_m,keypow_inv);
    Matrix* banner_enc_m = MatrixMultipy(banner_m,keypow_inv);

    assert(MatrixSame(flag_m,MatrixMultipy(flag_enc_m,keypow)));

    char* flag_enc = ToHex(GetStr(flag_enc_m), size*size);
    char* banner_enc = ToHex(GetStr(banner_enc_m), size*size);

    char* config_c = NULL;
    asprintf(&config_c, config_c_fmt, size, banner, fail_banner, banner_enc, flag_enc);
    puts(config_c);
    FILE* fp = fopen("config.c", "w");
    fputs(config_c, fp);

}
