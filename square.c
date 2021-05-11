#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

double method_hord(double (*f)(double), double (*g)(double), double cur, double last, double eps) {
    double next = 0;
    double f_cur, f_last, f_next, f_eps;
    f_cur = f(cur) - g(cur); 
    f_last = f(last) - g(last);
    next = cur - f_cur * (last - cur) / (f_last - f_cur);
    f_next = f(next) - g(next);
    if (fabs(f_next) >= eps) {
        if (f_next > 0)
            next = method_hord(f, g, cur, next, eps);
        next = method_hord(f, g, next, last, eps);   
    }
    return next;
}

double rootc(double (*f)(double), double (*g)(double), double cur, double last, double eps, int* num) {
    double next = 0;
    double f_cur, f_last, f_next, f_eps;
    f_cur = f(cur) - g(cur); 
    f_last = f(last) - g(last);
    next = cur - f_cur * (last - cur) / (f_last - f_cur);
    (*num)++;
    f_next = f(next) - g(next);
    if (fabs(f_next) >= eps) {
        if (f_next > 0)
            next = rootc(f, g, cur, next, eps, num);
        next = rootc(f, g, next, last, eps, num);       
    }
    return next;
}

double method_trapec(double (*f)(double), double a, double b, int n) {
    double eps = (b - a)/n;
    double res = 0;
    for (double i = a + eps; i < b; i+=eps) 
        res += f(i) * eps;
    res += f(a)*eps*1/2 + f(b) * eps * 1/2;
    return res;
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double res = method_hord(f, g, a, b, eps1);
    return res;
}

double integral(double (*f)(double), double a, double b, double eps2) {
    int n = 10;
    double p = 1/3, res = 0;
    double In = method_trapec(f, a, b, n);
    double I2n = method_trapec(f, a, b, 2*n);
    while (fabs(I2n - In) >= eps2) {
        In = I2n;
        n *= 2;
        I2n = method_trapec(f, a, b, 2*n);
    }
    return I2n;
}

