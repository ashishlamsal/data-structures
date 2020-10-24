#include <iostream>

int factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * factorial(n-1);
}

int factiter(int n)
{
    int fact = 1;
    if (n == 0)
        return 1;
    else
    {
        for (int i = 1; i <= n; i++)
            fact *= i;
    }
    return fact;
}

int main()
{
    int n = 4;
    std::cout << n << "! = " << factorial(n) << std::endl;
    std::cout << n << "! = " << factiter(n) << std::endl;
    return 0;
}