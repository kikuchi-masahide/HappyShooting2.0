#include "MatVec.h"

#include <Eigen/Dense>
#include <Eigen/LU>

#include "Math.h"

using namespace MatVec;

MatVec::Vector4 MatVec::XYZ1(MatVec::Vector3 _vec3)
{
	return MatVec::Vector4(_vec3(0),_vec3(1),_vec3(2),1);
}

MatVec::Vector4 MatVec::XYZ0(MatVec::Vector3 _vec3)
{
	return MatVec::Vector4(_vec3(0),_vec3(1),_vec3(2),0);
}

MatVec::Vector3 MatVec::XYZ(MatVec::Vector4 _vec4)
{
	if (Zero(_vec4(3)))
	{
		return Vector3(_vec4(0), _vec4(1), _vec4(2));
	}
	return Vector3(_vec4(0) / _vec4(3), _vec4(1) / _vec4(3), _vec4(2) / _vec4(3));
}

MatVec::Vector3 MatVec::XY0(MatVec::Vector2 _vec2)
{
	return Vector3(_vec2(0),_vec2(1),0);
}

MatVec::Matrix4x4 MatVec::Identity4x4()
{
	auto mat = MatVec::Matrix4x4();
	mat(0, 0) = 1;
	mat(1, 1) = 1;
	mat(2, 2) = 1;
	mat(3, 3) = 1;
	return mat;
}

MatVec::Matrix4x4 MatVec::Translation(double _x, double _y, double _z)
{
	auto mat = Identity4x4();
	mat(0, 3) = _x;
	mat(1, 3) = _y;
	mat(2, 3) = _z;
	return mat;
}

MatVec::Matrix4x4 MatVec::Translation(Vector3 _vec)
{
	auto mat = Identity4x4();
	mat(0, 3) = _vec(0);
	mat(1, 3) = _vec(1);
	mat(2, 3) = _vec(2);
	return mat;
}

MatVec::Matrix4x4 MatVec::Expand(double _x, double _y, double _z)
{
	auto mat = Matrix4x4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat(i, j) = 0;
		}
	}
	mat(0, 0) = _x;
	mat(1, 1) = _y;
	mat(2, 2) = _z;
	mat(3, 3) = 1;
	return mat;
}

MatVec::Matrix4x4 MatVec::Expand(Vector3 _vec)
{
	auto mat = Matrix4x4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat(i, j) = 0;
		}
	}
	mat(0, 0) = _vec(0);
	mat(1, 1) = _vec(1);
	mat(2, 2) = _vec(2);
	mat(3, 3) = 1;
	return mat;
}

MatVec::Quaternion MatVec::GetQuaternion(MatVec::Vector3 _axis, double _theta)
{
	if (Zero(_axis.Norm()))
	{
		Log::OutputCritical("Zero Vector is set as an axis of quaternion");
	}
	_axis.Normalize();
	double x = _axis(0) * sin(_theta / 2);
	double y = _axis(1) * sin(_theta / 2);
	double z = _axis(2) * sin(_theta / 2);
	double w = cos(_theta / 2);
	return Quaternion(x, y, z, w);
}

MatVec::Matrix4x4 MatVec::Rotate(Quaternion _q)
{
	auto mat = Matrix4x4();
	double x = _q(0);
	double y = _q(1);
	double z = _q(2);
	double w = _q(3);

	mat(0, 0) = 1 - 2 * y * y - 2 * z * z;
	mat(0, 1) = 2 * x * y + 2 * z * w;
	mat(0, 2) = 2 * x * z - 2 * w * y;
	mat(0, 3) = 0;

	mat(1, 0) = 2 * x * y - 2 * w * z;
	mat(1, 1) = 1 - 2 * x * x - 2 * z * z;
	mat(1, 2) = 2 * y * z + 2 * w * x;
	mat(1, 3) = 0;

	mat(2, 0) = 2 * x * z + 2 * w * y;
	mat(2, 1) = 2 * y * z - 2 * w * x;
	mat(2, 2) = 1 - 2 * x * x - 2 * y * y;
	mat(2, 3) = 0;

	mat(3, 0) = 0;
	mat(3, 1) = 0;
	mat(3, 2) = 0;
	mat(3, 3) = 1;
	return mat;
}

