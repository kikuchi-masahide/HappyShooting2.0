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

//正直ここに置きたくないが，シェーダとの情報の受け渡しのために仕方なく
#include <DirectXMath.h>
//一部構造体のみ名前空間を外し使う構造体を分かりやすくする
using DirectX::XMMATRIX;
using DirectX::XMFLOAT2;
using DirectX::XMFLOAT3;

#include "Log.h"
#include "Math.h"
#include "MatVec.h"
#include "Rect2.h"