#include <iostream>
int main() {
	const int NUM_STATES = 4, NUM_INPUTS = 2;
	char inValue;
	int state = 0;
	int lookUp[NUM_STATES][NUM_INPUTS] = {0, 0, 0, 1, 0, 0, 0, 0};
	int statelookUp[NUM_STATES][NUM_INPUTS] = {1,3, 1, 2, 1, 0, 1, 0 };
	std::cin.get(inValue);
	std::cout << '0';
	while (inValue != '\n') {
		std::cout << lookUp[state][inValue - 'a'];
		state = statelookUp[state][inValue - 'a'];
		std::cin.get(inValue);
	}
	return 0;
}