#include <stdio.h>

/* CHUC NANG 6: Ham de quy tinh lai kep P * (1 + r)^n */
double tinhLaiKep(double P, double r, int n) {
    if (n == 0) {
        return P; /* Dieu kien dung de quy */
    }
    return tinhLaiKep(P * (1 + r), r, n - 1); /* Goi de quy cho ky tiep theo */
}