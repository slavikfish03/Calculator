#include "Calculator.hpp"

int main() {
	std::cout << "Enter an expression or type 'Exit' to exit: " << std::endl;

	Calculator calculator;
	std::string input_expression;
	bool isInput = true;

	while (isInput) {
		std::getline(std::cin, input_expression);
		if (input_expression == "Exit" || input_expression == "exit") {
			isInput = false;
			break;
		}
		calculator.Solve(input_expression);
	}

	return 0;
}
