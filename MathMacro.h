#pragma once
#include <cmath>

/// /// <summary>
/// _d���ق�0�ł��邩�ǂ������肷��
/// </summary>
inline bool Zero(double _d)
{
	double eps = 1e-8;
	return (abs(_d) < eps);
}

inline double Max(double _a, double _b)
{
	if (_a < _b)return _b;
	return _a;
}

inline double Min(double _a, double _b)
{
	if (_a < _b)return _a;
	return _b;
}

constexpr double PI = 3.1415926535;