// AssignmentA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

typedef unsigned long long int BIG_NUMBER;

BIG_NUMBER cmmdc_v1(BIG_NUMBER a, BIG_NUMBER b) {
    while (a != b)
        if (a > b)
            a -= b;
        else
            b -= a;
    return a;
}

BIG_NUMBER cmmdc_v2(BIG_NUMBER a, BIG_NUMBER b) {
    BIG_NUMBER r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

BIG_NUMBER cmmdc_v3(BIG_NUMBER a, BIG_NUMBER b) {
    BIG_NUMBER minimum_between_a_b = a;
    if (a < b)
        minimum_between_a_b = b;
    for (BIG_NUMBER divisor = minimum_between_a_b; divisor > 1; divisor--)
        if (a % divisor == 0 &&  b % divisor == 0)
            return divisor;
    return 1;
}

double getExecutionTime(BIG_NUMBER (*f) (BIG_NUMBER, BIG_NUMBER), BIG_NUMBER a, BIG_NUMBER b) {
    clock_t begin = clock();
    BIG_NUMBER rez = (*f)(a, b);
    clock_t end = clock();
    double time_taken = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("GCD: %I64u\n", rez);
    return time_taken;
}

BIG_NUMBER generate_random_BIG_NUMBER(BIG_NUMBER lower_bound, BIG_NUMBER upper_bound){
    return rand() % (upper_bound - lower_bound + (BIG_NUMBER)1) + lower_bound;
}

int main()
{
    srand(time(0));

    BIG_NUMBER a /* = 123456789*/;
    BIG_NUMBER b /* = 987654321*/;

    //printf("Input the first number: ");
    //scanf_s("%d", &a);

    //printf("Input the second number: ");
    //scanf_s("%d", &b);
    int number_of_inputs = 10;

    BIG_NUMBER lower_random_bound = 100000;
    BIG_NUMBER upper_random_bound = 100000;

    for (int i = 0; i < number_of_inputs; i++) {
        a = generate_random_BIG_NUMBER(lower_random_bound, upper_random_bound);
        b = generate_random_BIG_NUMBER(lower_random_bound, upper_random_bound);
        printf("For a=%I64u and b=%I64u:\n", a, b);
        printf("V1 finished in %lf seconds\n", getExecutionTime(cmmdc_v1, a, b));
        printf("V2 finished in %lf seconds\n", getExecutionTime(cmmdc_v2, a, b));
        //printf("V3 finished in %f s\n", getExecutionTime(cmmdc_v3, a, b));
        printf("--------------------------------------------\n");
        lower_random_bound *= 10;
        upper_random_bound *= 10;
    }
    
    return 0;
}