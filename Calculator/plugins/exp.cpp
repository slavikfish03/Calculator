#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef EXP_EXPORTS
#define EXP_API __declspec(dllexport)
#else
#define EXP_API __declspec(dllimport)
#endif

extern "C" EXP_API double function(std::deque<double> arguments_function) {
	return exp(arguments_function.at(0));
}

extern "C" EXP_API std::string name() {
	return "exp";
}

extern "C" EXP_API int countOperands() {
	return 1;
}

extern "C" EXP_API int priority() {
	return 3;
}