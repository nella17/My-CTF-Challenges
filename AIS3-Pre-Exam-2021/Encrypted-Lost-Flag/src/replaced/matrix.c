#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"

int extgcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int g = extgcd(b, a%b, y, x);
    *y -= (a/b)**x;
    return g;
}
int inverse(int x) {
    int u, v;
    int g = extgcd(x, mod, &u, &v);
    assert(g == 1);
    if (u < mod) u += mod;
    return u;
}

______* Init______(int size) {
    ______* m = (______*)malloc(sizeof(______));
    m->size = size;
    size_t sz = sizeof(MATRIX_TYPE)*size*size;
    m->array = (MATRIX_TYPE*)malloc(sz);
    memset(m->array, 0, sz);
    return m;
}
______* Init______String(int size, const unsigned char* str) {
    ______* m = Init______(size);
    for(int i = 0; i < size*size && str[i]; i++)
        m->array[i] = str[i];
    return m;
}
______* Init______Index(int size) {
    ______* m = Init______(size);
    for(int i = 0; i < size; i++)
        mset(m,i,i) = 1;
    return m;
}
______* Init______Copy(const ______* x) {
    int size = x->size;
    ______* m = Init______(size);
    memcpy(m->array, x->array, sizeof(MATRIX_TYPE)*size*size);
    return m;
}

______* ______Multipy(const ______* a, const ______* b) {
    assert(a->size == b->size);
    int size = a->size;
    ______* m = Init______(size);
    for(int i = 0; i < size; i++)
        for(int k = 0; k < size; k++)
            for(int j = 0; j < size; j++)
                mset(m,i,j) = (mget(m,i,j) + mget(a,i,k) * mget(b,k,j)) % mod;
    return m;
}

______* ______Inverse(const ______* _x) {
    ______* x = Init______Copy(_x);
    int size = x->size;
    ______* m = Init______Index(size);
    for(int i = 0; i < size; i++) {
        {
            int j = i;
            while (j < size && mget(x,j,i) == 0) j++;
            if (j == size) {
                fprintf(stderr, "inverse matrix not exist\n");
                return NULL;
            }
            for(int k = 0; k < size; k++) {
                MATRIX_TYPE t = mget(x,i,k);
                mset(x,i,k) = mget(x,j,k);
                mset(x,j,k) = t;
            }
        }
        {
            int inv = inverse(mget(x,i,i));
            assert(inv > 0);
            for(int j = 0; j < size; j++) {
                mset(x,i,j) = mget(x,i,j) * inv % mod;
                mset(m,i,j) = mget(m,i,j) * inv % mod;
            }
        }
        for(int j = 0; j < size; j++) if (j != i) {
            int mul = mget(x,j,i);
            for(int k = 0; k < size; k++) {
                mset(x,j,k) = (mget(x,j,k) + mod - mul*mget(x,i,k)%mod) % mod;
                mset(m,j,k) = (mget(m,j,k) + mod - mul*mget(m,i,k)%mod) % mod;
            }
        }
    }
    free(x);
    return m;
}
char* GetStr(const ______* m) {
    size_t size = m->size;
    char* str = (char*)malloc(sizeof(char)*(size*size+1));
    str[0] = 0;
    for(int i = 0; i < size*size && m->array[i]; i++) {
        str[i] = m->array[i];
        str[i+1] = 0;
    }
    return str;
}

void Print______(______* m, char* fmt, char c) {
    int size = m->size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            printf(fmt, mget(m,i,j), i, j);
        printf("%c", c);
    }
}
void Print______Inline(______* m) {
    Print______(m, "%c", '\0');
    puts("");
}
void Print______InlineHex(______* m) {
    printf("\"");
    Print______(m, "\\x%02x", '\0');
    printf("\"\n");
}
void Print______Pretty(______* m) {
    puts("-------");
    Print______(m, "%3u ", '\n');
    puts("-------");
}

int fpow(int a, int b) {
    int r = 1;
    for(a %= mod; b; b >>= 1) {
        if (b&1) r = r*a%mod;
        a = a*a%mod;
    }
    return r;
}
______* fpowM(const ______* _a, int b) {
    ______* a = Init______Copy(_a);
    ______* r = Init______Index(a->size);
    ______* ptr;
    for(; b; b >>= 1) {
        if (b&1) {
            ptr = ______Multipy(r,a);
            free(r);
            r = ptr;
        }
        ptr = ______Multipy(a,a);
        free(a);
        a = ptr;
    }
    return r;
}

int ______Same(const ______* a, const ______* b) {
    if (a->size != b->size) return 0;
    return memcmp(a->array, b->array, sizeof(MATRIX_TYPE)*a->size*b->size) == 0;
}

#ifdef TEST
int main() {
    printf("%d %d\n", fpow(2,5), fpow(2,10));

    int x, y, g;
    g = extgcd(2,3,&x,&y);
    assert(g == 1 && x == -1 && y == 1);
    assert(inverse(5)*5%mod == 1);

    char* sa = "Hello ______!qwq0qwqw_wq_qw_wqwq";
    char* sb = "YAY this ______!.qq.._.._..?=_=.";
    int sz = 5;

    ______* a = Init______String(sz, sa);
    ______* b = Init______String(sz, sb);
    ______* c = ______Multipy(a,b);
    Print______Inline(a);
    Print______Inline(b);
    Print______InlineHex(c);

    // a*b = c
    // a = c*invb
    // b = inva*c

    ______* inva = ______Inverse(a);
    ______* invb = ______Inverse(b);
    Print______Pretty(______Multipy(a,inva));
    Print______Pretty(______Multipy(b,invb));

    ______* aa = ______Multipy(c,invb);
    Print______Inline(aa);
    ______* bb = ______Multipy(inva,c);
    Print______Inline(bb);

    // ______* t = Init______String(4, "\xe4\x91\x66\xea\x81\xba\xe1\xe7\xf1\xf7\x6a\xda\x00\x00\x00\x00");
}
#endif
