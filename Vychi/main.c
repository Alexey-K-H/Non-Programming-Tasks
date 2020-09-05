#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double equation(double x, double a, double b, double c){
    return x*x*x + a*x*x + b*x + c;
}

double find_discriminant(double a, double b, double c){
    return b*b - 4*a*c;
}

void swap(double *first, double *second){
    double tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}

void find_root_section(double a, double b, double c, double step, double e, double start_pos, double *l_bound, double *r_bound){
    int sign = (equation(start_pos, a, b, c) > 0 ? 1 : -1);

    while (1)
    {
        if(sign*equation(start_pos, a, b, c) < -e){
            *l_bound = start_pos - step;
            *r_bound = start_pos;
            break;
        } else{
            start_pos += step;
        }
    }
}

double find_root_in_section(double a, double b, double c, double e, double l_bound, double r_bound){
    double average;
    int sign_alpha = equation(l_bound, a, b, c) > 0 ? 1 : -1;
    int sign_betta = equation(r_bound, a, b, c) > 0 ? 1 : -1;

    if(sign_alpha == 1 || sign_betta == -1){
        while (1){
            average = (r_bound + l_bound)/2;

            if(fabs(equation(average, a, b, c)) < e){
                return average;
            } else if(equation(average, a, b, c) > e){
                l_bound = average;
            } else if(equation(average, a, b, c) < e){
                r_bound = average;
            }
        }
    } else{
        while (1){
            average = (r_bound + l_bound)/2;
            if(fabs(equation(average, a, b, c)) < e){
                return average;
            } else if(equation(average, a, b, c) > e){
                r_bound = average;
            } else if(equation(average, a, b, c) < e){
                l_bound = average;
            }
        }
    }
}



int main(int argc, char** argv) {
    if(argc != 4){
        printf("ERROR! You should enter 3 arguments: A, B and C for equation:\n");
        printf("EQUATION: x^3 + A*x^2 + B*x + C\n");
        return 1;
    }

    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    double c = strtod(argv[3], NULL);

    printf("EQUATION: x^3 + (%.0lf)*x^2 + (%.0lf)*x + (%.0lf)\n", a, b, c);

    double eps = 1e-03;
    double step = 0.09;
    double discriminant = find_discriminant(3, 2*a, b);

    if(discriminant > eps*eps){
        printf("Discriminant > 0\n");
        double alpha = (-2*a - sqrt(discriminant))/(2*3);
        double betta = (-2*a + sqrt(discriminant))/(2*3);

        if(betta < alpha){
            swap(&alpha, &betta);
        }

        //Границы отрезка, содержащего корень
        double l_bound = 0;
        double r_bound = 0;

        printf("f(betta) = %lf\n", equation(betta, a, b, c));
        printf("f(alpha) = %lf\n", equation(alpha, a, b, c));

        //f(alpha) > 0 & f(betta) > 0
        if(equation(alpha, a, b, c) > eps && equation(betta, a, b, c) > eps){
            printf("One root\n");
            find_root_section(a, b, c, -step, eps, alpha, &l_bound, &r_bound);
            double x = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            printf("x* = %.5lf\n", x);
        }

        //f(alpha) > 0 & f(betta) = 0
        if(equation(alpha, a, b, c) > eps && fabs(equation(betta, a, b, c)) < eps){
            printf("Two roots\n");
            find_root_section(a, b, c, -step, eps, alpha - eps, &l_bound, &r_bound);
            double x = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            printf("x1* = %.5lf\nx2* = %.5lf\n", x, betta);
        }

        //f(alpha) > 0 & f(betta) < 0
        if(equation(alpha, a, b, c) > eps && equation(betta, a, b, c) < -eps){
            printf("Three roots\n");

            find_root_section(a, b, c, -step, eps, alpha - eps, &l_bound, &r_bound);
            double x1 = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            find_root_section(a, b, c, step, eps, alpha + eps, &l_bound, &r_bound);
            double x2 = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            find_root_section(a, b, c, step, eps, betta + eps, &l_bound, &r_bound);
            double x3 = find_root_in_section(a, b, c, eps, l_bound, r_bound);

            printf("x1* = %.5lf\nx2* = %.5lf\nx3* = %.5lf\n", x1, x2, x3);
        }

        //f(alpha) = 0 & f(betta) < 0
        if(fabs(equation(alpha, a, b, c)) < eps && equation(betta, a, b, c) < -eps){
            printf("Two roots\n");
            find_root_section(a, b, c, step, eps, betta + eps, &l_bound, &r_bound);
            double x = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            printf("x1* = %.5lf\nx2* = %.5lf\n", alpha, x);
        }

        //f(alpha) < 0 & f(betta) < 0
        if(equation(alpha, a, b, c) < -eps && equation(betta, a, b, c) < eps){
            printf("One root\n");
            find_root_section(a, b, c, step, eps, betta + eps, &l_bound, &r_bound);
            double x = find_root_in_section(a, b, c, eps, l_bound, r_bound);
            printf("x* = %.5lf\n", x);
        }

        //f(alpha) = 0 && f(betta) = 0
        if(fabs(equation(alpha, a, b, c)) < eps && fabs(equation(betta, a, b, c)) < eps){
            printf("One root\n");
            printf("x* = %.5lf\n", alpha);
        }
    }
    else if(fabs(discriminant) < eps*eps || discriminant < -eps){
        printf("Discriminant <= 0\n");
        printf("One root\n");
        double x;

        if(fabs(equation(0, a, b, c)) < eps){
            x = 0;
        }
        else{
            double l_bound = 0;
            double r_bound = 0;

            if(equation(0, a, b, c) < eps){
                find_root_section(a, b, c, step, eps, 0, &l_bound, &r_bound);
            }
            else{
                find_root_section(a, b, c, -step, eps, 0, &l_bound, &r_bound);
            }
            x = find_root_in_section(a, b, c, eps, l_bound, r_bound);
        }

        printf("x* = %.5lf\n", x);

    }

    return 0;
}
