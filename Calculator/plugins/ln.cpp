#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef LN_EXPORTS
#define LN_API __declspec(dllexport)
#else
#define LN_API __declspec(dllimport)
#endif

extern "C" LN_API double function(std::deque<double> arguments_function) {
	return log(arguments_function.at(0));
}

extern "C" LN_API std::string name() {
	return "ln";
}

extern "C" LN_API int countOperands() {
	return 1;
}

extern "C" LN_API int priority() {
	return 3;
}