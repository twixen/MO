#include <stdio.h>
#include <math.h>
#include <string.h>
double f(double x);
double df(double x);
void bisection(double a, double b, double e);
void newton(double x, double e);

int main() {
  double a, b, e;
  int status; 
  char chce_podac_x[2];
  do {
    printf("Podaj a: ");
    scanf("%lf", &a);
    printf("Podaj b: ");
    scanf("%lf", &b);
    if(a < b) {
      if (f(a) * f(b) < 0) {
        do {
          printf("Podaj przybliżenie: ");
          status = scanf("%lf", &e);
          if(e > 0 && e < 1) {
            bisection(a, b, e);
            newton(a, e);
          }
          do {
            printf("Chcesz podać kolejne przybliżenie? (tak/nie): ");
            scanf("%s", chce_podac_x);
            if(strcmp(chce_podac_x, "tak") == 0 || strcmp(chce_podac_x, "nie") == 0) break;
          } while(1);
        } while (strcmp(chce_podac_x, "tak") == 0);	
      } else {
        printf("błąd: f(a) i f(b) muszą mieć różny znak\n");
      }	
    } else {
      printf("błąd: a musi być mniejsze od b\n");
    }
  } while(a >= b || f(a) * f(b) >= 0);

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
  printf("Metoda połowienia:\n");
  printf("x = %.16lf, f(x) = %.16lf, Kroki: %d\n", m, fm, step);
}

void newton(double x, double e) {
  int step = 0;
  while (fabs(f(x)) > e) {
    x -= f(x) / df(x);
    step += 1;
  }
  printf("Metoda Newtona:\n");
  printf("x = %.16lf, f(x) = %.16lf, Kroki: %d\n", x, f(x), step);
}
