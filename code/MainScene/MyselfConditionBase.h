#pragma once
#include "../Engine/Component.h"

class MyselfMediatorComponent;

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
    /// <summary>
    /// 今自機がダメージを喰らわない状態ならばtrueを返す
    /// </summary>
    virtual bool IsInvincible() = 0;
protected:
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

