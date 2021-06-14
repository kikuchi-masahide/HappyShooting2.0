#pragma once

namespace MatVec
{
	using namespace Eigen;
	using Matrix3x3 = Matrix3d;
	using Matrix4x4 = Matrix4d;
	using Vector2 = Vector2d;
	/// <summary>
	/// �E��n�c3�����x�N�g��
	/// </summary>
	using Vector3 = Vector3d;
	/// <summary>
	/// �c4�����x�N�g��
	/// </summary>
	using Vector4 = Vector4d;
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
	/// </summary>
	Vector3 XYZ(Vector4 _vec4);
	/// <summary>
	/// (x,y)��(x,y,0)�ɕϊ�
	/// </summary>
	Vector3 XY0(Vector2 _vec2);
	/// <summary>
	/// 3x3�P�ʍs��
	/// </summary>
	Matrix3x3 Identity3x3();
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
	using Quaternion = Vector4d;
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
}