MatVec::Quaternion MatVec::Slerp(MatVec::Quaternion _q1, MatVec::Quaternion _q2, double t)
{
	//_q1‚Æ_q2‚ÌŠÔ‚ÌŠp“x
	double omega = acos(Dot(_q1,_q2));
	return sin((1 - t) * omega) / sin(omega) * _q1 + sin(t * omega) / sin(omega) * _q2;
}

MatVec::Matrix4x4 MatVec::GetOrthoGraphicProjection(double width, double height, double near_z, double far_z)
{
	BOOST_ASSERT_MSG(!Zero(width), "invalid width given to MatVec::GetOrthoGraphicProjection");
	BOOST_ASSERT_MSG(!Zero(height), "invalid height given to MatVec::GetOrthoGraphicProjection");
	BOOST_ASSERT_MSG(near_z < far_z, "invalid near_z & far_z given to MatVec::GetOrthoGraphicProjection");
	BOOST_ASSERT_MSG(!Zero(far_z-near_z), "invalid near_z & far_z given to MatVec::GetOrthoGraphicProjection");
	Matrix4x4 res = Identity4x4();
	res(0, 0) = 2 / width;
	res(1, 1) = 2 / height;
	res(2, 2) = 1 / (far_z - near_z);
	res(2, 3) = near_z / (near_z - far_z);
	return res;
}

