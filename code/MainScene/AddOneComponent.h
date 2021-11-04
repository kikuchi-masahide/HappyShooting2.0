#pragma once
#include "../Engine/Component.h"

//Update���Ăяo����邽�тɁC�󂯎�����Q�ƕϐ���1�����₷
//(�Q�Ƃ��Ă���ϐ��̐����͊��m�ł��Ȃ����߁C���̕ϐ��������I�u�W�F�N�g��DeleteFlag�����ĂĂ��K�v������)
template<class T>
class AddOneComponent :
    public Component
{
public:
    AddOneComponent(GameObjectHandle handle,int prio,T* target);
    ~AddOneComponent();
    void Update() override;
private:
    T* target_;
};

template<class T>
inline AddOneComponent<T>::AddOneComponent(GameObjectHandle handle, int prio, T* target)
    :Component(handle,prio),
    target_(target)
{
}

template<class T>
inline AddOneComponent<T>::~AddOneComponent()
{
}

template<class T>
inline void AddOneComponent<T>::Update()
{
    (*target_)++;
}
