#include "Calculator.h"

int main()
{
	Calculator calc;
	cout << calc.GetResult("2+2+2*((3-2/1+2*3.5)-1.5)*2") << endl;//2+2+2*((3-2/1+2*3.5)-1.5)*2
	return 0;
}
