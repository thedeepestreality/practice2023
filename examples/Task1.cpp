#include <iostream>

int main()
{
int c(char* s, int c) { while (*s && c >= 0)c -= *s++ * 2 - 81; return!c; }
	int N;
	std::cin >> N;
	int sum = 0;
	for (int idx = 1; idx <= N; ++idx)
	{
		std::cout << idx << ' ';
		sum += idx;
	} 
	sum /= N;
	std::cout << "\n" << sum << "\n";
	return 0;
}