MatVec::Matrix4x4 MatVec::GetInverseMatrix(Matrix4x4& A)
{
	//LU•ª‰ð
	Matrix4x4 L = Identity4x4();   //‘ÎŠp—v‘f1
	Matrix4x4 U = Identity4x4();
	U.m[0][0] = A.m[0][0];
	U.m[0][1] = A.m[0][1];
	U.m[0][2] = A.m[0][2];
	U.m[0][3] = A.m[0][3];
	L.m[1][0] = A.m[1][0] / U.m[0][0];
	U.m[1][1] = A.m[1][1] - L.m[1][0] * U.m[0][1];
	U.m[1][2] = A.m[1][2] - L.m[1][0] * U.m[0][2];
	U.m[1][3] = A.m[1][3] - L.m[1][0] * U.m[0][3];
	L.m[2][0] = A.m[2][0] / U.m[0][0];
	L.m[2][1] = (A.m[2][1] - L.m[2][0] * U.m[0][1]) / A.m[1][1];
	U.m[2][2] = A.m[2][2] - L.m[2][0] * U.m[0][2] - L.m[2][1] * U.m[1][2];
	U.m[2][3] = A.m[2][3] - L.m[2][0] * U.m[0][3] - L.m[2][1] * U.m[1][3];
	L.m[3][0] = A.m[3][0] / U.m[0][0];
	L.m[3][1] = (A.m[3][1] - L.m[3][0] * U.m[0][1]) / U.m[1][1];
	L.m[3][2] = (A.m[3][2] - L.m[3][0] * U.m[0][2] - L.m[3][1] * U.m[1][2]) / U.m[2][2];
	U.m[3][3] = A.m[3][3] - L.m[3][0] * U.m[0][3] - L.m[3][1] * U.m[1][3] - L.m[3][2] * U.m[2][3];

	//LY=E‚È‚éY
	Matrix4x4 Y;
	Y.m[0][0] = 1;
	Y.m[1][0] = 0 - L.m[1][0] * Y.m[0][0];
	Y.m[2][0] = 0 - L.m[2][0] * Y.m[0][0] - L.m[2][1] * Y.m[1][0];
	Y.m[3][0] = 0 - L.m[3][0] * Y.m[0][0] - L.m[3][1] * Y.m[1][0] - L.m[3][2] * Y.m[2][0];
	Y.m[0][1] = 0;
	Y.m[1][1] = 1 - L.m[1][0] * Y.m[0][1];
	Y.m[2][1] = 0 - L.m[2][0] * Y.m[0][1] - L.m[2][1] * Y.m[1][1];
	Y.m[3][1] = 0 - L.m[3][0] * Y.m[0][1] - L.m[3][1] * Y.m[1][1] - L.m[3][2] * Y.m[2][1];
	Y.m[0][2] = 0;
	Y.m[1][2] = 0 - L.m[1][0] * Y.m[0][2];
	Y.m[2][2] = 1 - L.m[2][0] * Y.m[0][2] - L.m[2][1] * Y.m[1][2];
	Y.m[3][2] = 0 - L.m[3][0] * Y.m[0][2] - L.m[3][1] * Y.m[1][2] - L.m[3][2] * Y.m[2][2];
	Y.m[0][3] = 0;
	Y.m[1][3] = 0 - L.m[1][0] * Y.m[0][3];
	Y.m[2][3] = 0 - L.m[2][0] * Y.m[0][3] - L.m[2][1] * Y.m[1][3];
	Y.m[3][3] = 1 - L.m[3][0] * Y.m[0][3] - L.m[3][1] * Y.m[1][3] - L.m[3][2] * Y.m[2][3];

	//UX=Y‚È‚éX(=A^{-1})
	Matrix4x4 X;
	X.m[3][0] = (Y.m[3][0])                                                                         / U.m[3][3];
	X.m[2][0] = (Y.m[2][0] - U.m[2][3] * X.m[3][0])                                                 / U.m[2][2];
	X.m[1][0] = (Y.m[1][0] - U.m[1][2] * X.m[2][0] - U.m[1][3] * X.m[3][0])                         / U.m[1][1];
	X.m[0][0] = (Y.m[0][0] - U.m[0][1] * X.m[1][0] - U.m[0][2] * X.m[2][0] - U.m[0][3] * X.m[3][0]) / U.m[0][0];
	X.m[3][1] = (Y.m[3][1])                                                                         / U.m[3][3];
	X.m[2][1] = (Y.m[2][1] - U.m[2][3] * X.m[3][1])                                                 / U.m[2][2];
	X.m[1][1] = (Y.m[1][1] - U.m[1][2] * X.m[2][1] - U.m[1][3] * X.m[3][1])                         / U.m[1][1];
	X.m[0][1] = (Y.m[0][1] - U.m[0][1] * X.m[1][1] - U.m[0][2] * X.m[2][1] - U.m[0][3] * X.m[3][1]) / U.m[0][0];
	X.m[3][2] = (Y.m[3][2])                                                                         / U.m[3][3];
	X.m[2][2] = (Y.m[2][2] - U.m[2][3] * X.m[3][2])                                                 / U.m[2][2];
	X.m[1][2] = (Y.m[1][2] - U.m[1][2] * X.m[2][2] - U.m[1][3] * X.m[3][2])                         / U.m[1][1];
	X.m[0][2] = (Y.m[0][2] - U.m[0][1] * X.m[1][2] - U.m[0][2] * X.m[2][2] - U.m[0][3] * X.m[3][2]) / U.m[0][0];
	X.m[3][3] = (Y.m[3][3])                                                                         / U.m[3][3];
	X.m[2][3] = (Y.m[2][3] - U.m[2][3] * X.m[3][3])                                                 / U.m[2][2];
	X.m[1][3] = (Y.m[1][3] - U.m[1][2] * X.m[2][3] - U.m[1][3] * X.m[3][3])                         / U.m[1][1];
	X.m[0][3] = (Y.m[0][3] - U.m[0][1] * X.m[1][3] - U.m[0][2] * X.m[2][3] - U.m[0][3] * X.m[3][3]) / U.m[0][0];

	return X;
}

XMMATRIX MatVec::ConvertToXMMATRIX(Matrix4x4 mat)
{
	DirectX::XMMATRIX dxmatrix;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dxmatrix.r[i].m128_f32[j] = static_cast<float>(mat(i, j));
		}
	}
	return dxmatrix;
}

XMFLOAT2 MatVec::ConvertToXMFLOAT2(Vector2 vec2)
{
	return DirectX::XMFLOAT2(static_cast<float>(vec2(0)),vec2(1));
}

XMFLOAT3 MatVec::ConvertToXMFLOAT3(Vector3 vec3)
{
	return DirectX::XMFLOAT3(vec3(0),vec3(1),vec3(2));
}

double MatVec::Dot(Vector2 v1, Vector2 v2)
{
	return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1]);
}

double MatVec::Dot(Vector3 v1, Vector3 v2)
{
	return (v1.v[0]*v2.v[0]+v1.v[1]*v2.v[1]+v1.v[2]*v2.v[2]);
}