int main(int argc, char* argv[]) { //-help -root -integral
    int count = 1;
    double otvet, x0, xk, eps = 0.001, res;
    int cnst = 0;
    int n1 = 0, n2 = 0, check_c = 0, check_x = 0;
    if (argc > 1){
        if (strcmp(argv[count],"-help") == 0) {
            cnst = 1;
        }
        else if (strcmp(argv[count],"-root") == 0) {
            count++;
            cnst = 2;
        }
        else if (strcmp(argv[count],"-integral") == 0) {
            count++;
            cnst = 3;
        }
        else if (strcmp(argv[count],"-x") == 0 || strcmp(argv[count],"-c") == 0)
            cnst = 4;
        switch (cnst)
        {
        case 1:
            printf("\nAll key option, which you can use:\n\n");
            printf("-help - open help menu\n\n");
            printf("-c - add with square count of itterations\n");
            printf("-x - add with square points of intersection of lines\n\n");
            printf("Key for test function root and integral:\n");
            printf("-root - find x in the equation f(x) = g(x) on segment(segment should have root of this equation)\n");
            printf("Argc:\n");
            printf("1)f: 1(f1), 2(f2) or 3(f3)\n");
            printf("2)g: 1(f1), 2(f2) or 3(f3)\n");
            printf("3)a(start of the segment)\n");
            printf("4)b(end of the segment)\n");
            printf("5)eps(accuracy of the calculations)\n");
            printf("Example -root f1 f3 -1.5 15 0.01\n\n");
            printf("-integral - find integral of function on segment\n");
            printf("Argc:\n");
            printf("1)f: 1(f1), 2(f2) or 3(f3)\n");
            printf("2)a(start of the segment)\n");
            printf("3)b(end of the segment)\n");
            printf("4)eps(accuracy of the calculations)\n");
            printf("Example -integral f1 1.34 5.143 0.01\n");
            printf("\nYOU CAN WRITE ONLY ONE KEY OPTION IN COMMAND LINE(Expect -x and -c)\n\n");
            printf("If you want to start program, write ./(filename) with key option -c or -x or both\n\n");
            return 0;
        case 2: 
            if (argc < 7)
                printf("\nA few arguments\n\n");
            else if (argc > 7)
                printf("\nA lot of arguments\n\n");
            else {
                sscanf(argv[2],"%d", &n1);
                sscanf(argv[3],"%d", &n2);
                sscanf(argv[4], "%lf", &x0);
                sscanf(argv[5], "%lf", &xk);
                sscanf(argv[6], "%lf", &eps);
                printf("x = ");
                if (n1 == 1 && n2 == 1)
                    printf("%lf\n",root(f1, f1, x0, xk, eps));
                if (n1 == 1 && n2 == 2)
                    printf("%lf\n",root(f1, f2, x0, xk, eps));
                if (n1 == 1 && n2 == 3)
                    printf("%lf\n",root(f1, f3, x0, xk, eps));
                if (n1 == 2 && n2 == 1)
                    printf("%lf\n",root(f1, f2, x0, xk, eps));
                if (n1 == 2 && n2 == 2)
                    printf("%lf\n",root(f2, f2, x0, xk, eps));
                if (n1 == 2 && n2 == 3)
                    printf("%lf\n",root(f2, f3, x0, xk, eps));
                if (n1 == 3 && n2 == 1)
                    printf("%lf\n",root(f1, f3, x0, xk, eps));
                if (n1 == 3 && n2 == 2)
                    printf("%lf\n",root(f2, f3, x0, xk, eps));
                if (n1 == 3 && n2 == 3)
                    printf("%lf\n",root(f3, f3, x0, xk, eps));
            } 
            return 0;
        case 3:
            if (argc < 6)
                printf("\nA few arguments\n\n");
            else if (argc > 6)
                printf("\nA lot of arguments\n\n");
            else {
                sscanf(argv[2],"%d", &n1);
                sscanf(argv[3], "%lf", &x0);
                sscanf(argv[4], "%lf", &xk);
                sscanf(argv[5], "%lf", &eps);
                printf("Integral = ");
                if (n1 == 1)
                    printf("%lf\n",integral(f1, x0, xk, eps));
                if (n1 == 2)
                    printf("%lf\n",integral(f1, x0, xk, eps));
                if (n1 == 3)
                    printf("%lf\n",integral(f1, x0, xk, eps));
            }
            return 0;
        case 4:
            break;
        default:
            printf("\nWrong key option\n\n");
            return 0;
        }
    }
    while (argc != 1) {
        if (strcmp(argv[argc - 1],"-x") == 0) 
            check_x = 1;
        else if (strcmp(argv[argc - 1],"-c") == 0)
            check_c = 1;
        argc--;
    }
    printf("Write the segment on which the area of this shape is located:\n[a, b] (Example: -10 10)\n");
    scanf("%lf %lf",&x0, &xk);
    res = integral(f1, root(f1, f3, x0, xk, eps),root(f1, f2, x0, xk, eps), eps);
    res -= integral(f3, root(f1, f3, x0, xk, eps),root(f2, f3, x0, xk, eps), eps);
    res -= integral(f2, root(f2, f3, x0, xk, eps),root(f1, f2, x0, xk, eps), eps);
    printf("\nSquare = %lf\n", res);
    if (check_x == 1) {
        printf("\n");
        printf("Func1 intersects Func2 in x = %lf\n", root(f1, f2, -10, 10, 0.001));
        printf("Func1 intersects Func3 in x = %lf\n", root(f1, f3, -10, 10, 0.001));
        printf("Func2 intersects Func3 in x = %lf\n", root(f2, f3, -10, 10, 0.001));
    }
    if (check_c == 1) {
        int num = 0;
        printf("\n");
        rootc(f1, f2, x0, xk, eps, &num);
        printf("Count itteration to find x for Func1 and Func2 = %d\n", num);
        num = 0;
        rootc(f1, f3, x0, xk, eps, &num);
        printf("Count itteration to find x for Func1 and Func3 = %d\n", num);
        num = 0;
        rootc(f2, f3, x0, xk, eps, &num);
        printf("Count itteration to find x for Func2 and Func3 = %d\n", num);
    }
    return 0;
}