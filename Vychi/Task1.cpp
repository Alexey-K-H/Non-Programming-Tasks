#include <iostream>
#include <cmath>

double f(double x, double a, double b, double c){
    return pow(x, 3) + a*pow(x, 2) + b*x + c;
}

double find_root(double a0, double b0, double eps, double a, double b, double c){
    double x;
    while((b0 - a0) / 2 > eps){
        x = (a0 + b0) / 2;
        if((f(a0, a, b, c) * f(x, a, b, c)) > 0) a0 = x;
        else b0 = x;
    }
    return x;
}

void find_roots(double a, double b, double c, double eps){
    double a0;
    double b0;

    double D = pow(2*a, 2) - 4*3*b;

    double alpha = (-2 - sqrt(D))/6;
    double betta = (-2 + sqrt(D))/6;

    double f_alpha = f(alpha, a, b, c);
    double f_betta = f(betta, a, b, c);

    std::cout << "alpha = " << alpha << std::endl;
    std::cout << "betta = " << betta << std::endl;

    std::cout << "f(alpha) = " << f_alpha << std::endl;
    std::cout << "f(betta) = " << f_betta << std::endl;

    a0 = alpha - 4;
    b0 = alpha;
    double x1 = find_root(a0, b0, eps, a, b, c);
    printf("X1 = %.5f\n", x1);

    a0 = alpha;
    b0 = betta;
    double x2 = find_root(a0, b0, eps, a, b, c);
    printf("X2 = %.5f\n", x2);

    a0 = betta;
    b0 = betta + 4;
    double x3 = find_root(a0, b0, eps, a, b, c);
    printf("X3 = %.5f\n", x3);
}

int main(int argc, char **argv) {
    if(argc != 4){
        std::cout << "Wrong number of arguments!" << std::endl;
        return 1;
    }

    double eps = 1e-3;

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);

    std::cout << "Current parameters values: a = " << a << "; b = " << b << "; c = " << c << ";" << std::endl;
    std::cout << "Current equation: f(x) = x^3 + (" << a << ")*x^2 + (" << b << ")*x + (" << c << ");" << std::endl;

    find_roots(a, b, c, eps);

    return 0;
}
