#include <iostream>

int main()
{
	// pre-condition loop
	int counter = 5;
	while (counter < 5)
		std::cout << counter++ << "\n";

	//post-condition loop
	do
	{
		std::cout << counter++ << "\n";
	}
	while (counter < 5);

	int sum = 0;
	for (int idx = 0; idx < 5; ++idx) {
		if (idx == 2)
			continue;
		if (idx == 3)
			break;
		sum += idx;
		std::cout << idx << "\n";
	}

	//old visual studio
	//system("pause");
	return 0;
}