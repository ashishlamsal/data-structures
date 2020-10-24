// 3. factorial for given number ‘n’ using tail recursion
#include <iostream>

int factorial(int n, int accumulator = 1)
{
    if (n == 0)
        return accumulator;
    else
        return factorial(n - 1, n * accumulator);
}

int main()
{
    int n;
    std::cout << "Enter a number : ";
    std::cin >> n;
    std::cout << n << "! = " << factorial(n) << std::endl;
    return 0;
}