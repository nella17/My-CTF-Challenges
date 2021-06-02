#ifndef MATRIX_H_
#define MATRIX_H_

static const int mod = 257;
int extgcd(int a, int b, int *x, int *y);
int inverse(int x);

#define mset(m,i,j) (m->array[i*m->size+j])
#define mget(m,i,j) ((int)(m->array[i*m->size+j]))
typedef int MATRIX_TYPE;
struct ______ {
    int size;
    MATRIX_TYPE* array;
};
typedef struct ______ ______;

______* Init______(int size);
______* Init______String(int size, const unsigned char* str);
______* Init______Index(int size);
______* Init______Copy(const ______* x);
______* ______Multipy(const ______* a, const ______* b);
______* ______Inverse(const ______* x);
char* GetStr(const ______* m);

void Print______(______* m, char* fmt, char c);
void Print______Inline(______* m);
void Print______InlineHex(______* m);
void Print______Pretty(______* m);

______* fpowM(const ______* _a, int b);
int ______Same(const ______* a, const ______* b);

#endif
