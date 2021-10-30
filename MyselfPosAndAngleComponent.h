#pragma once
#include "code/Engine/Component.h"

#include "code/Engine/GameObject.h"
#include "Math.h"

class LayerManager;

class MyselfPosAndAngleComponent :
    public Component
{
public:
    //activeレイヤーから現在の変形状況を受け取り，それを基に自機の位置と向きを決定するUpdateComponent
    MyselfPosAndAngleComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager);
    void Update() override;
    ~MyselfPosAndAngleComponent();
private:
    //1tickあたりの移動距離
    constexpr static double moving_dist_ = 3.45;
    boost::shared_ptr<LayerManager> layer_manager_;
};

