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
	/// (x,y,z)を(x,y,z,1)に拡張
	/// </summary>
	Vector4 XYZ1(Vector3 _vec3);
	/// <summary>
	/// (x,y,z)を(x,y,z,0)に拡張
	/// </summary>
	Vector4 XYZ0(Vector3 _vec3);
	/// <summary>
	/// (x,y,z,w)を(x,y,z)に変換
	/// (w=0ならそのまま，w\neq 0ならば/w)
	/// </summary>
	Vector3 XYZ(Vector4 _vec4);
	/// <summary>
	/// (x,y)を(x,y,0)に変換
	/// </summary>
	Vector3 XY0(Vector2 _vec2);
	/// <summary>
	/// 4x4単位行列
	/// </summary>
	Matrix4x4 Identity4x4();
	/// <summary>
	/// (_x,_y,_z)だけ平行移動行列
	/// </summary>
	Matrix4x4 Translation(double _x, double _y,double _z);
	/// <summary>
	/// _vecだけ平行移動する行列
	/// </summary>
	Matrix4x4 Translation(Vector3 _vec);
	/// <summary>
	/// x座標を_x，y座標を_y，z座標を_z倍に拡大する行列
	/// </summary>
	Matrix4x4 Expand(double _x, double _y, double _z);
	/// <summary>
	/// x座標を_vec[0]，y座標を_vec[1]，z座標を_vec[2]倍に拡大する行列
	/// </summary>
	Matrix4x4 Expand(Vector3 _vec);
	/// <summary>
	/// quaternionは4次元ベクトルを流用
	/// </summary>
	using Quaternion = Vector4;
	/// <summary>
	/// 回転軸と角度を指定してquaternionを取得
	/// </summary>
	Quaternion GetQuaternion(Vector3 _axis, double _theta);
	/// <summary>
	/// quaternionを回転行列に変換
	/// </summary>
	Matrix4x4 Rotate(Quaternion _q);
	/// <summary>
	/// _q1と_q2をt:(1-t)で補完
	/// </summary>
	Quaternion Slerp(Quaternion _q1, Quaternion _q2, double t);
	/// <summary>
	/// 原点を中心とする正射影プロジェクション行列を作る
	/// </summary>
	/// <param name="width">近接平面の横幅[px]</param>
	/// <param name="height">近接平面の縦幅[px]</param>
	/// <param name="near_z">近接平面のz座標(変換後0となるz座標)</param>
	/// <param name="far_z">遠方平面のz座標(変換後1となるz座標)</param>
	Matrix4x4 GetOrthoGraphicProjection(double width, double height, double near_z, double far_z);
	/// <summary>
	/// LU分解で逆行列を求める
	/// </summary>
	Matrix4x4 GetInverseMatrix(Matrix4x4& mat);
	XMMATRIX ConvertToXMMATRIX(Matrix4x4 mat);
	XMFLOAT2 ConvertToXMFLOAT2(Vector2 vec2);
	XMFLOAT3 ConvertToXMFLOAT3(Vector3 vec3);
	/// <summary>
	/// 内積を求める
	/// </summary>
	inline double Dot(Vector2 v1, Vector2 v2);
	/// <summary>
	/// 内積を求める
	/// </summary>
	inline double Dot(Vector3 v1, Vector3 v2);
	/// <summary>
	/// 内積を求める
	/// </summary>
	inline double Dot(Vector4 v1, Vector4 v2);
}