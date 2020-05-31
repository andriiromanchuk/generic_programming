#include "utils.h"

int sum_int(int a, int b) {
    return a + b;
}

double sum_double(double a, double b) {
    return a + b;
}

#define MAKE_SUM(type) \
    type sum_##type(type a, type b) { \
        return a + b; \
    }

//MAKE_SUM(int)
//MAKE_SUM(double)


// Overloading
int osum(int a, int b) {
    return a + b;
}

double osum(double a, double b) {
    return a + b;
}

template <typename T>
T sum(T a, T b) {
    LOG;

    return a + b;
}

int main() {
    int x = 4;
    int y = 3;
    double d = 8.8;
    double b = 3.3;

    sum_int(x, y);
    sum_double(d, b);

    osum(x, y);
    osum(d, b);

    //osum(x, d);

    // explicit type argument
    sum<int>(x, 7);
    sum<double>(d, b);

    // changed type argument
    sum<double>(x, y);

    // explicit template usage
    sum<>(x, y);
    // type deduction
    sum(x, y);

    // arguments with different types
    //sum(x, d);
    sum(static_cast<double>(x), d);
    sum<double>(x, d);

    return 0;
}
