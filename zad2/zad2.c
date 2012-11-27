#include <stdio.h>
#include <math.h>
double f(double x);
double df(double x);
void bisection(double a, double b, double e);
void newton(double x, double e);

int main() {
    double a, b, e;
    scanf("%lf%lf", &a, &b);
    if (a < b && f(a) * f(b) < 0) {
        while (scanf("%lf", &e) == 1) {
            bisection(a, b, e);
            newton(a, e);
        }
    }
    return 0;
}

double f(double x) {
    return exp(x) + x + 2;
}

double df(double x) {
    return exp(x) + 1;
}

void bisection(double a, double b, double e) {
    double m = (a + b) / 2;
    double fm = f(m);
    int step = 0;
    while (fabs(fm) > e) {
        if ((f(a) * fm) < 0) {
            b = m;
        } else if ((f(b) * fm) < 0) {
            a = m;
        }
        m = (a + b) / 2;
        fm = f(m);
        step += 1;
    }
    printf("%.16lf %.16lf %d\n", m, fm, step);
}

void newton(double x, double e) {
    int step = 0;
    while (fabs(f(x)) > e) {
        x -= f(x) / df(x);
        step += 1;
    }
    printf("%.16lf %.16lf %d\n", x, f(x), step);
}
