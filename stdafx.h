#pragma once
#include <cmath>
#include <string>
#include <map>
#include <Windows.h>
#include <vector>
#include <list>
#include <set>
#include <typeinfo>

#include <Eigen/Dense>
#include <Eigen/LU>

#include <boost/noncopyable.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>

//���������ɒu�������Ȃ����C�V�F�[�_�Ƃ̏��̎󂯓n���̂��߂Ɏd���Ȃ�
#include <DirectXMath.h>
//�ꕔ�\���̂̂ݖ��O��Ԃ��O���g���\���̂𕪂���₷������
using DirectX::XMMATRIX;
using DirectX::XMFLOAT2;
using DirectX::XMFLOAT3;

#include "Log.h"
#include "Math.h"
#include "MatVec.h"
#include "Rect2.h"