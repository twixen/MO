#include <stdio.h>
#include <stdlib.h>

double MyPow(double x0, int exp) {
    return exp > 0 ? MyPow(x0, exp - 1) * x0 : 1;
}

void fillMatrix(int n, double **t, double x0) {
    int i, j;
    for (j = 0; j < n; j++) {
        t[0][j] = 1;
        for (i = 1; i < n; i++) {
            if (i + j < n)t[i][j] = t[i - 1][j] * (n - i - j);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i + j < n)t[i][j] *= MyPow(x0, n - j - i - 1);
        }
    }
}

void resolveMatrix(int n, double **t) {
    int i, j;
    for (i = n - 1; i >= 0; i--) {
        t[i][n] /= t[i][n - i - 1];
        for (j = 0; j < i; j++) {
            t[j][n] -= t[j][n - i - 1] * t[i][n] ;
        }
    }
}

void printMatrix(int n, double **t) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            printf("%lf ", t[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void clearMatrix(int n, double **t, double *A) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            t[i][j] = 0;
        }
        t[i][n] = A[i];
    }
}

void printPolynomial(int n, double **t) {
    int i = n;
    printf("W(x) = ");
    while (--i) {
        printf("%lf", t[i][n]);
        printf("x^%d + ", i);
    }
    printf("%lfx^0", t[0][n]);
}

int main() {
    double *A, **t, x0;
    int i, n;
    scanf("%d", &n);
    n += 1;
    A = malloc(n * sizeof (double));
    for (i = 0; i < n; i++) {
        scanf("%lf", &A[i]);
    }
    t = malloc(n * sizeof (double*));
    for (i = 0; i < n; i++) {
        t[i] = malloc((n + 1) * sizeof (double));
    }
    while (scanf("%lf", &x0) == 1) {
        clearMatrix(n, t, A);
        fillMatrix(n, t, x0);
        resolveMatrix(n, t);
        printPolynomial(n, t);
    }
    return 0;
}