double MatVec::Dot(Vector4 v1, Vector4 v2)
{
	return (v1.v[0]*v2.v[0]+v1.v[1]*v2.v[1]+v1.v[2]*v2.v[2]+v1.v[3]*v2.v[3]);
}

MatVec::Vector2::Vector2()
{
	v[0] = 0;
	v[1] = 0;
}

MatVec::Vector2::Vector2(double x, double y)
{
	v[0] = x;
	v[1] = y;
}

MatVec::Vector2::~Vector2()
{
}

double& MatVec::Vector2::operator()(unsigned int ind)
{
	return v[ind];
}

Vector2 MatVec::Vector2::operator+() const
{
	return Vector2(v[0],v[1]);
}

Vector2 MatVec::Vector2::operator-() const
{
	return Vector2(-v[0],-v[1]);
}

Vector2& MatVec::Vector2::operator*=(double d)
{
	v[0] *= d;
	v[1] *= d;
	return *this;
}

Vector2& MatVec::Vector2::operator/=(double d)
{
	v[0] /= d;
	v[1] /= d;
	return *this;
}

Vector2& MatVec::Vector2::operator+=(const Vector2& v2)
{
	v[0] += v2.v[0];
	v[1] += v2.v[1];
	return *this;
}

Vector2& MatVec::Vector2::operator-=(const Vector2& v2)
{
	v[0] -= v2.v[0];
	v[1] -= v2.v[1];
	return *this;
}

double MatVec::Vector2::Norm()
{
	return sqrt(v[0] * v[0] + v[1] * v[1]);
}

void MatVec::Vector2::Normalize()
{
	double norm = Norm();
	*this /= norm;
}

Vector2 MatVec::operator*(const Vector2& v, double d)
{
	return Vector2(v.v[0] * d, v.v[1] * d);
}

Vector2 MatVec::operator*(double d, const Vector2& v)
{
	return Vector2(v.v[0]*d,v.v[1]*d);
}

Vector2 MatVec::operator/(const Vector2& v, double d)
{
	return Vector2(v.v[0]/d,v.v[1]/d);
}

Vector2 MatVec::operator+(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.v[0]+v2.v[0],v1.v[1]+v2.v[1]);
}

Vector2 MatVec::operator-(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.v[0]-v2.v[0],v1.v[1]-v2.v[1]);
}

bool MatVec::operator==(const Vector2& v1, const Vector2& v2)
{
	return (v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1]);
}

bool MatVec::operator!=(const Vector2& v1, const Vector2& v2)
{
	return !(v1 == v2);
}

MatVec::Vector3::Vector3()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

MatVec::Vector3::Vector3(double x, double y, double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

MatVec::Vector3::~Vector3()
{
}

double& MatVec::Vector3::operator()(unsigned int ind)
{
	return v[ind];
}

Vector3 MatVec::Vector3::operator+() const
{
	return Vector3(v[0], v[1], v[2]);
}

Vector3 MatVec::Vector3::operator-() const
{
	return Vector3(-v[0], -v[1], -v[2]);
}

Vector3& MatVec::Vector3::operator*=(double d)
{
	v[0] *= d;
	v[1] *= d;
	v[2] *= d;
	return *this;
}

Vector3& MatVec::Vector3::operator/=(double d)
{
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
	return *this;
}

Vector3& MatVec::Vector3::operator+=(const Vector3& v2)
{
	v[0] += v2.v[0];
	v[1] += v2.v[1];
	v[2] += v2.v[2];
	return *this;
}

Vector3& MatVec::Vector3::operator-=(const Vector3& v2)
{
	v[0] -= v2.v[0];
	v[1] -= v2.v[1];
	v[2] -= v2.v[2];
	return *this;
}

double MatVec::Vector3::Norm()
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void MatVec::Vector3::Normalize()
{
	double norm = Norm();
	*this /= norm;
}

Vector3 MatVec::operator*(const Vector3& v, double d)
{
	return Vector3(v.v[0] * d, v.v[1] * d, v.v[2] * d);
}

Vector3 MatVec::operator*(double d, const Vector3& v)
{
	return Vector3(v.v[0] * d, v.v[1] * d, v.v[2] * d);
}

Vector3 MatVec::operator/(const Vector3& v, double d)
{
	return Vector3(v.v[0] / d, v.v[1] / d, v.v[2] / d);
}

Vector3 MatVec::operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
}

