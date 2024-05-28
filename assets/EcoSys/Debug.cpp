#include "Debug.h"

void Debug::Loaded(const string& prompt) {
	cout << "SUCCES: " << prompt << '\n';
}

void Debug::Warning(const string& prompt) {
	cout << "AVERTIZARE: " << prompt << '\n';
}

void Debug::Error(const string& prompt) {
	cout << "EROARE: " << prompt << '\n';
}


