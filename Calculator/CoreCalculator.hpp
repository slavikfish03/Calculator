#pragma once

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

using PriorityMap = std::map<std::string, int>;
using AssociativityMap = std::map<std::string, bool>;
using OperatorsMap = std::map<std::string, std::function<double(double, double)>>;

class CoreCalculator {
private:
	PriorityMap _priority_operations;
	AssociativityMap _left_associativity_operations;
	OperatorsMap _basic_operators;
	//available_function

public:
	CoreCalculator();

	bool isOperator(std::string op);
	bool isLeftAssociative(std::string op);
	bool PrioritySecondOpOverFirstOp(std::string op1, std::string op2);
	bool isFunction(std::string op);
	bool isNumber(std::string token);

	std::string Calculate(std::stringstream& rpn_expression);

	PriorityMap& GetPriotityOperations();
	AssociativityMap& GetLeftAssociativityOperations();
	OperatorsMap& GetBasicOperators();

	void SetPriotityOperations(PriorityMap new_priotity_operations);
	void SetLeftAssociativityOperations(AssociativityMap new_left_associativity_operations);
	void SetBasicOperators(OperatorsMap new_basic_operators);
};