/*
����� �����������

����:
	���������:
		PluginManager pluginManager - ����� ��������� dll ��� ������������

������:
	Solve - �������� �����, ��������� �� main, ������������ ������� ���������
	ConvertToRPN(string& infix_expression) - ����� ����������� �� ��������� ������� � �������� ��������, 
	���������� ������ � �������� ��������
	Calculate - �����������, ���������� �� Solve

*/
#pragma once

#include "CoreCalculator.hpp"

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

class Calculator {
private:
	std::unique_ptr<CoreCalculator> _core_calculator;
	//std::vector<std::string> _current_tokens;
	//PluginManager plugin_manager;

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