#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;
class MyselfConditionBase;
class MyselfPosAdjustComponent;
class MyselfAddNormalBulletComponent;
class CollisionComponent;
class MyselfArmorBase;

//自機の複数コンポーネントをまとめるコンポーネント それらのブジェクトへの追加は行わない
//まとめるコンポーネントは，
//・DrawTextureComponent
//・あたり判定コンポーネント
//TODO:何か間違っている気がする 各Stateに当たり判定を付属させた方がおそらく楽
//まあテストで配った後に考える
//TODO:自機が攻撃喰らってパカパカしてる時、自分からダメージ入れる判定が生きているっぽい
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
    //次tickからの健康状態をnext_stateに差し替える(旧componentの消去も行う)
    void SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition);
    //自機描画時のα変更(ちょっと気持ち悪い...)
    void SetAlpha(double alpha);
    //ここらへんを全部おっぴろげにするのはあまりに先行き不安な気がするが <- 何でこうしたんだっけ
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    ComponentHandle<MyselfConditionBase> condition_;
    //MyselfCollisionComponentから呼び出される、当たり判定処理関数
    //(具体的な処理はcondition_に任せる)
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_);
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //攻撃を受けてから何tick無敵になるか
    static constexpr unsigned int invulnerable_time_ = 120;
    //この値が0以上ならば無敵中
    int damage_counter_;
    //攻撃を受けた状況によって自身のαを変える
    void SetMyselfAlpha();
    //自機移動制限
    //左辺，下辺，右辺，上辺
    ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
    ComponentHandle<MyselfAddNormalBulletComponent> bullet_;
    //自機の武器装備、および自機描画を委譲する
    boost::shared_ptr<MyselfArmorBase> armor_;
};