Vector3 MatVec::operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}

bool MatVec::operator==(const Vector3& v1, const Vector3& v2)
{
	return (v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1] && v1.v[2] == v2.v[2]);
}

bool MatVec::operator!=(const Vector3& v1, const Vector3& v2)
{
	return !(v1 == v2);
}

MatVec::Vector4::Vector4()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
}

MatVec::Vector4::Vector4(double x, double y, double z, double w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

MatVec::Vector4::~Vector4()
{
}

double& MatVec::Vector4::operator()(unsigned int ind)
{
	return v[ind];
}

Vector4 MatVec::Vector4::operator+() const
{
	return Vector4(v[0], v[1], v[2], v[3]);
}

Vector4 MatVec::Vector4::operator-() const
{
	return Vector4(-v[0], -v[1], -v[2], -v[3]);
}

Vector4& MatVec::Vector4::operator*=(double d)
{
	v[0] *= d;
	v[1] *= d;
	v[2] *= d;
	v[3] *= d;
	return *this;
}

Vector4& MatVec::Vector4::operator/=(double d)
{
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
	v[3] /= d;
	return *this;
}

Vector4& MatVec::Vector4::operator+=(const Vector4& v2)
{
	v[0] += v2.v[0];
	v[1] += v2.v[1];
	v[2] += v2.v[2];
	v[3] += v2.v[3];
	return *this;
}

Vector4& MatVec::Vector4::operator-=(const Vector4& v2)
{
	v[0] -= v2.v[0];
	v[1] -= v2.v[1];
	v[2] -= v2.v[2];
	v[3] -= v2.v[3];
	return *this;
}

double MatVec::Vector4::Norm()
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

void MatVec::Vector4::Normalize()
{
	double norm = Norm();
	*this /= norm;
}

Vector4 MatVec::operator*(const Vector4& v, double d)
{
	return Vector4(v.v[0] * d, v.v[1] * d, v.v[2] * d, v.v[3] * d);
}

Vector4 MatVec::operator*(double d, const Vector4& v)
{
	return Vector4(v.v[0] * d, v.v[1] * d, v.v[2] * d, v.v[3] * d);
}

Vector4 MatVec::operator/(const Vector4& v, double d)
{
	return Vector4(v.v[0] / d, v.v[1] / d, v.v[2] / d , v.v[3] / d);
}

Vector4 MatVec::operator+(const Vector4& v1, const Vector4& v2)
{
	return Vector4(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2], v1.v[3] + v2.v[3]);
}

Vector4 MatVec::operator-(const Vector4& v1, const Vector4& v2)
{
	return Vector4(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2], v1.v[3] - v2.v[3]);
}

bool MatVec::operator==(const Vector4& v1, const Vector4& v2)
{
	return (v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1] && v1.v[2] == v2.v[2] && v1.v[3] == v2.v[3]);
}

bool MatVec::operator!=(const Vector4& v1, const Vector4& v2)
{
	return !(v1 == v2);
}

Vector4 MatVec::operator*(const Matrix4x4& m, const Vector4& v)
{
	Vector4 res;
	res.v[0] = m.m[0][0] * v.v[0] + m.m[0][1] * v.v[1] + m.m[0][2] * v.v[2] + m.m[0][3] * v.v[3];
	res.v[1] = m.m[1][0] * v.v[0] + m.m[1][1] * v.v[1] + m.m[1][2] * v.v[2] + m.m[1][3] * v.v[3];
	res.v[2] = m.m[2][0] * v.v[0] + m.m[2][1] * v.v[1] + m.m[2][2] * v.v[2] + m.m[2][3] * v.v[3];
	res.v[3] = m.m[3][0] * v.v[0] + m.m[3][1] * v.v[1] + m.m[3][2] * v.v[2] + m.m[3][3] * v.v[3];
	return res;
}

MatVec::Matrix4x4::Matrix4x4()
{
	std::fill(m[0], m[4], 0);
}

MatVec::Matrix4x4::~Matrix4x4()
{
}

double& MatVec::Matrix4x4::operator()(unsigned int i, unsigned int j)
{
	return m[i][j];
}

