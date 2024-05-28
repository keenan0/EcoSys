#pragma once
#include <string>
#include <iostream>
using namespace std;

class Debug {
private:
public:
	Debug() = default;
	~Debug() = default;

	static void Loaded(const string& prompt);
	static void Warning(const string& prompt);
	static void Error(const string& prompt);
};

