#include <iostream>
#include <cmath>

using namespace std;

const double MEAN = 30;
const double NUM  = 51;
double Poisson(double x);
double Factorial(double x);

int main()
{
	double total = 0;
	for(double i = 0; i < NUM; i++){
		total += Poisson(i+1);
	}
	cout << 1 - total << endl;

	return 0;
}

double Poisson(double x)
{
	return pow(MEAN,x) * exp(-1 * MEAN) / Factorial(x);
}

double Factorial(double x)
{
	double rval = 1;
	for(double i = 1; i <= x; i++)
		rval *= i;
	return rval;
}
