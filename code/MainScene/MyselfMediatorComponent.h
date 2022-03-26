#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class EnemyWaveManager;
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
    MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemy);
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
    boost::shared_ptr<EnemyWaveManager> enemy_wave_manager_;
    //MyselfCollisionComponentから呼び出される、当たり判定処理関数
    //(具体的な処理はcondition_に任せる)
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_);
    //自機の武器をMyselfArmor2に変更する
    //TODO:今回自機の武器が高々3種類ぐらいしかないからいいけど、もっとあったらどうするんだろうね?
    void SetMyselfArmor2();
    //TODO:逆再生を作る時、MyselfConditionBaseの時系列を持っておくこともちょっと考えたけど、
    //インスタンス・コンポーネントの生成・削除が含まれているため相当めんどくさそう
    //例えばコンポーネントが存在するしない以外に「activeかinactiveか」を持たせ、かつ
    //各コンディションのインスタンスは常に保持し、コンディションの遷移はコマンドとして記憶する
    //というふうにすれば可能か?
    //今回は時間もアレなんでとりあえずやりませんけど
    //次tickから順行・逆行再生
    void SetProgradePlay();
    void SetRetrogradePlay(unsigned int speed);
    //自機位置・角度の変遷をdequeで持つ(末尾の方が時間的に後)
    //TODO:今はMyselfRetrogradeConditionから参照するためにpublicにするが、
    //そのうちこれをCondition内で完結するようにしたい
    std::deque<MatVec::Vector2> pos_transition_;
    std::deque<double> angle_transition_;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<MyselfConditionBase> condition_;
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //攻撃を受けてから何tick無敵になるか
    static constexpr unsigned int invulnerable_time_ = 120;
    //この値が0以上ならば無敵中
    int damage_counter_;
    //自機移動制限
    //左辺，下辺，右辺，上辺
    ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
    //自機の武器装備、および自機描画を委譲する
    boost::shared_ptr<MyselfArmorBase> armor_;
    //自機位置を何個まで保存しておくか
    static const int transition_max_length_;
    //speed倍速で逆行再生中ならばspeed、順行再生中ならば-1
    int retrograde_speed_;
};

