#include "math_functions.h"
int own::abs(int x) {
    return x > 0 ? x : -x;
}
double own::abs(double x) {
    return x > 0 ? x : -x;
}
int own::trunc(double x) {
    return (int)x;
}
double own::sin(double x) {
    double pi = 3.1415926535897932;
    if (x >= 0 && x <= pi/4) {
        double res = 0, increment = x, accuracy = 1e-10, i = 1;
        while (abs(increment) >= accuracy) {
            res += increment;
            increment *= (-1)*x*x/(i + 1)/(i + 2);
            i += 2;
        }
        return res;
    } else if (x > pi/4 && x <= pi/2) return cos(pi/2 - x);
    else if (x > pi/2 && x <= pi) return sin(pi - x);
    else if (x > pi && x < 2*pi) return -sin(2*pi - x);
    else if (x > 2*pi) return sin(x - 2*pi*trunc(x/2/pi));
    else return -sin(x);
}
double own::cos(double x) {
    double pi = 3.1415926535897932;
    if (x >= 0 && x <= pi/4) {
        double res = 0, increment = 1, accuracy = 1e-10, i = 0;
        while (abs(increment) >= accuracy) {
            res += increment;
            increment *= (-1)*x*x/(i + 1)/(i + 2);
            i += 2;
        }
        return res;
    } else if (x > pi/4 && x <= pi/2) return sin(pi/2 - x);
    else if (x > pi/2 && x <= pi) return -cos(pi - x);
    else if (x > pi && x < 2*pi) return cos(2*pi - x);
    else if (x > 2*pi) return cos(x - 2*pi*trunc(x/2/pi));
    else return cos(x);
}
double own::exp(double x) {
    double mult = 2.718281828459045;
    double val1 = 1, val2 = 0;
    int whole_part = trunc(x);
    double frac_part = x - whole_part;
    while (whole_part) {
        if (whole_part % 2 == 0) {
            mult *= mult;
            whole_part /= 2;
        } else {
            if (whole_part < 0) {
                val1 /= mult;
                ++whole_part;
            } else {
                val1 *= mult;
                --whole_part;
            }
        }
    }
    double accuracy = 0.0000001, i = 0, increment = 1;
    while (abs(increment) >= accuracy) {
        val2 += increment;
        increment *= frac_part/(++i);
    }
    return val1*val2;
}
double own::ln(double a) {
    double x = 10, decrement = 1, accuracy = 1e-13, reload_val = 10;
    bool set = false;
    while (abs(decrement) >= accuracy) {
        decrement = 1 - a/exp(x);
        x -= decrement;
        if (x >= 709 && !set) {
            x = reload_val += 20;
            decrement = 1;
        } else set = true;
    }
    return x;
}
double own::pow(double x, double a) {
    return exp(a*ln(x));
}
double own::sqrt(double x) {
    if (x == 0) return 0;
    double first_sqrts[] = {0,
                            1,
                            1.414213562373,
                            1.7320508075688,
                            2,
                            2.2360679774997,
                            2.4494897427831,
                            2.6457513110645,
                            2.8284271247461,
                            3,
                            3.1622776601683};
    int exp = 0;
    double num = x;
    while (num > 10) {
        num /= 10;
        exp += 1;
    }
    double a = exp % 2 ? first_sqrts[9]*first_sqrts[trunc(num)] : first_sqrts[trunc(num)];
    for (int i = 0; i < exp/2; ++i) a *= 10;
    double r = x - a*a, residue = r/2/a, accuracy = 1e-6;
    while (abs(x - (a + residue)*(a + residue)) >= accuracy) {
        residue = r/(2*a + residue);
    }
    return a + residue;
}
