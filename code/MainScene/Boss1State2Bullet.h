#pragma once
#include "../Engine/Component.h"

class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;
class LayerManager;
class CollisionManager;

//Boss1State2で登場する，フヨフヨ浮いてる弾の全初期化や移動，消滅をすべて管理する
class Boss1State2Bullet :
    public Component
{
public:
    Boss1State2Bullet(GameObjectHandle handle, boost::shared_ptr<CollisionManager> collision_manager,boost::shared_ptr<LayerManager> layer_manager);
    void Update() override;
private:
    ~Boss1State2Bullet();
    //実体化(不透明度0->1)に何tickかけるか
    static constexpr unsigned int visualization_period_ = 60;
    //消滅するまでの自由な移動を何tick行うか.
    static constexpr unsigned int freemove_period_ = 60 * 22;
    //移動を終えてから消滅まで何tickかけるか
    static constexpr unsigned int unvisualization_period_ = 60;
    //半径
    static constexpr double size_ = 20;
    unsigned int counter_;
    //αをこちらで変更する
    ComponentHandle<DrawNormalBulletComponent> draw_component_;
    //実体化が終わった瞬間追加し，移動が終わった瞬間消す
    ComponentHandle<NormalBulletCollisionComponent> collision_component_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //次tickの移動距離
    double dx_, dy_;
    //乱数生成用
    static std::random_device seed_gen_;
    static std::mt19937 engine_;
    //[0,1)実数乱数
    static std::uniform_real_distribution<> dist_;
    //static変数の初期化を1度でも行ったらtrue
    static bool static_init_flag_;
};

