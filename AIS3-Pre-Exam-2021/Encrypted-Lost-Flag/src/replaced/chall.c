#include "matrix.h"
#include "config.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

______* decrypt(const unsigned char* enc, char* key) {
    int pow = *(int*)(key+strlen(key)-sizeof(int)/sizeof(char));
    ______* enc_m = Init______String(size,enc);
    ______* key_m = Init______String(size,key);
    ______* dec = ______Multipy(enc_m,fpowM(key_m,pow));
    return dec;
}

int main() {
    char* key = (char*)malloc(sizeof(char)*(size*size+5));
    scanf("%s", key);
    ______* banner_m = Init______String(size, banner);
    ______* banner_dec = decrypt(banner_enc, key);
    if (!______Same(banner_m, banner_dec)) {
        puts(fail_banner);
    } else {
        puts(GetStr(banner_dec));
        printf("flag is: %s\n", GetStr(decrypt(flag_enc, key)));
    }
    return 0;
}
