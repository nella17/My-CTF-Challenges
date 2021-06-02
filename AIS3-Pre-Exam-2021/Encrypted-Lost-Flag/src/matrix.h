#ifndef MATRIX_H_
#define MATRIX_H_

static const int mod = 257;
int extgcd(int a, int b, int *x, int *y);
int inverse(int x);

#define mset(m,i,j) (m->array[i*m->size+j])
#define mget(m,i,j) ((int)(m->array[i*m->size+j]))
typedef int MATRIX_TYPE;
struct Matrix {
    int size;
    MATRIX_TYPE* array;
};
typedef struct Matrix Matrix;

Matrix* InitMatrix(int size);
Matrix* InitMatrixString(int size, const unsigned char* str);
Matrix* InitMatrixIndex(int size);
Matrix* InitMatrixCopy(const Matrix* x);
Matrix* MatrixMultipy(const Matrix* a, const Matrix* b);
Matrix* MatrixInverse(const Matrix* x);
char* GetStr(const Matrix* m);

void PrintMatrix(Matrix* m, char* fmt, char c);
void PrintMatrixInline(Matrix* m);
void PrintMatrixInlineHex(Matrix* m);
void PrintMatrixPretty(Matrix* m);

Matrix* fpowM(const Matrix* _a, int b);
int MatrixSame(const Matrix* a, const Matrix* b);

#endif
