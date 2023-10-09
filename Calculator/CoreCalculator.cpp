#include "CoreCalculator.hpp"

CoreCalculator::CoreCalculator() {
	_priority_operations = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };
	_left_associativity_operations = { {"+", true}, {"-", true}, {"*", true}, {"/", true} };
	_basic_operators = {
		{"+", [](double x, double y) {return x + y; }},
		{"-", [](double x, double y) {return x - y; }},
		{"*", [](double x, double y) {return x * y; }},
		{"/", [](double x, double y) {return x / y; }}
	};
}

bool CoreCalculator::isOperator(std::string op) {
	return (op == "+" || op == "-" || op == "*" || op == "/");
}

bool CoreCalculator::isLeftAssociative(std::string token) {
	return _left_associativity_operations[token];
}

bool CoreCalculator::PrioritySecondOpOverFirstOp(std::string op1, std::string op2) {
	return _priority_operations[op1] <= _priority_operations[op2];
}

bool CoreCalculator::isFunction(std::string func) {
	std::vector<std::string> available_functions = { "sin", "cos" };
	for (auto function : available_functions) {
		if (func == function) {
			return true;
		}
	}
	return false;
}

bool CoreCalculator::isNumber(std::string token) {
	std::regex numberRegex("[+-]?([0-9]*[.])?[0-9]+");
	return std::regex_match(token, numberRegex);
}

std::string CoreCalculator::Calculate(std::stringstream& rpn_expression) {
	std::stack<std::string> calculating_stack;
	std::string token;

	while (rpn_expression >> token) {
		//std::cout << token << std::endl;
		if (isNumber(token)) {
			calculating_stack.push(token);
		}
		else if (isOperator(token)) {
			// проверка в ядре калькулятора
			double interim_result;
			double operand_2 = stod(calculating_stack.top());
			calculating_stack.pop();
			double operand_1 = stod(calculating_stack.top());
			calculating_stack.pop();
			interim_result = _basic_operators[token](operand_1, operand_2);
			calculating_stack.push(std::to_string(interim_result));
		}
		//else if (isFunction(token)) {

		//}
	}

	return calculating_stack.top();
}

/////////////////////

PriorityMap& CoreCalculator::GetPriotityOperations() {
	return _priority_operations;
}

AssociativityMap& CoreCalculator::GetLeftAssociativityOperations() {
	return _left_associativity_operations;
}

OperatorsMap& CoreCalculator::GetBasicOperators() {
	return _basic_operators;
}

void CoreCalculator::SetPriotityOperations(PriorityMap new_priotity_operations) {
	_priority_operations = new_priotity_operations;
}

void CoreCalculator::SetLeftAssociativityOperations(AssociativityMap new_left_associativity_operations) {
	_left_associativity_operations = new_left_associativity_operations;
}

void CoreCalculator::SetBasicOperators(OperatorsMap new_basic_operators) {
	_basic_operators = new_basic_operators;
}

