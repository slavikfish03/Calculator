#pragma once

#include <map>
#include <vector>
#include <string>
#include <windows.h>
#include <iostream>

typedef double (*TypeFunc)(std::vector<double>);
typedef std::string(*NameFunc)();
using FunctionsMap = std::map<std::string, TypeFunc>; //NameFunc

class PluginManager {
private:
	FunctionsMap _available_functions;
	void LoadingAvailableLibraries();
	std::string GetPathDLL();
	void InitializationAvailableFunctions(std::string name_function, TypeFunc function);
public:
	PluginManager();

	FunctionsMap& GetAvailableFunctions();
	void SetAvailableFunctions(FunctionsMap new_available_functions);
};