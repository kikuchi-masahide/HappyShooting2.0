#pragma once
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"

class LayerManager;
class CollisionManager;

//8tick‚¨‚«‚É©‹@’Êí’e‚ğ’Ç‰Á
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
private:
    //’e‚Ì1tick‚Å‚ÌˆÚ“®‹——£
    static constexpr double moving_dist_ = 8;
    //’e‚Ì”¼Œa
    static constexpr double bullet_redius_ = 5;
    //‚±‚Ìtick”‚¨‚«‚É’e‚ğ’Ç‰Á
    static constexpr unsigned int period_to_fire_ = 8;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //ŠÔ Update‚ÌÅŒã‚Å‰ÁZ
    unsigned int time_;
};

