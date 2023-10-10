#pragma once

#include "CoreCalculator.hpp"
#include "PluginManager.hpp"

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
#include <memory>
#include <format>

typedef double (*TypeFunc)(std::vector<double>);
typedef std::string(*NameFunc)();
using FunctionsMap = std::map<std::string, TypeFunc>;

class Calculator {
private:
	std::unique_ptr<CoreCalculator> _core_calculator;
	//std::vector<std::string> _current_tokens;
	std::unique_ptr<PluginManager> _plugin_manager;
	FunctionsMap _available_functions;

public:
	Calculator();
	Calculator(Calculator const&) = delete;
	Calculator(Calculator&&) = delete;
	Calculator operator=(Calculator const&) = delete;
	Calculator operator=(Calculator&&) = delete;
	~Calculator();

	std::vector<std::string> TokenizeExpression(std::string input_expression);
	std::vector<std::string> ConvertToStandartForm(const std::vector<std::string>& tokens);
	std::stringstream ConvertToRPN(std::vector<std::string> tokens);

	void Solve(std::string input_expression);
};