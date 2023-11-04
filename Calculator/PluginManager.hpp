#pragma once

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <tuple>
#include <windows.h>
#include <iostream>

typedef double (*TypeFunc)(std::deque<double>);
typedef std::string(*NameFunc)();
typedef int (*CountOperands)();
typedef int (*Priority)();


using FunctionsMap = std::map<std::string, std::tuple<TypeFunc, int, int>>;

class PluginManager {
private:
	FunctionsMap _available_functions;
	void LoadingAvailableLibraries();
	std::string GetPathDLL();
	void InitializationAvailableFunctions(std::string name_function, TypeFunc function, int count_operands, int priority);
public:
	PluginManager();

	FunctionsMap& GetAvailableFunctions();
};