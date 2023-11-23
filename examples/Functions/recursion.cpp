#include <iostream>

long long factorial(int n){
    if (n < 2)
        return 1;
    return n*factorial(n-1);
}

int fibonacci(unsigned int n){
    if (n < 2)
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{

    return 0;
}