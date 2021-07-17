#pragma once
#include "Component.h"

#include "GameObjectHandle.h"
#include "Math.h"

class MainScene;

class MyselfPosAndAngleComponent :
    public Component
{
public:
    //activeレイヤーから現在の変形状況を受け取り，それを基に自機の位置と向きを決定するUpdateComponent
    MyselfPosAndAngleComponent(GameObjectHandle handle, MainScene* scene);
    void Update() override;
    ~MyselfPosAndAngleComponent();
    /// <summary>
    /// このコンポーネントがレイヤーの変形を受け取るための関数
    /// 元の位置にあるレイヤーの中心を原点とし，そこからのレイヤーの変形を
    /// 行列にまとめて毎tick渡す
    /// </summary>
    void SetLayerTransform(MatVec::Matrix4x4 matrix);
private:
    MatVec::Matrix4x4 layer_transform_;
    MainScene* main_scene_;
    //1tickあたりの移動距離
    constexpr static double moving_dist_ = 3.45;
};

