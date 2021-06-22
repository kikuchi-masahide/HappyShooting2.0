#pragma once

class Component;

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
	ComponentHandle(T* _obj, std::set<void*>* _set)
		:mComp(_obj), mHandleSet(_set)
	{
		if (mComp != nullptr) {
			mHandleSet->insert((void*)this);
		}
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
		Reset();
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
	void Reset()
	{
		if (mComp != nullptr)
		{
			mHandleSet->erase(static_cast<void*>(this));
			mHandleSet = nullptr;
			mComp = nullptr;
		}
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
		Reset();
		if (h.mComp != nullptr)
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
	std::set<void*>* mHandleSet;
};