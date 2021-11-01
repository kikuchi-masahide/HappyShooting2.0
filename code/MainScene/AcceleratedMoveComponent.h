#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//毎tickオブジェクト位置に速度v_を足し，v_に加速度a_を足すことで，加速度的な動きをさせる
//(判定がだるいので，一回画面より大幅に外に出たらすぐに消滅させる)
class AcceleratedMoveComponent :
    public Component
{
public:
    /// <param name="initial_pos">初期位置</param>
    /// <param name="initial_v">初期速度</param>
    /// <param name="a">加速度</param>
    AcceleratedMoveComponent(GameObjectHandle obj, int prio,MatVec::Vector2 initial_pos,MatVec::Vector2 initial_v,MatVec::Vector2 a);
    void Update() override;
private:
    ~AcceleratedMoveComponent();
    //Update()でオブジェクト位置に足す速度
    MatVec::Vector2 v_;
    //加速度
    MatVec::Vector2 a_;
};

