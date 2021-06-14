#pragma once

#include "Component.h"

//Component���p�������N���X�̃|�C���^����Ɏg���n���h��
template<class T>
class ComponentHandle {
public:
	//�R�s�[�R���X�g���N�^
	ComponentHandle(const ComponentHandle<T>& _handle)
		:mComp(_handle.mComp), mHandleSet(_handle.mHandleSet)
	{
		mHandleSet->insert((void*)this);
	}
	//GameObject��AddChild�ł̂ݎg����R���X�g���N�^
	ComponentHandle(T* _obj, boost::shared_ptr<std::set<void*>> _set)
		:mComp(_obj), mHandleSet(_set)
	{
		mHandleSet->insert((void*)this);
	}
	ComponentHandle()
		: mComp(nullptr), mHandleSet(nullptr)
	{}
	ComponentHandle(const T* comp)
		:mComp(comp), mHandleSet(comp->mHandles)
	{
		mHandleSet->insert((void*)this);
	}
	~ComponentHandle()
	{
		if (mHandleSet != nullptr)mHandleSet->erase((void*)this);
	}
	T* operator->() const noexcept
	{
		//�_���O�����O�|�C���^�Ȃ��assert���o��
		if (mComp == nullptr) {
			Log::OutputCritical("Dungling Pointer");
		}
		return mComp;
	}
	bool IsValid() const
	{
		return (mComp != nullptr);
	}
	void Reset(Component* const _comp)
	{
		BOOST_ASSERT_MSG(mComp == _comp, "ComponentHandle::Reset() should be called in Component::~Component()");
		mComp = nullptr;
		mHandleSet.reset();
	}
	bool operator!() const noexcept
	{
		return !static_cast<bool>(*this);
	}
	template<class U>
	explicit operator ComponentHandle<U>() const noexcept {
		//�p���֌W�̃`�F�b�N
		U* self;
		try {
			self = dynamic_cast<U*>(mComp);
		}
		catch (std::bad_cast& b) {
			Log::OutputCritical("bad_cast\n");
		}
		return ComponentHandle<U>(self, mHandleSet);
	}
	//bool�^�ŃL���X�g�����S���ꉻ �_���O�����O�n���h���ł��邩�ۂ�
	explicit operator bool() const noexcept
	{
		return (mComp != nullptr);
	}
	ComponentHandle<T>& operator=(const ComponentHandle<T>& h) {
		if (mHandleSet)
		{
			mHandleSet->erase((void*)this);
			mHandleSet = nullptr;
		}
		mComp = nullptr;
		if (h.mComp)
		{
			mComp = h.mComp;
			mHandleSet = h.mHandleSet;
			mHandleSet->insert((void*)this);
		}
		return *this;
	}
private:
	//�n���h�����w���R���|�[�l���g
	T* mComp;
	//mComp���w���n���h����set�̃|�C���^(void*���g���̂͂ł���΂�߂���)
	boost::shared_ptr<std::set<void*>> mHandleSet;
};