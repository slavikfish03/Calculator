#include "CoreCalculator.hpp"

CoreCalculator::CoreCalculator(FunctionsMap& available_functions) {
	_available_functions = available_functions;

	_priority_operations = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };

	// adding priorities of loaded functions
	for (const auto& func : _available_functions) {
		_priority_operations[func.first] = std::get<2>(func.second);
	}
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

bool CoreCalculator::PrioritySecondOverFirst(std::string op1, std::string op2) {
	return _priority_operations[op1] <= _priority_operations[op2];
}

bool CoreCalculator::isFunction(std::string func) {
	return (_available_functions.count(func));
}

bool CoreCalculator::isNumber(std::string token) {
	std::regex numberRegex("[+-]?([0-9]*[.])?[0-9]+");
	return std::regex_match(token, numberRegex);
}

std::deque<double> CoreCalculator::BuildArgumentsFunction(int count_operands, std::stack<std::string>& calculating_stack) {
	std::deque<double> args;
	double operand;
	for (int i = 0; i < count_operands; i++) {
		operand = stod(calculating_stack.top());
		calculating_stack.pop();
		args.push_front(operand);
	}
	return args;
}

std::string CoreCalculator::Calculate(std::stringstream& rpn_expression) {
	std::stack<std::string> calculating_stack;
	std::string token;
	
	if (rpn_expression.str().empty()) return std::string("Error");

	while (rpn_expression >> token) {
		if (isNumber(token)) {
			calculating_stack.push(token);
		}
		else if (isOperator(token)) {
			try {
				if (calculating_stack.empty() || calculating_stack.size() == 1) {
					throw std::string{ "Incorrect expression: Function arguments are missing or invalid characters are entered" };
				}
				double operand_2 = stod(calculating_stack.top());
				calculating_stack.pop();
				double operand_1 = stod(calculating_stack.top());
				calculating_stack.pop();
				double interim_result = _basic_operators[token](operand_1, operand_2);
				calculating_stack.push(std::to_string(interim_result));
			}
			catch (const std::string& ex) {
				std::cout << ex << std::endl;
				return std::string("Error");
			}
		}
		else if (isFunction(token)) {
			int count_operands = std::get<1>(_available_functions[token]);

			try {
				if (calculating_stack.empty()) {
					throw std::string{ "Incorrect expression: Function arguments are missing or invalid characters are entered" };
				}
			}
			catch (const std::string& ex) {
				std::cout << ex << std::endl;
				return std::string("Error");
			}

			std::deque<double> args = BuildArgumentsFunction(count_operands, calculating_stack);

			double interim_result = std::get<0>(_available_functions[token])(args);
			calculating_stack.push(std::to_string(interim_result));
		}
	}

	double result = stod(calculating_stack.top());
	
	try {
		if (std::isinf(result) || std::isnan(result)) {
			throw std::string{ "Incorrect expression: Incorrect value of function arguments or an attempt to divide by zero" };
		}
	}
	catch (const std::string& ex) {
		std::cout << ex << std::endl;
		return std::string("Error");
	}

	return calculating_stack.top();
}

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

