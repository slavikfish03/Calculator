#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef SIN_EXPORTS
#define SIN_API __declspec(dllexport)
#else
#define SIN_API __declspec(dllimport)
#endif

extern "C" SIN_API double function(std::deque<double> arguments_function) {
	return sin(arguments_function.at(0));
}

extern "C" SIN_API std::string name() {
	return "sin";
}

extern "C" SIN_API int countOperands() {
	return 1;
}

extern "C" SIN_API int priority() {
	return 3;
}