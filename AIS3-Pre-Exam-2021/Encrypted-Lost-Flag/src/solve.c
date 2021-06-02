#include "matrix.h"
#include "config.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    // flag_enc * key = flag
    // banner_enc * key = banner
    // key = banner_enc_inv * banner
    Matrix* banner_m = InitMatrixString(size, banner);
    Matrix* banner_enc_m = InitMatrixString(size, banner_enc);
    Matrix* banner_enc_inv_m = MatrixInverse(banner_enc_m);
    PrintMatrixInlineHex(banner_enc_inv_m);
    Matrix* key_m = MatrixMultipy(banner_enc_inv_m, banner_m);
    Matrix* flag_enc_m = InitMatrixString(size, flag_enc);
    Matrix* flag_m = MatrixMultipy(flag_enc_m, key_m);
    puts(GetStr(flag_m));
}
