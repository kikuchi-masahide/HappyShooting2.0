#pragma once

class Component;

//Componentを継承したクラスのポインタ代わりに使うハンドラ
template<class T>
class ComponentHandle {
public:
	//コピーコンストラクタ
	ComponentHandle(const ComponentHandle<T>& _handle)
		:mComp(_handle.mComp), mHandleSet(_handle.mHandleSet)
	{
		mHandleSet->insert((void*)this);
	}
	//GameObjectのAddChildでのみ使われるコンストラクタ
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
		//ダングリングポインタならばassertを出す
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
		//継承関係のチェック
		U* self;
		try {
			self = dynamic_cast<U*>(mComp);
		}
		catch (std::bad_cast& b) {
			Log::OutputCritical("bad_cast\n");
		}
		return ComponentHandle<U>(self, mHandleSet);
	}
	//bool型でキャストを完全特殊化 ダングリングハンドルであるか否か
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
	//指しているコンポーネントが同じならば等しい
	bool operator==(const ComponentHandle<T>&handle);
private:
	//ハンドルが指すコンポーネント
	T* mComp;
	//mCompを指すハンドルのsetのポインタ(void*を使うのはできればやめたい)
	std::set<void*>* mHandleSet;
};

template<class T>
inline bool ComponentHandle<T>::operator==(const ComponentHandle<T>& handle)
{
	return (mComp == handle.mComp);
}
