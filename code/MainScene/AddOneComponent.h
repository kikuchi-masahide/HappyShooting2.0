#pragma once
#include "../Engine/Component.h"

//Updateが呼び出されるたびに，受け取った参照変数を1ずつ増やす
//(参照している変数の生死は感知できないため，その変数を持つ元オブジェクトでDeleteFlagを建ててやる必要がある)
//HACK:componentを更新用と出力用にわけたため、出力用componentの時間変数を別の更新用コンポーネントからいじる必要が出てしまった
//ふつうにコンポーネントを2種類に分ける必要はなかったのでは?
//ただし更新順、出力順の変数を2つ持つ必要が出てきそう
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
