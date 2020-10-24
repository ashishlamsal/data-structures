#include <iostream>

int fibonacci(int n) {
    if (n == 0 || n == 1) 
        return n;
    else 
        return fibonacci(n - 1) + fibonacci(n - 2);
}

void fiboiter(int count)
{
    long long int a = 0 ,b = 1, c;
    for (int i = 0; i < count; i++){
        std::cout << a << " ";
        c = a + b;
        a = b;
        b = c;
    }
    std::cout << "\n";
}

int main()
{
    int count = 50; // first 10 fibonacci numbers i.e. F0 - F9
    // for (int i = 0; i < count; i++)
    //     std::cout << fibonacci(i) << " ";   // ith term fibonacci F0, F1, ... Fn
    // std::cout << "\n";

    fiboiter(count);
    return 0;
}