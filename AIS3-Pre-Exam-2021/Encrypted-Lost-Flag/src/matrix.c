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

Matrix* InitMatrix(int size) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->size = size;
    size_t sz = sizeof(MATRIX_TYPE)*size*size;
    m->array = (MATRIX_TYPE*)malloc(sz);
    memset(m->array, 0, sz);
    return m;
}
Matrix* InitMatrixString(int size, const unsigned char* str) {
    Matrix* m = InitMatrix(size);
    for(int i = 0; i < size*size && str[i]; i++)
        m->array[i] = str[i];
    return m;
}
Matrix* InitMatrixIndex(int size) {
    Matrix* m = InitMatrix(size);
    for(int i = 0; i < size; i++)
        mset(m,i,i) = 1;
    return m;
}
Matrix* InitMatrixCopy(const Matrix* x) {
    int size = x->size;
    Matrix* m = InitMatrix(size);
    memcpy(m->array, x->array, sizeof(MATRIX_TYPE)*size*size);
    return m;
}

Matrix* MatrixMultipy(const Matrix* a, const Matrix* b) {
    assert(a->size == b->size);
    int size = a->size;
    Matrix* m = InitMatrix(size);
    for(int i = 0; i < size; i++)
        for(int k = 0; k < size; k++)
            for(int j = 0; j < size; j++)
                mset(m,i,j) = (mget(m,i,j) + mget(a,i,k) * mget(b,k,j)) % mod;
    return m;
}

Matrix* MatrixInverse(const Matrix* _x) {
    Matrix* x = InitMatrixCopy(_x);
    int size = x->size;
    Matrix* m = InitMatrixIndex(size);
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
char* GetStr(const Matrix* m) {
    size_t size = m->size;
    char* str = (char*)malloc(sizeof(char)*(size*size+1));
    str[0] = 0;
    for(int i = 0; i < size*size && m->array[i]; i++) {
        str[i] = m->array[i];
        str[i+1] = 0;
    }
    return str;
}

void PrintMatrix(Matrix* m, char* fmt, char c) {
    int size = m->size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            printf(fmt, mget(m,i,j), i, j);
        printf("%c", c);
    }
}
void PrintMatrixInline(Matrix* m) {
    PrintMatrix(m, "%c", '\0');
    puts("");
}
void PrintMatrixInlineHex(Matrix* m) {
    printf("\"");
    PrintMatrix(m, "\\x%02x", '\0');
    printf("\"\n");
}
void PrintMatrixPretty(Matrix* m) {
    puts("-------");
    PrintMatrix(m, "%3u ", '\n');
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
Matrix* fpowM(const Matrix* _a, int b) {
    Matrix* a = InitMatrixCopy(_a);
    Matrix* r = InitMatrixIndex(a->size);
    Matrix* ptr;
    for(; b; b >>= 1) {
        if (b&1) {
            ptr = MatrixMultipy(r,a);
            free(r);
            r = ptr;
        }
        ptr = MatrixMultipy(a,a);
        free(a);
        a = ptr;
    }
    return r;
}

int MatrixSame(const Matrix* a, const Matrix* b) {
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

    char* sa = "Hello Matrix!qwq0qwqw_wq_qw_wqwq";
    char* sb = "YAY this Matrix!.qq.._.._..?=_=.";
    int sz = 5;

    Matrix* a = InitMatrixString(sz, sa);
    Matrix* b = InitMatrixString(sz, sb);
    Matrix* c = MatrixMultipy(a,b);
    PrintMatrixInline(a);
    PrintMatrixInline(b);
    PrintMatrixInlineHex(c);

    // a*b = c
    // a = c*invb
    // b = inva*c

    Matrix* inva = MatrixInverse(a);
    Matrix* invb = MatrixInverse(b);
    PrintMatrixPretty(MatrixMultipy(a,inva));
    PrintMatrixPretty(MatrixMultipy(b,invb));

    Matrix* aa = MatrixMultipy(c,invb);
    PrintMatrixInline(aa);
    Matrix* bb = MatrixMultipy(inva,c);
    PrintMatrixInline(bb);

    // Matrix* t = InitMatrixString(4, "\xe4\x91\x66\xea\x81\xba\xe1\xe7\xf1\xf7\x6a\xda\x00\x00\x00\x00");
}
#endif