Matrix4x4 MatVec::Matrix4x4::operator+()
{
	return *this;
}

Matrix4x4 MatVec::Matrix4x4::operator-()
{
	m[0][0] *= -1;
	m[0][1] *= -1;
	m[0][2] *= -1;
	m[0][3] *= -1;

	m[1][0] *= -1;
	m[1][1] *= -1;
	m[1][2] *= -1;
	m[1][3] *= -1;

	m[2][0] *= -1;
	m[2][1] *= -1;
	m[2][2] *= -1;
	m[2][3] *= -1;

	m[3][0] *= -1;
	m[3][1] *= -1;
	m[3][2] *= -1;
	m[3][3] *= -1;

	return *this;
}

Matrix4x4& MatVec::Matrix4x4::operator*=(double d)
{
	m[0][0] *= d;
	m[0][1] *= d;
	m[0][2] *= d;
	m[0][3] *= d;

	m[1][0] *= d;
	m[1][1] *= d;
	m[1][2] *= d;
	m[1][3] *= d;

	m[2][0] *= d;
	m[2][1] *= d;
	m[2][2] *= d;
	m[2][3] *= d;

	m[3][0] *= d;
	m[3][1] *= d;
	m[3][2] *= d;
	m[3][3] *= d;

	return *this;
}

Matrix4x4& MatVec::Matrix4x4::operator/=(double d)
{
	m[0][0] /= d;
	m[0][1] /= d;
	m[0][2] /= d;
	m[0][3] /= d;

	m[1][0] /= d;
	m[1][1] /= d;
	m[1][2] /= d;
	m[1][3] /= d;

	m[2][0] /= d;
	m[2][1] /= d;
	m[2][2] /= d;
	m[2][3] /= d;

	m[3][0] /= d;
	m[3][1] /= d;
	m[3][2] /= d;
	m[3][3] /= d;

	return *this;
}

Matrix4x4& MatVec::Matrix4x4::operator+=(const Matrix4x4& v2)
{
	m[0][0] += v2.m[0][0];
	m[0][1] += v2.m[0][1];
	m[0][2] += v2.m[0][2];
	m[0][3] += v2.m[0][3];

	m[1][0] += v2.m[1][0];
	m[1][1] += v2.m[1][1];
	m[1][2] += v2.m[1][2];
	m[1][3] += v2.m[1][3];

	m[2][0] += v2.m[2][0];
	m[2][1] += v2.m[2][1];
	m[2][2] += v2.m[2][2];
	m[2][3] += v2.m[2][3];

	m[3][0] += v2.m[3][0];
	m[3][1] += v2.m[3][1];
	m[3][2] += v2.m[3][2];
	m[3][3] += v2.m[3][3];

	return *this;
}

Matrix4x4& MatVec::Matrix4x4::operator-=(const Matrix4x4& v2)
{
	m[0][0] -= v2.m[0][0];
	m[0][1] -= v2.m[0][1];
	m[0][2] -= v2.m[0][2];
	m[0][3] -= v2.m[0][3];

	m[1][0] -= v2.m[1][0];
	m[1][1] -= v2.m[1][1];
	m[1][2] -= v2.m[1][2];
	m[1][3] -= v2.m[1][3];

	m[2][0] -= v2.m[2][0];
	m[2][1] -= v2.m[2][1];
	m[2][2] -= v2.m[2][2];
	m[2][3] -= v2.m[2][3];

	m[3][0] -= v2.m[3][0];
	m[3][1] -= v2.m[3][1];
	m[3][2] -= v2.m[3][2];
	m[3][3] -= v2.m[3][3];

	return *this;
}

Matrix4x4 MatVec::operator*(const Matrix4x4& v, const double& d)
{
	Matrix4x4 v2 = v;
	v2 *= d;
	return v2;
}

Matrix4x4 MatVec::operator*(double d, const Matrix4x4& v)
{
	Matrix4x4 v2 = v;
	v2 *= d;
	return v2;
}

Matrix4x4 MatVec::operator*(const Matrix4x4& a, const Matrix4x4& b)
{
	Matrix4x4 m;
	m.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0];
	m.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1];
	m.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2];
	m.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3];

	m.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0];
	m.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1];
	m.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2];
	m.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3];

	m.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0];
	m.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1];
	m.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2];
	m.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3];

	m.m[3][0] = a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0];
	m.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1];
	m.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2];
	m.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3];

	return m;
}

