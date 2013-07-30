#include "BracketsCalc.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	CBracketsCalc calc;
	string str;
	cout << "==================" << endl;
	cout << "=Enter ""q"" for exit=" << endl;
	cout << "==================" << endl;
	cout << endl;
	while (1) {	
		cout << "==================" << endl;
		cin >> str;
		if (str=="q") break;
		cout << "==================" << endl;
		calc.input(str);
		if (calc.validation()) {
			cout << calc.calculation() << endl;
			cout << "==================" << endl;
		} else {
			cout << "Invalid Data" << endl;
			cout << "==================" << endl;
		}
		cout << endl;
	}

	return 0;
}

