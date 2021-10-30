#pragma once

#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace MatVec
{
	
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
	XMMATRIX ConvertToXMMATRIX(Matrix4x4 mat);
	XMFLOAT2 ConvertToXMFLOAT2(Vector2 vec2);
	XMFLOAT3 ConvertToXMFLOAT3(Vector3 vec3);
}