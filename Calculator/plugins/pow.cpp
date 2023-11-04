#include "pch.h"
#include <cmath>
#include <deque>
#include <string>

#ifdef POW_EXPORTS
#define POW_API __declspec(dllexport)
#else
#define POW_API __declspec(dllimport)
#endif

extern "C" POW_API double function(std::deque<double> arguments_function) {
	return pow(arguments_function.at(0), arguments_function.at(1));
}

extern "C" POW_API std::string name() {
	return "^";
}

extern "C" POW_API int countOperands() {
	return 2;
}

extern "C" POW_API int priority() {
	return 4;
}