#include <stdio.h>

int Fibo_Recursion(int n)
{
    if (n < 2)
        return n;
    return Fibo_Recursion(n - 1) + Fibo_Recursion(n - 2);
}

int Fibo_TopDown(int n, int* arr)
{
    if (arr[n] != -1)
        return arr[n];

    if (n < 2)
        arr[n] = n;
    else
        arr[n] = Fibo_TopDown(n - 1, arr) + Fibo_TopDown(n - 2, arr);

    return arr[n];
}

int Fibo_BottomUp(int n)
{
    if (n < 2)
        return n;

    int* arr = new int[n + 1];
    arr[0] = 0;
    arr[1] = 1;

    for (int i = 2; i < n + 1; ++i)
        arr[i] = arr[i - 1] + arr[i - 2];

    return arr[n];
}


int main()
{
    int n = 20;
    int* arr = new int[n + 1];
    for (int i = 0; i < n + 1; ++i)
        arr[i] = -1;

    printf("1. %d\n", Fibo_Recursion(n));
    printf("2. %d\n", Fibo_TopDown(n, arr));
    printf("3. %d\n", Fibo_BottomUp(n));

    getchar();
}