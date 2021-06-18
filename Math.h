#pragma once

/// <summary>
/// _d‚ª‚Ù‚Ú0‚Å‚ ‚é‚©‚Ç‚¤‚©”»’è‚·‚é
/// </summary>
inline bool Zero(double _d)
{
	double eps = 1e-8;
	return (abs(_d) < eps);
}

const double PI = 3.1415926535;