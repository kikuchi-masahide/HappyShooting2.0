#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;

class Boss2State0BulletBig :
    public Component
{
public:
    /// <param name="inv">n‚ß‚É’e‚Ì“®‚­•ûŒü‚ğ”½“]‚µ‚Ä¶‚©‚ç‰E‚É‚·‚é‚©”Û‚©</param>
    Boss2State0BulletBig(GameObjectHandle obj, bool inv, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss2State0BulletBig();
    void Update() override;
private:
    int time_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    //‰½tickŠÔŠu‚Å’e‚ğ¶¬‚·‚é‚©
    static const int bullet_period_;
    //’e‚ğ¶¬‚·‚é‚Æ‚«ˆê‹C‚É‰½ŒÂì‚é‚©
    static const int bullet_num_per_;
    //‚Å‚Á‚©‚¢’e‚Ìi‚Ş•ûŒü
    //x²•ûŒü‚Í•K—v‚É‰‚¶‚Ä³•‰”½“]
    static const double bullet_dx0_;
    static const double bullet_dy_;
    //‚Å‚Á‚©‚¢’e‚Ì”¼Œa
    static const double bullet_radius_;
    double bullet_dx_;
};

