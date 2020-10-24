// 4. Fibonacci number for given term ‘n’ using tail recursion
#include <iostream>

int fibonacci(int n, int a = 0, int b = 1) {
    if (n == 0)
        return a;
    if (n == 1)
        return b;
    else
        return fibonacci(n - 1, b, a + b);
}

int main()
{
    int n;
    std::cout << "Enter a number : ";
    std::cin >> n;
    std::cout << "F" << n << " = " << fibonacci(n) << std::endl;
    return 0;
}