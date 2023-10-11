#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef SQRT_EXPORTS
#define SQRT_API __declspec(dllexport)
#else
#define SQRT_API __declspec(dllimport)
#endif

extern "C" SQRT_API double function(std::deque<double> arguments_function) {
	return sqrt(arguments_function.at(0));
}

extern "C" SQRT_API std::string name() {
	return "sqrt";
}

extern "C" SQRT_API int countOperands() {
	return 1;
}

extern "C" SQRT_API int priority() {
	return 3;
}