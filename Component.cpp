#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "Game.h"
#include "ComponentHandle.h"

Component::~Component() {
	BOOST_ASSERT_MSG(mDeleteCheck == true, "irregal destructor call without GameObject permission");
	//std::for_each(mHandles.begin(), mHandles.end(), [this](void* _obj) {
	////	�������
	//	auto handle = static_cast<ComponentHandle<Component>*>(_obj);
	//	handle->Reset();
	//});
	while (!mHandles.empty())
	{
		auto itr = mHandles.begin();
		auto handle = static_cast<ComponentHandle<Component>*>(*itr);
		handle->Reset();
	}
	//for (auto itr = mHandles.begin(); itr != mHandles.end();)
	//{
	//	auto handle = static_cast<ComponentHandle<Component>*>(*itr);
	//	handle->Reset();
	//}
}

Component::Component(int _order)
	: mUpdPriority(_order), mDeleteFlag(false),mDeleteCheck(false)
{
}

void Component::Update() {}