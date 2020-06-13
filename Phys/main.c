#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double U0 = 1;
double hPlank = 1;
double m = 1;
double a;

double F1(double E){
    return tan((sqrt(2*m*(E+U0))*a)/(2*hPlank)) - 1.0/(sqrt((U0/fabs(E)) - 1));
}

double F2(double E){
    return (1.0/tan((sqrt(2*m*(E+U0))*a)/(2*hPlank))) - 1.0/(sqrt((U0/fabs(E)) - 1));
}

double FindRoot(double (*f)(double), double e1, double e2, double eps){
    double c;
    while(fabs(e2 - e1) / 2 > eps){
        c = (e1 + e2) / 2;
        if((f(e1) * f(c)) > 0) e1=c;
        else e2=c;
    }
    return c;
}

double FindCoefficient(double curr_E, int parity, FILE* out){
    double coefficient;
    fprintf(out, "Coefficient between C and B\n");
    double k1 = sqrt(2*m*(curr_E + U0))/hPlank;
    if(parity){
        coefficient = cos((a / 2) * k1) / exp((-a / 2) * k1 * tan((a / 2) * k1));
        fprintf(out, "C = %.5lf*B\n", coefficient);
    }
    else{
        coefficient = sin((a / 2) * k1) / exp((-a / 2) * k1 * (1.00 / tan((a / 2) * k1)));
        fprintf(out, "C = %.5lf*B\n", coefficient);
    }

    return coefficient;
}

void BuildGraph(double coefficient, double curr_E, int parity, double b, FILE* out){
    double x_values[51];
    double y_values[51];

    double k1 = sqrt(2*m*(curr_E + U0))/hPlank;

    for(int i = 0; i < 51; i++){
        x_values[i] = b + i*0.2;

        if(parity){
            if(x_values[i] < a/2 && x_values[i] > -a/2){
                y_values[i] = cos(k1*x_values[i]);
            }
            else{
                if(x_values[i] < -(a/2)){
                    y_values[i] = coefficient * (exp((x_values[i]) * k1 * tan(k1 * (a / 2))));
                } else if(x_values[i] > (a/2)){
                    y_values[i] = coefficient * (exp((-x_values[i]) * k1 * tan(k1 * (a / 2))));
                }
            }
        }
        else{
            if(x_values[i] < a/2 && x_values[i] > -a/2){
                y_values[i] = sin(k1*x_values[i]);
            }
            else{
                if(x_values[i] < -(a/2)){
                    y_values[i] = -coefficient * (exp((x_values[i]) * k1 * (1.0 / tan(k1 * (a / 2)))));
                } else if(x_values[i] > (a/2)){
                    y_values[i] = coefficient * (exp((-x_values[i]) * k1 * (1.0 / tan(k1 * (a / 2)))));
                }
            }
        }
    }

    fprintf(out, "Values function:\n");
    if(parity){
        fprintf(out, "Even functions:\n");
    } else{
        fprintf(out, "Odd functions:\n");
    }

    for(int i = 0; i < 51; i++){
        fprintf(out, "x[%d]:%.2lf\t", i, x_values[i]);
    }
    fprintf(out, "\n");

    for(int i = 0; i < 51; i++){
        fprintf(out, "y[%d]:%.2lf\t", i, y_values[i]);
    }
    fprintf(out, "\n\n");
}

int main(){

    FILE *out;

    out = fopen("output.txt", "w");
    if(out == NULL){
        printf("Cannot open file!\n");
        return 0;
    }

    char num_str[20];
    printf("Enter a:");
    fgets(num_str, 20, stdin);
    a = strtod(num_str, NULL);

    fprintf(out, "Current a: %lf\n\n", a);

    double e1,e2,eps,x;
    eps = pow(10, -8);
    e1 = -1.0;
    e2 = -0.9;

    //Границы области построения
    double b = -5;
    double coefficient;

    while(e2 < 0){
        if(F1(e1) * F1(e2) < 0){
            x=FindRoot(F1, e1, e2, eps);
            fprintf(out, "Even solution:Interval[%.1f;%.1f] Solution:E = %.5f\n", e1, e2, x);
            coefficient = FindCoefficient(x, 1, out);
            BuildGraph(coefficient, x, 1, b, out);
        }

        if(F2(e1) * F2(e2) < 0){
            x=FindRoot(F2, e1, e2, eps);
            fprintf(out, "Odd solution:Interval[%.1f;%.1f] Solution:E = %.5f\n", e1, e2, x);
            coefficient = FindCoefficient(x, 0, out);
            BuildGraph(coefficient, x, 0, b, out);
        }

        e2 += 0.1;
        e1 += 0.1;
    }

    return 0;
}