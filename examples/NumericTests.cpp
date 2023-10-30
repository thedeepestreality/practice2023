#include <iostream>
#include <ctime>

int main()
{
    double x;
    int n;
    std::cout << "Input x: ";
    std::cin >> x;
    std::cout << "Input n: ";
    std::cin >> n;

    double sum = 0;
    clock_t start = clock();
    for (int idx = 1; idx <= n; ++idx)
        sum += std::pow(-1, idx - 1) * std::pow(x, idx) / idx;
    clock_t end = clock();
    std::cout << sum << " " << std::log(1 + x) << "\n";
    std::cout << "Elapsed time: " << (double)(end - start)/CLOCKS_PER_SEC << "\n";

    sum = 0;
    double xPower = x;
    start = clock();
    for (int idx = 1; idx <= n; ++idx) {
        sum += xPower / idx;
        xPower *= -x;
    }
    end = clock();
    std::cout << sum << " " << std::log(1 + x) << "\n";
    std::cout << "Elapsed time: " << (double)(end - start) / CLOCKS_PER_SEC << "\n";

    system("pause"); 
    return 0;
}