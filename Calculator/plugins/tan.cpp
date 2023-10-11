#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef TAN_EXPORTS
#define TAN_API __declspec(dllexport)
#else
#define TAN_API __declspec(dllimport)
#endif

extern "C" TAN_API double function(std::deque<double> arguments_function) {
	return tan(arguments_function.at(0));
}

extern "C" TAN_API std::string name() {
	return "tan";
}

extern "C" TAN_API int countOperands() {
	return 1;
}

extern "C" TAN_API int priority() {
	return 3;
}