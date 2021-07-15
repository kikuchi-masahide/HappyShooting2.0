#pragma once

namespace MatVec
{
	class Matrix4x4 {
	public:
		Matrix4x4();
		~Matrix4x4();
		double m[4][4];
		double& operator()(unsigned int i, unsigned int j);
		Matrix4x4 operator+();
		Matrix4x4 operator-();
		Matrix4x4& operator*=(double d);
		Matrix4x4& operator/=(double d);
		Matrix4x4& operator+=(const Matrix4x4& v2);
		Matrix4x4& operator-=(const Matrix4x4& v2);
	};
	Matrix4x4 operator*(const Matrix4x4& v, const double& d);
	Matrix4x4 operator*(double d, const Matrix4x4& v);
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator/(const Matrix4x4& v, double d);
	Matrix4x4 operator+(const Matrix4x4& v1, const Matrix4x4& v2);
	Matrix4x4 operator-(const Matrix4x4& v1, const Matrix4x4& v2);
	bool operator==(const Matrix4x4& v1, const Matrix4x4& v2);
	bool operator!=(const Matrix4x4& v1, const Matrix4x4& v2);
	
	class Vector2 {
	public:
		Vector2();
		Vector2(double x, double y);
		~Vector2();
		double v[2];
		double& operator()(unsigned int ind);
		Vector2 operator+() const;
		Vector2 operator-() const;
		Vector2& operator*=(double d);
		Vector2& operator/=(double d);
		Vector2& operator+=(const Vector2& v2);
		Vector2& operator-=(const Vector2& v2);
		double Norm();
		void Normalize();
	};
	Vector2 operator*(const Vector2& v, double d);
	Vector2 operator*(double d, const Vector2& v);
	Vector2 operator/(const Vector2& v, double d);
	Vector2 operator+(const Vector2& v1, const Vector2& v2);
	Vector2 operator-(const Vector2& v1, const Vector2& v2);
	bool operator==(const Vector2& v1, const Vector2& v2);
	bool operator!=(const Vector2& v1, const Vector2& v2);

	class Vector3 {
	public:
		Vector3();
		Vector3(double x, double y, double z);
		~Vector3();
		double v[3];
		double& operator()(unsigned int ind);
		Vector3 operator+() const;
		Vector3 operator-() const;
		Vector3& operator*=(double d);
		Vector3& operator/=(double d);
		Vector3& operator+=(const Vector3& v2);
		Vector3& operator-=(const Vector3& v2);
		double Norm();
		void Normalize();
	};
	Vector3 operator*(const Vector3& v, double d);
	Vector3 operator*(double d, const Vector3& v);
	Vector3 operator/(const Vector3& v, double d);
	Vector3 operator+(const Vector3& v1, const Vector3& v2);
	Vector3 operator-(const Vector3& v1, const Vector3& v2);
	bool operator==(const Vector3& v1, const Vector3& v2);
	bool operator!=(const Vector3& v1, const Vector3& v2);

	class Vector4 {
	public:
		Vector4();
		Vector4(double x, double y, double z, double w);
		~Vector4();
		double v[4];
		double& operator()(unsigned int ind);
		Vector4 operator+() const;
		Vector4 operator-() const;
		Vector4& operator*=(double d);
		Vector4& operator/=(double d);
		Vector4& operator+=(const Vector4& v2);
		Vector4& operator-=(const Vector4& v2);
		double Norm();
		void Normalize();
	};
	Vector4 operator*(const Vector4& v, double d);
	Vector4 operator*(double d, const Vector4& v);
	Vector4 operator/(const Vector4& v, double d);
	Vector4 operator+(const Vector4& v1, const Vector4& v2);
	Vector4 operator-(const Vector4& v1, const Vector4& v2);
	bool operator==(const Vector4& v1, const Vector4& v2);
	bool operator!=(const Vector4& v1, const Vector4& v2);

	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	/// <summary>
	/// (x,y,z)��(x,y,z,1)�Ɋg��
	/// </summary>
	Vector4 XYZ1(Vector3 _vec3);
	/// <summary>
	/// (x,y,z)��(x,y,z,0)�Ɋg��
	/// </summary>
	Vector4 XYZ0(Vector3 _vec3);
	/// <summary>
	/// (x,y,z,w)��(x,y,z)�ɕϊ�
	/// (w=0�Ȃ炻�̂܂܁Cw\neq 0�Ȃ��/w)
	/// </summary>
	Vector3 XYZ(Vector4 _vec4);
	/// <summary>
	/// (x,y)��(x,y,0)�ɕϊ�
	/// </summary>
	Vector3 XY0(Vector2 _vec2);
	/// <summary>
	/// 4x4�P�ʍs��
	/// </summary>
	Matrix4x4 Identity4x4();
	/// <summary>
	/// (_x,_y,_z)�������s�ړ��s��
	/// </summary>
	Matrix4x4 Translation(double _x, double _y,double _z);
	/// <summary>
	/// _vec�������s�ړ�����s��
	/// </summary>
	Matrix4x4 Translation(Vector3 _vec);
	/// <summary>
	/// x���W��_x�Cy���W��_y�Cz���W��_z�{�Ɋg�傷��s��
	/// </summary>
	Matrix4x4 Expand(double _x, double _y, double _z);
	/// <summary>
	/// x���W��_vec[0]�Cy���W��_vec[1]�Cz���W��_vec[2]�{�Ɋg�傷��s��
	/// </summary>
	Matrix4x4 Expand(Vector3 _vec);
	/// <summary>
	/// quaternion��4�����x�N�g���𗬗p
	/// </summary>
	using Quaternion = Vector4;
	/// <summary>
	/// ��]���Ɗp�x���w�肵��quaternion���擾
	/// </summary>
	Quaternion GetQuaternion(Vector3 _axis, double _theta);
	/// <summary>
	/// quaternion����]�s��ɕϊ�
	/// </summary>
	Matrix4x4 Rotate(Quaternion _q);
	/// <summary>
	/// _q1��_q2��t:(1-t)�ŕ⊮
	/// </summary>
	Quaternion Slerp(Quaternion _q1, Quaternion _q2, double t);
	/// <summary>
	/// ���_�𒆐S�Ƃ��鐳�ˉe�v���W�F�N�V�����s������
	/// </summary>
	/// <param name="width">�ߐڕ��ʂ̉���[px]</param>
	/// <param name="height">�ߐڕ��ʂ̏c��[px]</param>
	/// <param name="near_z">�ߐڕ��ʂ�z���W(�ϊ���0�ƂȂ�z���W)</param>
	/// <param name="far_z">�������ʂ�z���W(�ϊ���1�ƂȂ�z���W)</param>
	Matrix4x4 GetOrthoGraphicProjection(double width, double height, double near_z, double far_z);
	/// <summary>
	/// LU�����ŋt�s������߂�
	/// </summary>
	Matrix4x4 GetInverseMatrix(Matrix4x4& mat);
	XMMATRIX ConvertToXMMATRIX(Matrix4x4 mat);
	XMFLOAT2 ConvertToXMFLOAT2(Vector2 vec2);
	XMFLOAT3 ConvertToXMFLOAT3(Vector3 vec3);
	/// <summary>
	/// ���ς����߂�
	/// </summary>
	inline double Dot(Vector2 v1, Vector2 v2);
	/// <summary>
	/// ���ς����߂�
	/// </summary>
	inline double Dot(Vector3 v1, Vector3 v2);
	/// <summary>
	/// ���ς����߂�
	/// </summary>
	inline double Dot(Vector4 v1, Vector4 v2);
}