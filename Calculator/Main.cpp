#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <regex>
#include <exception>
#include <sstream>
#include <functional>

#include "Calculator.hpp"
#include "CoreCalculator.hpp"

//std::map<std::string, int> priority_operations = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };
//std::map<std::string, bool> left_associativity_operations = { {"+", true}, {"-", true}, {"*", true}, {"/", true} };
//std::map<std::string, std::function<double(double, double)>> basic_operators = {
//	{"+", [](double x, double y) {return x + y; }},
//	{"-", [](double x, double y) {return x - y; }},
//	{"*", [](double x, double y) {return x * y; }},
//	{"/", [](double x, double y) {return x / y; }}
//};
//
//bool isOperator(std::string op) {
//	return (op == "+" || op == "-" || op == "*" || op == "/");
//}
//
//bool isLeftAssociative(std::string token) {
//	return left_associativity_operations[token];
//}
//
//bool PrioritySecondOpOverFirstOp(std::string op1, std::string op2) {
//	return priority_operations[op1] <= priority_operations[op2];
//}
//
//bool isFunction(std::string func) {
//	std::vector<std::string> available_functions = { "sin", "cos" };
//	for (auto function : available_functions) {
//		if (func == function) {
//			return true;
//		}
//	}
//	return false;
//}
//
//bool isNumber(std::string token) {
//	std::regex numberRegex("[+-]?([0-9]*[.])?[0-9]+");
//	return std::regex_match(token, numberRegex);
//}
//
//std::stringstream Convert(std::vector<std::string> input_string) {
//	std::stack<std::string> operator_stack;
//	std::queue<std::string> output_queue;
//	std::stringstream output_stringstream;
//
//	int i = 0;
//	while (i < input_string.size()) {
//		if (input_string.at(i) == "(") {
//			if (isNumber(input_string.at(i + 1)) || isFunction(input_string.at(i + 1)) || input_string.at(i+1) == "(") {
//				i++;
//				continue;
//			}
//			else {
//				input_string.insert(input_string.begin() + i + 1, "0");
//			}
//		}
//		i++;
//	}
//
//	if (input_string.at(0) == "-" || input_string.at(0) == "+") output_stringstream << "0 ";//output_queue.push("0");
//	for (std::string token : input_string) {
//		if (isNumber(token)) {
//			//output_queue.push(token);
//			output_stringstream << token + " ";
//		}
//		else if (isFunction(token))
//		{
//			operator_stack.push(token);
//		}
//		else {
//			if (isOperator(token)) {
//				while (!operator_stack.empty() &&
//					isOperator(operator_stack.top()) &&
//					(PrioritySecondOpOverFirstOp(token, operator_stack.top()) ||
//						(priority_operations[token] == priority_operations[operator_stack.top()] &&
//							isLeftAssociative(token)))) {
//					//output_queue.push(operator_stack.top());
//					output_stringstream << operator_stack.top() + " ";
//					operator_stack.pop();
//				}
//				operator_stack.push(token);
//			}
//			else if (token == "(") {
//				operator_stack.push(token);
//			}
//			else if (token == ")") {
//				while (!operator_stack.empty() && operator_stack.top() != "(") {
//					//output_queue.push(operator_stack.top());
//					output_stringstream << operator_stack.top() + " ";
//					operator_stack.pop();
//				}
//
//				try {
//					if (operator_stack.empty()) {
//						throw std::string{ "Incorrect expression: missing parenthesis" };
//					}
//					operator_stack.pop();
//				}
//				catch (const std::string& ex) {
//					std::cout << ex << std::endl;
//					std::exit(1);
//				}
//				if (!operator_stack.empty() && isFunction(operator_stack.top())) {
//					output_stringstream << operator_stack.top() + " ";
//					//output_queue.push(operator_stack.top());
//					operator_stack.pop();
//				}
//			}
//		}
//	}
//	while (!operator_stack.empty()) {
//		try {
//			if (operator_stack.top() == "(") {
//				throw std::string{ "Incorrect expression: missing parenthesis" };
//			}
//		}
//		catch (const std::string& ex) {
//			std::cout << ex << std::endl;
//			std::exit(1);
//		}
//		//output_queue.push(operator_stack.top());
//		output_stringstream << operator_stack.top() + " ";
//		operator_stack.pop();
//	}
//
//	//std::stringstream output_ss;
//	//while (!output_queue.empty()) {
//	//	output_ss << output_queue.front() << " ";
//	//	output_queue.pop();
//	//}
//	return output_stringstream;
//
//}
//
//std::vector<std::string> tokenizeExpression(std::string expression) {
//	std::vector<std::string> tokens;
//	std::string token = "";
//
//	for (char ch : expression) {
//		if (ch == ' ')
//			continue;
//
//		if (isdigit(ch)) {
//			token += ch;
//		}
//		else if (isalpha(ch)) {
//			token += ch;
//		}
//		else if (ch == '.' || ch == ',') {
//			token += ch;
//		}
//		else {
//			if (!token.empty()) {
//				tokens.push_back(token);
//				token = "";
//			}
//			tokens.push_back(std::string(1, ch));
//		}
//	}
//
//	if (!token.empty()) {
//		tokens.push_back(token);
//	}
//
//	return tokens;
//}
//
//std::string Calculate(std::stringstream& rpn) {
//	std::stack<std::string> calculating_stack;
//	std::string token;
//
//	while (rpn >> token) {
//		std::cout << token << std::endl;
//		if (isNumber(token)) {
//			calculating_stack.push(token);
//		}
//		else if (isOperator(token)) {
//			// проверка в ядре калькулятора
//			double interim_result;
//			double operand_2 = stod(calculating_stack.top());
//			calculating_stack.pop();
//			double operand_1 = stod(calculating_stack.top());
//			calculating_stack.pop();
//			interim_result = basic_operators[token](operand_1, operand_2);
//			calculating_stack.push(std::to_string(interim_result));
//		}
//		//else if (isFunction(token)) {
//
//		//}
//	}
//
//	return calculating_stack.top();
//}

int main() {
	////std::queue<std::string> tokens = tokenizeExpression("3*(-sin(0)+4)");
	//std::string input_string;
	//std::cin >> input_string;
	////std::queue<std::string> tokens = tokenizeExpression(input_string);
	//std::vector<std::string> tokens = tokenizeExpression(input_string);
	////while (!tokens.empty())
	////{
	////	v.emplace_back(std::move(tokens.front()));
	////	tokens.pop();
	////}
	//std::stringstream rpn = Convert(tokens);

	//std::string token;
	////while (rpn >> token) {
	////	std::cout << token << " ";
	////}
	//std::cout << Calculate(rpn) << std::endl;

	////while (!rpn.empty())
	////{
	////	v1.emplace_back(std::move(rpn.front()));
	////	rpn.pop();
	////}
	////for (auto elem : v1) {
	////	std::cout << elem << " ";
	////}

	Calculator calculator;
	std::string input_expression;
	std::cin >> input_expression;

	calculator.Solve(input_expression);

	return 0;
}
