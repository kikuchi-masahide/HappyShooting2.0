#pragma once

#include "Log.h"

class Layer;

template<class T>
class LayerHandle {
public:
	//�R�s�[�R���X�g���N�^
	LayerHandle(const LayerHandle<T>& _handle)
		:mLayer(_handle.mLayer),mHandleSet(_handle.mHandleSet)
	{
		if (mLayer != nullptr) {
			mHandleSet->insert((void*)this);
		}
	}
	//Scene��AddLayer����Ăяo�����
	LayerHandle(T* _layer, std::set<void*>* _set)
		:mLayer(_layer), mHandleSet(_set)
	{
		mHandleSet->insert((void*)this);
	}
	LayerHandle()
		:mLayer(nullptr), mHandleSet(nullptr)
	{}
	~LayerHandle()
	{
		Reset();
	}
	T* operator->() const noexcept
	{
		//�_���O�����O�|�C���^�Ȃ��assert���o��
		BOOST_ASSERT_MSG(mLayer != nullptr, "LayerHandle dungling pointer");
		return mLayer;
	}
	bool IsValid() const
	{
		return (mLayer != nullptr);
	}
	void Reset()
	{
		if (mLayer != nullptr)
		{
			mHandleSet->erase(static_cast<void*>(this));
			mHandleSet = nullptr;
			mLayer = nullptr;
		}
	}
	bool operator!() const noexcept
	{
		return (mLayer == nullptr);
	}
	template<class U>
	explicit operator LayerHandle<U>() const noexcept {
		//�p���֌W�̃`�F�b�N
		U* self;
		try {
			self = dynamic_cast<U*>(mLayer);
		}
		catch (std::bad_cast& b) {
			Log::OutputCritical("bad_cast\n");
		}
		return LayerHandle<U>(self, mHandleSet);
	}
	//bool�^�ŃL���X�g�����S���ꉻ �_���O�����O�n���h���ł��邩�ۂ�
	explicit operator bool() const noexcept
	{
		return (mLayer != nullptr);
	}
	LayerHandle<T>& operator=(const LayerHandle<T>& h) {
		Reset();
		if (h.mLayer != nullptr)
		{
			mLayer = h.mLayer;
			mHandleSet = h.mHandleSet;
			mHandleSet->insert((void*)this);
		}
		return *this;
	}
private:
	//�n���h�����w�����C���[
	T* mLayer;
	//mLayer���w���n���h����set
	std::set<void*>* mHandleSet;
};