#pragma once

/// <summary>
/// _d���ق�0�ł��邩�ǂ������肷��
/// </summary>
inline bool Zero(double _d)
{
	double eps = 1e-8;
	return (abs(_d) < eps);
}

const double PI = 3.1415926535;