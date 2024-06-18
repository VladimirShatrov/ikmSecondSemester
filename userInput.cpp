#include "userInput.h"

void correctIntInput(int& x) {
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Inccorect input, try again." << endl;
			continue;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (cin.gcount() > 1) {
			continue;
		}
		break;
	}
}

void correctIntInput(int& x, int left, int right) {
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Inccorect input, try again." << endl;
			continue;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (cin.gcount() > 1) {
			continue;
		}
		if (x < left || x > right) {
			cout << endl << x << " is out of range: from " << left << " to " << right << endl;
			continue;
		}
		break;
	}
}