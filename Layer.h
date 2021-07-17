#pragma once

#include "Math.h"

class Scene;
class DX12Resource;
class DX12DescriptorHeap;
class Game;
template<class T>
class LayerHandle;

/// <summary>
/// ����̕`��̈�̃y���|���S����S������N���X
/// </summary>
class Layer {
public:
	Layer(Rect2 _rect, double _z, unsigned int _swap);
	/// <summary>
	/// Output�R���|�[�l���g�EScene::UniqueOutput�̌��z�~���ŌĂяo��
	/// �y���|���S���̃o�b�N�o�b�t�@�ւ̍ŏI�I�ȕ`����s���D
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// ��L���W���{���ɕύX�����̂�Draw���s�O
	/// </summary>
	void SetRect(Rect2 _rect);
	Rect2 GetRect();
	/// <summary>
	/// z���W���{���ɕύX�����̂�Draw���s�O
	/// </summary>
	void SetZ(double _z);
	double GetZ() const;
	//z���W�̕ύX�����������ۂ�
	bool HasZChanged();
	/// <summary>
	/// Scene����̂݌Ăяo����CRect�Cz�̕ύX�t���b�V���p�̊֐�
	/// </summary>
	void FlushZRectChange(Layer* _layer);
	bool GetDeleteFlag() const
	{
		return mDeleteFlag;
	}
	void SetDeleteFlag()
	{
		mDeleteFlag = true;
	}
	/// <summary>
	/// ���̃��C���[���y���|���S����\��t����X���b�v�`�F�[����ID���擾
	/// </summary>
	/// <returns></returns>
	unsigned int GetSwapchainID();
protected:
	virtual ~Layer();
	/// <summary>
	/// ���g���w��T�^��LayerHandle���擾
	/// </summary>
	template<class T>
	LayerHandle<T> This()
	{
		return LayerHandle<T>((T*)this, &mHandles);
	}
private:
	friend Scene;
	//Scene�̓f�X�g���N�^���ĂԒ��O��mDeleteCheck��true�ɂ���
	bool mDeleteCheck;
	//�������w���n���h���̏W��(void*�ɂ���̂���߂���)
	std::set<void*> mHandles;
	//&�ɂ��|�C���^�擾���֎~
	Layer* operator&() const noexcept;
	//Draw���s�O�̕ύX�̃X�g�b�N�Ƃ��̃t���O
	bool mWasZChanged;
	bool mWasRectChanged;
	double z;
	double mZAfter;
	//�N���C�A���g��̐�L�̈�
	Rect2 mRect;
	Rect2 mRectAfter;
	unsigned int mSwapchainID;
	bool mDeleteFlag;
};