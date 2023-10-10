#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <regex>
#include <exception>
#include <sstream>
#include <functional>

typedef double (*TypeFunc)(std::deque<double>);
typedef std::string(*NameFunc)();

using PriorityMap = std::map<std::string, int>;
using AssociativityMap = std::map<std::string, bool>;
using OperatorsMap = std::map<std::string, std::function<double(double, double)>>;
using FunctionsMap = std::map<std::string, std::pair<TypeFunc, int>>;

class CoreCalculator {
private:
	PriorityMap _priority_operations;
	AssociativityMap _left_associativity_operations;
	OperatorsMap _basic_operators;
	FunctionsMap _available_functions;

public:
	CoreCalculator(FunctionsMap& available_functions);

	bool isOperator(std::string op);
	bool isLeftAssociative(std::string op);
	bool PrioritySecondOpOverFirstOp(std::string op1, std::string op2);
	bool isFunction(std::string op);
	bool isNumber(std::string token);

	std::deque<double> BuildArgumentsFunction(int count_operands, std::stack<std::string>& calculating_stack);

	std::string Calculate(std::stringstream& rpn_expression);

	PriorityMap& GetPriotityOperations();
	AssociativityMap& GetLeftAssociativityOperations();
	OperatorsMap& GetBasicOperators();

	void SetPriotityOperations(PriorityMap new_priotity_operations);
	void SetLeftAssociativityOperations(AssociativityMap new_left_associativity_operations);
	void SetBasicOperators(OperatorsMap new_basic_operators);
};