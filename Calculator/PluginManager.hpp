#pragma once

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <windows.h>
#include <iostream>

typedef double (*TypeFunc)(std::deque<double>);
typedef std::string(*NameFunc)();
typedef int (*CountOperands)();
using FunctionsMap = std::map<std::string, std::pair<TypeFunc, int>>; //NameFunc

class PluginManager {
private:
	FunctionsMap _available_functions;
	void LoadingAvailableLibraries();
	std::string GetPathDLL();
	void InitializationAvailableFunctions(std::string name_function, TypeFunc function, int count_operands);
public:
	PluginManager();

	FunctionsMap& GetAvailableFunctions();
	void SetAvailableFunctions(FunctionsMap new_available_functions);
};