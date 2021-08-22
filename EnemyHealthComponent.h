#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

class LayerManager;

//TODO:(このコンポーネントなんで作ったんだっけ...?)
//敵機用体力管理コンポーネント
//0未満になるとオブジェクトを消滅させ，消滅エフェクトを追加する
class EnemyHealthComponent :
    public Component
{
public:
    /// <param name="scene">消滅オブジェクト追加用シーンポインタ</param>
    /// <param name="object">親オブジェクト</param>
    /// <param name="health0">開始時体力</param>
    EnemyHealthComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, double health0);
    ~EnemyHealthComponent();
    /// <summary>
    /// ダメージを与える
    /// 主にCollisionComponent::CheckHitComponentから呼び出される
    /// </summary>
    /// <returns>実際に喰らったダメージ(体力100で200ダメの弾を当てられると実ダメージは100)</returns>
    double Damage(double damage);
    /// <summary>
    /// 体力チェック
    /// </summary>
    void Update() override;
    /// <summary>
    /// 残りの体力が，全体力に占める割合を返す
    /// </summary>
    double GetHealthRate();
private:
    double all_health_;
    double health_;
    boost::shared_ptr<LayerManager> layer_manager_;
};

