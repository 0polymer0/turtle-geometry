#ifndef TURTLE_UTILS
#define TURTLE_UTILS

#include <cmath>

namespace Turt{

typedef double Units;
typedef double Coordinate;
typedef double Degrees;
typedef double Speed;

const long double PI = 3.14159263565;
double cosD(Degrees deg);
double sinD(Degrees deg);
double acosD(double ratio);

int zeroDivisor(int given, int modulus);

//int round(double toRound);

}

#endif