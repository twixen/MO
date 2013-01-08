#include <stdio.h>
#include <math.h>
double fdifferential(double x, double y);
double f(double x);

int main() {
    double k;
    double euler = 0;
    double heun = 0;
    double x = 1;
    scanf("%lf", &k);
    while (x < 3) {
        euler += fdifferential(x, euler) * k;
        heun += (fdifferential(x, heun) + fdifferential(x + k, heun + fdifferential(x, heun) * k)) * k / 2;
        x += k;
        printf("%10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf\n", x, f(x), euler, fabs(euler - f(x)), heun, fabs(heun - f(x)));
    }
    return 0;
}

double fdifferential(double x, double y) {
    return sqrt(y + x * x) + x * (4 * x * x - x - 2);
}

double f(double x) {
    return x * x * (x * x - 1);
}