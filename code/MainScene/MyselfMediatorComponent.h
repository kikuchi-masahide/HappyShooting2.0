#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;
class MyselfConditionBase;

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
    /// 自機にダメージを与える(当たり判定からの呼び出し)
    /// </summary>
    /// <param name="point">攻撃力</param>
    void CauseDamageToMyself(unsigned int point);
    /// <summary>
    /// 自機が無敵状態ならばtrueを返す(当たり判定からの呼び出し)
    /// </summary>
    bool IsInvincible();
    //次tickからの健康状態をnext_stateに差し替える(旧componentの消去も行う)
    void SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition);
    //自機描画時のα変更(ちょっと気持ち悪い...)
    void SetAlpha(double alpha);
    //ここらへんを全部おっぴろげにするのはあまりに先行き不安な気がするが
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    ComponentHandle<MyselfConditionBase> condition_;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //攻撃を受けてから何tick無敵になるか
    static constexpr unsigned int invulnerable_time_ = 120;
    //この値が0以上ならば無敵中
    int damage_counter_;
    //攻撃を受けた状況によって自身のαを変える
    void SetMyselfAlpha();
};

