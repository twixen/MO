#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 100

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
    printf("Wynik: W(x) = ");
    while (--i) {
        printf("%lf", t[i][n]);
        printf("x^%d + ", i);
    }
    printf("%lfx^0\n", t[0][n]);
}

int main() {
    double *A, **t, x0;
    int i, n;
    char chce_podac_x[2];

	do {
        printf("Podaj liczbę naturalną z przedziału od 0 do %d: ", N_MAX);
    	scanf("%d", &n);	
    } while(n < 0 || n > N_MAX);
    
  	n += 1;
    A = malloc(n * sizeof (double));
    for (i = 0; i < n; i++) {
        printf("Podaj A[%d]: ", i);
        scanf("%lf", &A[i]);
    }
    t = malloc(n * sizeof (double*));
    for (i = 0; i < n; i++) {
        t[i] = malloc((n + 1) * sizeof (double));
    }

    do {
		printf("Podaj X0: ");    
		scanf("%lf", &x0);
        clearMatrix(n, t, A);
        fillMatrix(n, t, x0);
        resolveMatrix(n, t);
        printPolynomial(n, t);
        
       	do {
			printf("Chcesz podać kolejne X0? (tak/nie): ");
			scanf("%s", chce_podac_x);
			if(strcmp(chce_podac_x, "tak") == 0 || strcmp(chce_podac_x, "nie") == 0) break;
       	} while(1);

    } while (strcmp(chce_podac_x, "tak") == 0);
    
    return 0;
}
