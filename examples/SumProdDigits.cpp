#include <iostream>

int main(){
	unsigned int val;
	std::cout << "Input val: ";
	std::cin >> val;
	unsigned int sum = 0;
	unsigned int prod = 1; // wrong for val = 0
	unsigned int reverse = 0;
	unsigned int deg10 = 1;
	unsigned int val_copy = val;
	while (val_copy != 0) {
		unsigned int digit = val_copy % 10;
		sum += digit;
		prod *= digit;
		val_copy /= 10;
		reverse *= 10;
		reverse += digit;
		deg10 *= 10;
	}
	deg10 /= 10;
	val_copy = val;
	std::cout << "REVERSE:\n";
	while (true) {
		unsigned int digit = val_copy / deg10;
		val_copy %= deg10;
		deg10 /= 10;
		std::cout << digit;
		if (deg10 != 0) {
			std::cout << ", ";
		}
		else {
			std::cout << '\n';
			break;
		}
	}
	
	/*while (true) {
		unsigned int digit = reverse % 10;
		reverse /= 10;
		std::cout << digit;
		if (reverse != 0) {
			std::cout << ", ";
		}
		else {
			std::cout << '\n';
			break;
		}
	}*/
	std::cout << "sum  = " << sum << '\n';
	std::cout << "prod = " << prod << '\n';
	return 0;
}