Matrix4x4 MatVec::operator/(const Matrix4x4& v, double d)
{
	Matrix4x4 m = v;
	m /= d;
	return m;
}

Matrix4x4 MatVec::operator+(const Matrix4x4& v1, const Matrix4x4& v2)
{
	Matrix4x4 m;
	m.m[0][0] = v1.m[0][0] + v2.m[0][0];
	m.m[0][1] = v1.m[0][1] + v2.m[0][1];
	m.m[0][2] = v1.m[0][2] + v2.m[0][2];
	m.m[0][3] = v1.m[0][3] + v2.m[0][3];

	m.m[1][0] = v1.m[1][0] + v2.m[1][0];
	m.m[1][1] = v1.m[1][1] + v2.m[1][1];
	m.m[1][2] = v1.m[1][2] + v2.m[1][2];
	m.m[1][3] = v1.m[1][3] + v2.m[1][3];

	m.m[2][0] = v1.m[2][0] + v2.m[2][0];
	m.m[2][1] = v1.m[2][1] + v2.m[2][1];
	m.m[2][2] = v1.m[2][2] + v2.m[2][2];
	m.m[2][3] = v1.m[2][3] + v2.m[2][3];

	m.m[3][0] = v1.m[3][0] + v2.m[3][0];
	m.m[3][1] = v1.m[3][1] + v2.m[3][1];
	m.m[3][2] = v1.m[3][2] + v2.m[3][2];
	m.m[3][3] = v1.m[3][3] + v2.m[3][3];

	return m;
}

Matrix4x4 MatVec::operator-(const Matrix4x4& v1, const Matrix4x4& v2)
{
	Matrix4x4 m;
	m.m[0][0] = v1.m[0][0] - v2.m[0][0];
	m.m[0][1] = v1.m[0][1] - v2.m[0][1];
	m.m[0][2] = v1.m[0][2] - v2.m[0][2];
	m.m[0][3] = v1.m[0][3] - v2.m[0][3];

	m.m[1][0] = v1.m[1][0] - v2.m[1][0];
	m.m[1][1] = v1.m[1][1] - v2.m[1][1];
	m.m[1][2] = v1.m[1][2] - v2.m[1][2];
	m.m[1][3] = v1.m[1][3] - v2.m[1][3];

	m.m[2][0] = v1.m[2][0] - v2.m[2][0];
	m.m[2][1] = v1.m[2][1] - v2.m[2][1];
	m.m[2][2] = v1.m[2][2] - v2.m[2][2];
	m.m[2][3] = v1.m[2][3] - v2.m[2][3];

	m.m[3][0] = v1.m[3][0] - v2.m[3][0];
	m.m[3][1] = v1.m[3][1] - v2.m[3][1];
	m.m[3][2] = v1.m[3][2] - v2.m[3][2];
	m.m[3][3] = v1.m[3][3] - v2.m[3][3];

	return m;
}

bool MatVec::operator==(const Matrix4x4& v1, const Matrix4x4& v2)
{
	return (
		v1.m[0][0] == v2.m[0][0] &&
		v1.m[0][1] == v2.m[0][1] &&
		v1.m[0][2] == v2.m[0][2] &&
		v1.m[0][3] == v2.m[0][3] &&

		v1.m[1][0] == v2.m[1][0] &&
		v1.m[1][1] == v2.m[1][1] &&
		v1.m[1][2] == v2.m[1][2] &&
		v1.m[1][3] == v2.m[1][3] &&

		v1.m[2][0] == v2.m[2][0] &&
		v1.m[2][1] == v2.m[2][1] &&
		v1.m[2][2] == v2.m[2][2] &&
		v1.m[2][3] == v2.m[2][3] &&

		v1.m[3][0] == v2.m[3][0] &&
		v1.m[3][1] == v2.m[3][1] &&
		v1.m[3][2] == v2.m[3][2] &&
		v1.m[3][3] == v2.m[3][3]
	);
}

bool MatVec::operator!=(const Matrix4x4& v1, const Matrix4x4& v2)
{
	return !(v1 == v2);
}

