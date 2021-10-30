#pragma once

namespace MatVec {

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
	/// <summary>
	/// 4x4�P�ʍs��
	/// </summary>
	Matrix4x4 Identity4x4();
	/// <summary>
	/// LU�����ŋt�s������߂�
	/// </summary>
	Matrix4x4 GetInverseMatrix(Matrix4x4& mat);
	/// <summary>
	/// ���_�𒆐S�Ƃ��鐳�ˉe�v���W�F�N�V�����s������
	/// </summary>
	/// <param name="width">�ߐڕ��ʂ̉���[px]</param>
	/// <param name="height">�ߐڕ��ʂ̏c��[px]</param>
	/// <param name="near_z">�ߐڕ��ʂ�z���W(�ϊ���0�ƂȂ�z���W)</param>
	/// <param name="far_z">�������ʂ�z���W(�ϊ���1�ƂȂ�z���W)</param>
	Matrix4x4 GetOrthoGraphicProjection(double width, double height, double near_z, double far_z);

}