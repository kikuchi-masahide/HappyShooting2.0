#pragma once
#include "Component.h"

#include "GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;

//自機の複数コンポーネントをまとめるコンポーネント それらのブジェクトへの追加は行わない
//まとめるコンポーネントは，
//・DrawTextureComponent
//・あたり判定コンポーネント
class MyselfMediatorComponent :
    public Component
{
public:
    MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    void Update() override;
    /// <summary>
    /// 自機にダメージを与える
    /// </summary>
    /// <param name="point">何ポイントダメージを入れるか</param>
    void CauseDamageToMyself(unsigned int point);
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //攻撃を受けてから何tick無敵になるか
    static constexpr unsigned int invulnerable_time_ = 120;
    //この値が0以上ならば無敵中
    int damage_counter_;
    //攻撃を受けた状況によって自身のαを変える
    void SetMyselfAlpha();
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
};

