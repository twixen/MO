#include <stdio.h>
#include <math.h>
double fdiff(double x, double y);
double f(double x);

int main() {
    double k;
    double euler = 0;
    double heun = 0;
    double x = 1;
    do {
        printf("Podaj krok całkowania z przedziału (0,1): ");
        scanf("%lf", &k);
        if (k <= 0 || k >= 1) printf("Niepoprawny krok\n");
    } while (k <= 0 || k >= 1);
    printf("      x        f(x)      euler       błąd       heun       błąd  \n");
    while (x + k <= 3) {
        euler += fdiff(x, euler) * k;
        heun += (fdiff(x, heun) + fdiff(x + k, heun + fdiff(x, heun) * k)) * k / 2;
        x += k;
        printf("%10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf\n", x, f(x), euler, fabs(euler - f(x)), heun, fabs(heun - f(x)));
    }
    return 0;
}

double fdiff(double x, double y) {
    return sqrt(y + x * x) + x * (4 * x * x - x - 2);
}

double f(double x) {
    return x * x * (x * x - 1);
}