#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <cmath>
#include <string>
#include <map>
#include <Windows.h>
#include <vector>
#include <list>
#include <set>
#include <typeinfo>

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