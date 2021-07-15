#pragma once
#include "Component.h"
#include "GameObjectHandle.h"

class MainScene;

//8tick‚¨‚«‚É©‹@’Êí’e‚ğ’Ç‰Á
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, MainScene* scene);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
private:
    //’e‚Ì1tick‚Å‚ÌˆÚ“®‹——£
    static constexpr double moving_dist_ = 8;
    //’e‚Ì”¼Œa
    static constexpr double bullet_redius_ = 5;
    //‚±‚Ìtick”‚¨‚«‚É’e‚ğ’Ç‰Á
    static constexpr unsigned int period_to_fire_ = 8;
    //eƒV[ƒ“
    MainScene* const scene_;
    //ŠÔ Update‚ÌÅŒã‚Å‰ÁZ
    unsigned int time_;
};

