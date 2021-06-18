#pragma once

/// <summary>
/// _dがほぼ0であるかどうか判定する
/// </summary>
inline bool Zero(double _d)
{
	double eps = 1e-8;
	return (abs(_d) < eps);
}

const double PI = 3.1415926535;