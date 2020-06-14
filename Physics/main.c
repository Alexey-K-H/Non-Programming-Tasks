#include <stdio.h>
#include <math.h>

double U0 = 1;
double hPlank = 1;
double m = 1;
double a;
double B;

double F1(double E){
    return tan((sqrt(2*m*(E+U0))*a)/(2*hPlank)) - 1.0/(sqrt((U0/fabs(E)) - 1));
}

double F2(double E){
    return (-1.0/tan((sqrt(2*m*(E+U0))*a)/(2*hPlank))) - 1.0/(sqrt((U0/fabs(E)) - 1));
}

double FindRoot(double (*f)(double), double e1, double e2, double eps){
    double c;
    while((e2 - e1) / 2 > eps){
        c = (e1 + e2) / 2;
        if((f(e1) * f(c)) > 0) e1=c;
        else e2=c;
    }
    return c;
}

double FindCoeffitient(double curr_E, int chetnost){
    double coeffitient;
    double k1 = sqrt(2*m*(curr_E + U0))/hPlank;
    if(chetnost){
        coeffitient = cos((a/2)*k1)/exp((-a/2)*k1*tan((a/2)*k1));
    }
    else{
        coeffitient = sin(-(a/2)*k1)/exp((a/2)*k1*(1.00/tan((a/2)*k1)));
    }

    return coeffitient;
}

void BuildGraph(double coeffitient, double curr_E, int chetnost, double b, FILE *out, FILE *valOut){
    double x_values[81];
    double y_values[81];

    double k1 = sqrt(2*m*(curr_E + U0))/hPlank;
    //fprintf(out, "k1:%lf\n", k1);
    //double k2;

    for(int i = 0; i < 81; i++){
        x_values[i] = b + i*0.25;

        if(chetnost){
            if(x_values[i] < a/2 && x_values[i] > -a/2){
                y_values[i] = cos(k1*x_values[i]);
            }
            else{
                if(x_values[i] < -(a/2)){
                    y_values[i] = coeffitient*(exp((x_values[i])*k1*tan(k1*(a/2))));
                } else if(x_values[i] > (a/2)){
                    y_values[i] = coeffitient*(exp((-x_values[i])*k1*tan(k1*(a/2))));
                }
            }
            //k2 = k1*tan(k1*(a/2));
            //fprintf(out, "k2:%lf\n", k2);
        }
        else{
            if(x_values[i] < a/2 && x_values[i] > -a/2){
                y_values[i] = sin(k1*x_values[i]);
            }
            else{
                if(x_values[i] < -(a/2)){
                    y_values[i] = -coeffitient*(exp((-x_values[i])*k1*(1.0/tan(k1*(a/2)))));
                } else if(x_values[i] > (a/2)){
                    y_values[i] = coeffitient*(exp((x_values[i])*k1*(1.0/tan(k1*(a/2)))));
                }
            }
            //k2 = -k1*(1.0/tan(k1*(a/2)));
            //fprintf(out, "k2:%lf\n", k2);
        }

        //fprintf(out, "B:%lf\n", B);
        //fprintf(out, "C:%lf\n", B*coeffitient);
    }

    fprintf(out, "Значения функций:\n");
    if(chetnost){
        fprintf(out, "Четные функции:\n");
        fprintf(valOut, "Chet func\n");
    } else{
        fprintf(out, "Нечетные функции:\n");
        fprintf(valOut, "Nechet func\n");
    }

    for(int i = 0; i < 81; i++){
        fprintf(out, "x[%d]:%.2lf\t", i, x_values[i]);
    }
    fprintf(out, "\n");

    for(int i = 0; i < 81; i++){
        fprintf(out, "y[%d]:%.2lf\t", i, y_values[i]);
        fprintf(valOut, "%lf\n", y_values[i]);
    }
    fprintf(out, "\n\n");
    fprintf(valOut, "\n\n");
}

int main(){
    FILE *out;
    out = fopen("output.txt", "w");

    FILE *valOut;
    valOut = fopen("valOut.xls", "w");

    if(out == NULL || valOut == NULL){
        printf("Cannot open file!\n");
        return 0;
    }

    printf("Enter a:");
    scanf("%lf", &a);
    fprintf(out, "Current a: %lf\n\n", a);

    printf("Enter B:");
    scanf("%lf", &B);

    double e1,e2,eps,x;
    eps = pow(10, -8);
    e1 = -1.0;
    e2 = -0.99;

    int count_levels = 0;

    double b = -10;
    double coeff;

    while(e2 < 0){
        if(F1(e1) * F1(e2) < 0){
            x=FindRoot(F1, e1, e2, eps);
            coeff = FindCoeffitient(x, 1);
            if(coeff == FP_NAN || isinf(coeff)){
            } else{
                fprintf(out,"Четное решение:Interval[%.3f;%.3f]:E = %.5f\n", e1, e2, x);
                BuildGraph(coeff, x, 1, b, out, valOut);
                count_levels++;
            }
        }

        if(F2(e1) * F2(e2) < 0){
            x=FindRoot(F2, e1, e2, eps);
            coeff = FindCoeffitient(x, 0);
            if(coeff == FP_NAN || isinf(coeff)){
            } else{
                fprintf(out, "Нечетное решение:Interval[%.3f;%.3f]:E = %.5f\n", e1, e2, x);
                BuildGraph(coeff, x, 0, b, out, valOut);
                count_levels++;
            }
        }

        e2 += 0.01;
        e1 += 0.01;

    }

    fprintf(out, "Count_levels:%d\n", count_levels);

    return 0;
}

