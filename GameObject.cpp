#include "GameObject.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "Scene.h"
#include "Game.h"

GameObject::GameObject(Scene* _scene, boost::shared_ptr<std::set<GameObjectHandle*>> _hset, MatVec::Vector2 _pos, double _scale, double _angle)
	:mScene(_scene), mHandles(_hset), mPosition(_pos), mScale(_scale), mRotation(_angle),mDeleteFlag(false)
{
	BOOST_ASSERT_MSG(_scene != nullptr,"GameObject::GameObject() should be called in Scene::AddObject()");
	BOOST_ASSERT_MSG(_hset != nullptr, "GameObject::GameObject() should be called in Scene::AddObject()");
}

MatVec::Vector2 GameObject::GetPosition() const
{
	return mPosition;
}

MatVec::Vector2 GameObject::SetPosition(MatVec::Vector2 _pos)
{
	mPosition = _pos;
	return mPosition;
}

double GameObject::GetScale() const
{
	return mScale;
}

double GameObject::SetScale(double _sc)
{
	if (_sc < 0)mScale = 0.0f;
	else mScale = _sc;
	return mScale;
}

double GameObject::GetRotation() const
{
	return mRotation;
}

double GameObject::SetRotation(double _ro)
{
	mRotation = _ro;
	return mRotation;
}

GameObject::~GameObject() {
	//�����������O�ɃR���|�[�l���g�����������Ă���
	mUpdateComponents.clear();
	mOutputComponents.clear();
	Log::OutputCritical("GameObject Delete");
}

void GameObject::DeleteFlagedComponents(Scene* _scene)
{
	//�����Ɛe�V�[������Ăяo����Ă��邩�̃`�F�b�N
	BOOST_ASSERT_MSG(_scene == mScene,"GameObject::DeleteFlagedComponents() should be called from mScene");
	//�R���|�[�l���g�����񂵃t���O�������Ă�����̂��폜
	auto itr = mUpdateComponents.begin();
	while (itr != mUpdateComponents.end()) {
		if ((*itr)->GetDeleteFlag()) {
			itr = mUpdateComponents.erase(itr);
		}
		else itr++;
	}
	itr = mOutputComponents.begin();
	while (itr != mOutputComponents.end()) {
		if ((*itr)->GetDeleteFlag()) {
			itr = mOutputComponents.erase(itr);
		}
		else itr++;
	}
}

Game& GameObject::GetGame() const
{
	return mScene->mGame;
}