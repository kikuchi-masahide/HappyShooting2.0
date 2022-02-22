#pragma once
#include "../Engine/Component.h"

class MyselfMediatorComponent;
class CollisionComponent;

/// <summary>
/// 自機の健康状態(通常，復活中，ビリビリ中...)とそれにより変わる位置更新の仕方，描画α，敵との当たり判定を管理
/// </summary>
class MyselfConditionBase :
    public Component
{
public:
    MyselfConditionBase(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator);
    virtual ~MyselfConditionBase();
    /// <summary>
    /// 位置，描画αの更新を行う．
    /// </summary>
    virtual void Update() override = 0;
    /// <summary>
    /// 当たり判定で自機がダメージを食らうとmediatorから呼び出され，
    /// 弾が当たった時の処理に加えて，
    /// 当たった弾の攻撃力から実ダメージを計算する
    /// (今はIsInvincible() == falseならばこの関数は呼ばれることはない)
    /// </summary>
    /// <param name="attack">敵弾攻撃力</param>
    /// <returns>実ダメージ</returns>
    virtual unsigned int GetDamaged(unsigned int attack) = 0;
    //弾を撃たせるか否かを返す
    virtual bool IsShooterActive();
    //MyselfCollisionComponentから呼び出される、当たり判定処理
    virtual void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_);
protected:
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

