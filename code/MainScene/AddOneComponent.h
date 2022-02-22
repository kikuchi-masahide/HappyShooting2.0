#pragma once
#include "../Engine/Component.h"

//Update���Ăяo����邽�тɁC�󂯎�����Q�ƕϐ���1�����₷
//(�Q�Ƃ��Ă���ϐ��̐����͊��m�ł��Ȃ����߁C���̕ϐ��������I�u�W�F�N�g��DeleteFlag�����ĂĂ��K�v������)
//HACK:component���X�V�p�Əo�͗p�ɂ킯�����߁A�o�͗pcomponent�̎��ԕϐ���ʂ̍X�V�p�R���|�[�l���g���炢����K�v���o�Ă��܂���
//�ӂ��ɃR���|�[�l���g��2��ނɕ�����K�v�͂Ȃ������̂ł�?
//�������X�V���A�o�͏��̕ϐ���2���K�v���o�Ă�����
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
