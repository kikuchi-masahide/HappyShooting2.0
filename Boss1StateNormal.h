#pragma once
#include "Boss1StateBase.h"

#include "Math.h"
#include "code/Engine/GameObject.h"

/// <summary>
/// –c‚ç‚ñ‚¾OŠpŒ`‚Ì’Êí’e‚ğŒ‚‚¿‘±‚¯‚éƒ‚[ƒh
/// </summary>
class Boss1StateNormal :
    public Boss1StateBase
{
public:
    Boss1StateNormal(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1StateNormal();
    void Update() override;
private:
    int counter_;
    //’e‚ğŒ‚‚Â•ûŒü
    double deg_;
    static constexpr double delta_deg_ = PI/120;
    //‰½ŒÂ‚Ì’e‚ğŒ‚‚Â‚©
    static constexpr int bullet_num_ = 96;
    //‰½tick‚¨‚«‚É’e‚ğŒ‚‚Â‚©D
    static constexpr int bullet_period_ = 30;
    //‚±‚Ìƒ‚[ƒh‚ª‰½tick‘±‚­‚©
    static constexpr int mode_period_ = 480;
    //’e‘¬
    static constexpr double bullet_speed_ = 4.0;
};

