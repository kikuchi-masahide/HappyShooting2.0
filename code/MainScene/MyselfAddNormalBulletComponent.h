#pragma once
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"

class LayerManager;
class CollisionManager;
class MyBulletComponent;

//8tick‚¨‚«‚Ì’Êí©‹@’e’Ç‰ÁA‚¨‚æ‚Ñ‚»‚ê‚ç‚ÌŠÇ—(‡sE‹tsÄ¶‚É‘Î‰‚³‚¹‚é)
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
    //’e‚¤‚Â‚È‚ç‚Îtrue‚É‚·‚é
    bool is_active_;
    //Ÿtick‚©‚ç‡sÄ¶‚ğs‚¤
    void SetProgradePlay();
    //Ÿtick‚©‚çspeed”{‘¬‚Å‹tÄ¶‚ğs‚¤
    void SetRetrogradePlay(unsigned int speed);
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
    int time_;
    //©•ª‚ªŒ‚‚Á‚½’e‚Ìvector LinearMoveRevComponent‚¾‚¯‚Á‚Ä‚¨‚¯‚Î‚æ‚¢
    std::vector<ComponentHandle<MyBulletComponent>> bullets_;
    //Ä¶ŠÔ
    int speed_;
};

