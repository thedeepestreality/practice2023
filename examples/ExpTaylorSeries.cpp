#include <iostream>
#include <cmath>

int main(){
	double x;
	double eps;
	std::cout << "Input x: ";
	std::cin >> x;
	std::cout << "Input eps: ";
	std::cin >> eps;
	double sum = 0.0;
	double val = 1.0;
	int counter = 1;
	while (std::abs(val) >= eps){
		sum += val;
		val *= x/counter++;
	}
	std::cout << "eps(x) = " << std::exp(x) << "\n";
	std::cout << "row(x) = " << sum << "\n";
	return 0;
}