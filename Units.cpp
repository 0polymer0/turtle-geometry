#include "Units.h"

double Turt::
cosD(Degrees deg){
	return std::cos(deg * PI / 180.0);
}

double Turt::
acosD(double ratio){
	return ((acos(ratio)* 180.0)/PI);
}

double Turt::
sinD(Degrees deg){
	return std::sin(deg * PI / 180.0);
}

/*int Turt::
round(double toRound){
	return toRound + 0.5;
}*/

int Turt:: 
zeroDivisor(int given, int modulus){
	int n = 1;
	while(given*n % modulus)
		n++;
	return n;
}