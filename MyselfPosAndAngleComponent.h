#pragma once
#include "code/Engine/Component.h"

#include "code/Engine/GameObject.h"
#include "Math.h"

class LayerManager;

class MyselfPosAndAngleComponent :
    public Component
{
public:
    //active���C���[���猻�݂̕ό`�󋵂��󂯎��C�������Ɏ��@�̈ʒu�ƌ��������肷��UpdateComponent
    MyselfPosAndAngleComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager);
    void Update() override;
    ~MyselfPosAndAngleComponent();
private:
    //1tick������̈ړ�����
    constexpr static double moving_dist_ = 3.45;
    boost::shared_ptr<LayerManager> layer_manager_;
};

