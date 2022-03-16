#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;
class EnemyWaveManager;

class MyselfAddAimBulletComponent :
    public Component
{
public:
    MyselfAddAimBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<EnemyWaveManager> enemy);
    ~MyselfAddAimBulletComponent();
    void Update() override;
    bool is_active_;
private:
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    boost::shared_ptr<EnemyWaveManager> enemy_;
    unsigned int time_;
    //‚±‚Ìtick”‚¨‚«‚É’e‚ğ’Ç‰Á
    static constexpr unsigned int period_to_fire_ = 15;
    //’e‚Ì1tick‚Å‚ÌˆÚ“®‹——£
    static constexpr double moving_dist_ = 8.0;
    //’e‚Ì”¼Œa
    static constexpr double bullet_redius_ = 5.0;
    //2‘Î‚Ì‚¤‚¿•Ğ•û‚©‚ç’e‚ğo‚·(i=1,-1,to‚ÍŒ‚‚Â‘ÎÛ)
    void ShootFrom(int i, GameObjectHandle to);
};

