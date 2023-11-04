#pragma once

#include "CoreCalculator.hpp"
#include "PluginManager.hpp"

typedef double (*TypeFunc)(std::deque<double>);
typedef std::string(*NameFunc)();
using FunctionsMap = std::map<std::string, std::tuple<TypeFunc, int, int>>;

class Calculator {
private:
	std::unique_ptr<CoreCalculator> _core_calculator;
	std::unique_ptr<PluginManager> _plugin_manager;

public:
	Calculator();
	Calculator(Calculator const&) = delete;
	Calculator(Calculator&&) = delete;
	Calculator operator=(Calculator const&) = delete;
	Calculator operator=(Calculator&&) = delete;
	~Calculator();

	std::vector<std::string> TokenizeExpression(const std::string& input_expression);
	std::vector<std::string> ConvertToStandartForm(const std::vector<std::string>& tokens);
	std::stringstream ConvertToRPN(std::vector<std::string> tokens);

	void Solve(std::string input_expression);
};