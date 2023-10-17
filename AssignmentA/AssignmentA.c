// AssignmentA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stddef.h>

typedef unsigned long long int BIG_NUMBER;

//Repetitive substractions
//Time Complexity: O(max(a,b)) 
BIG_NUMBER cmmdc_v1(BIG_NUMBER a, BIG_NUMBER b) {
    while (a != b)
        if (a > b)
            a -= b;
        else
            b -= a;
    return a;
}

//Euclid
//Time Complexity: O(log(a) + log(b)) = O(n)
BIG_NUMBER cmmdc_v2(BIG_NUMBER a, BIG_NUMBER b) {
    BIG_NUMBER r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

//Product divided by 
//Time complexity: O(min(a,b))
BIG_NUMBER cmmdc_v3(BIG_NUMBER a, BIG_NUMBER b) {
    BIG_NUMBER greater = max(a, b);
    BIG_NUMBER smallest = min(a, b);
    for (BIG_NUMBER i = greater; ; i += greater) {
        if (i % smallest == 0)
            return a*b / i ;
    }
}

long double getExecutionTime(BIG_NUMBER (*gcd) (BIG_NUMBER, BIG_NUMBER), BIG_NUMBER a, BIG_NUMBER b) {
    LARGE_INTEGER start_time, end_time, frequency;
    /* `QueryPerformanceFrequency(&frequency);` is a function call that retrieves the frequency of the
    performance counter. The performance counter is a high-resolution timer that can be used to
    measure the execution time of a function or a piece of code. The frequency value returned by
    this function represents the number of ticks per second of the performance counter. */
    QueryPerformanceFrequency(&frequency);
    /* `QueryPerformanceCounter(&start_time);` is a function call that retrieves the current value of
    the performance counter. By calling
    `QueryPerformanceCounter` before and after the function execution, we can calculate the
    difference between the two values to determine the execution time. */
    QueryPerformanceCounter(&start_time);
    BIG_NUMBER rez = gcd(a, b);
    QueryPerformanceCounter(&end_time);

    /* This line of code calculates the execution time of a function or a piece of code. */
    long double time_taken = (long double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;


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

    BIG_NUMBER lower_random_bound = 1;
    BIG_NUMBER upper_random_bound = 100000000;

    for (int i = 0; i < number_of_inputs; i++) {
        a = generate_random_BIG_NUMBER(lower_random_bound, upper_random_bound);
        b = generate_random_BIG_NUMBER(lower_random_bound, upper_random_bound);
        printf("For a=%I64u and b=%I64u:\n", a, b);
        printf("V1 finished in %.10lf seconds\n", getExecutionTime(cmmdc_v1, a, b));
        printf("V2 finished in %.10lf seconds\n", getExecutionTime(cmmdc_v2, a, b));
        printf("V3 finished in %.10lf seconds\n", getExecutionTime(cmmdc_v3, a, b));
        printf("--------------------------------------------\n");
        lower_random_bound *= 10;
        upper_random_bound *= 10;
    }
    
    return 0;
}