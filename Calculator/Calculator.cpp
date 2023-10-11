#include "Calculator.hpp"

Calculator::Calculator() {
	_plugin_manager = std::make_unique<PluginManager>();
	
	FunctionsMap available_functions = _plugin_manager->GetAvailableFunctions();

	_core_calculator = std::make_unique<CoreCalculator>(available_functions);
}

Calculator::~Calculator() {
	_core_calculator = nullptr;
	_plugin_manager = nullptr;
}

std::vector<std::string> Calculator::TokenizeExpression(std::string input_expression) {
	std::vector<std::string> tokens;
	std::string token = "";

	for (char ch : input_expression) {
		if (ch == ' ')
			continue;

		if (isdigit(ch)) {
			token += ch;
		}
		else if (isalpha(ch)) {
			token += ch;
		}
		else if (ch == '.' || ch == ',') {
			token += ch;
		}
		else {
			if (!token.empty()) {
				tokens.push_back(token);
				token = "";
			}
			tokens.push_back(std::string(1, ch));
		}
	}

	if (!token.empty()) {
		tokens.push_back(token);
	}

	return tokens;
}

std::vector<std::string> Calculator::ConvertToStandartForm(const std::vector<std::string>& tokens) {
	std::vector<std::string> new_tokens;
	int i = 0;

	while (i < tokens.size()) {
		if (tokens.at(i) == "(") {
			if (_core_calculator->isNumber(tokens.at(i + 1)) ||
				_core_calculator->isFunction(tokens.at(i + 1)) ||
				tokens.at(i + 1) == "(") 
			{
				new_tokens.push_back(tokens.at(i));
				i++;
				continue;
			}
			else {
				i++;
				new_tokens.push_back("(");
				new_tokens.push_back("0");
				continue;
			}
		}
		new_tokens.push_back(tokens.at(i));
		i++;
	}
	return new_tokens;
}

std::stringstream Calculator::ConvertToRPN(std::vector<std::string> tokens) {
	std::stack<std::string> operator_stack;
	std::stringstream output_stringstream;

	tokens = this->ConvertToStandartForm(tokens);

	if (tokens.at(0) == "-" || tokens.at(0) == "+") output_stringstream << "0 ";

	for (std::string token : tokens) {
		if (_core_calculator->isNumber(token)) {
			output_stringstream << token + " ";
		}
		//else if (_core_calculator->isFunction(token))
		//{
		//	//operator_stack.push(token);
		//		while (
		//			!operator_stack.empty() &&
		//			(_core_calculator->isOperator(operator_stack.top()) || _core_calculator->isFunction(operator_stack.top())) &&
		//			(_core_calculator->PrioritySecondOverFirst(token, operator_stack.top()) ||
		//				(_core_calculator->GetPriotityOperations()[token] == _core_calculator->GetPriotityOperations()[operator_stack.top()] &&
		//					_core_calculator->isLeftAssociative(token)
		//					)))
		//		{
		//			output_stringstream << operator_stack.top() + " ";
		//			operator_stack.pop();
		//		}
		//		operator_stack.push(token);
		//}
		else {
			if (_core_calculator->isOperator(token) || _core_calculator->isFunction(token)) {
				while (
					!operator_stack.empty() &&
					(_core_calculator->isOperator(operator_stack.top()) || _core_calculator->isFunction(operator_stack.top())) &&
					(_core_calculator->PrioritySecondOverFirst(token, operator_stack.top()) ||
					(_core_calculator->GetPriotityOperations()[token] == _core_calculator->GetPriotityOperations()[operator_stack.top()] &&
					_core_calculator->isLeftAssociative(token)))) 
				{
						output_stringstream << operator_stack.top() + " ";
						operator_stack.pop();
				}
				operator_stack.push(token);
			}
			else if (token == "(") {
				operator_stack.push(token);
			}
			else if (token == ")") {
				while (!operator_stack.empty() && operator_stack.top() != "(") {
					output_stringstream << operator_stack.top() + " ";
					operator_stack.pop();
				}

				try {
					if (operator_stack.empty()) {
						throw std::string{ "Incorrect expression : incorrect parenthesis order or missing parentheses." };
					}
					operator_stack.pop();
				}
				catch (const std::string& ex) {
					std::cout << ex << std::endl;
					return std::stringstream();
				}

				if (!operator_stack.empty() && _core_calculator->isFunction(operator_stack.top())) {
					output_stringstream << operator_stack.top() + " ";
					operator_stack.pop();
				}
			}
		}
	}
	while (!operator_stack.empty()) {
		try {
			if (operator_stack.top() == "(") {
				throw std::string{ "Incorrect expression: incorrect parenthesis order or missing parentheses" };
			}
		}
		catch (const std::string& ex) {
			std::cout << ex << std::endl;
			return std::stringstream();
		}
		output_stringstream << operator_stack.top() + " ";
		operator_stack.pop();
	}

	return output_stringstream;
}

void Calculator::Solve(std::string input_expression) {
	std::vector<std::string> tokens = TokenizeExpression(input_expression);
	std::stringstream rpn_expression = ConvertToRPN(tokens);
	std::string answer = _core_calculator->Calculate(rpn_expression);
	std::cout << "Solution: " << answer << std::endl;

}