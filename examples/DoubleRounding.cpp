#include <iostream>
//#define PI 3.141592
//#define abs(x) (((x) < 0) ? -(x) : (x))
const double PI = 3.141592;

bool doubleEqual(double a, double b, double eps = 1e-16)
{
	return abs(a - b) < eps;
}

double deg3(double x)
{
	std::cout << x << "\n";
	return x * x * x;
}

int main()
{
	double PI_2 = PI / 2;

	std::cout << "1 2 3 PI \n";
	double deg = 60.0;
	double rad = deg / 180 * PI;
	std::cout.precision(32);
	std::cout.operator<<(0.1 == 1.1 - 1);
	std::cout << (0.1 == (1.1 - 1)) << '\n';
	std::cout << 0.1 << ' ' << 1.1 << ' ' << 1.1 - 1 << '\n';
	return 0;
}