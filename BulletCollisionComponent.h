#pragma once
#include "CollisionComponent.h"

#include "GameObject.h"

class MainScene;

//自機弾，敵機弾用当たり判定
class BulletCollisionComponent :
    public CollisionComponent
{
public:
    /// <param name="mytag">自分のタグ</param>
    /// <param name="enemytag">自分がダメージを与える対象のタグ</param>
    /// <param name="damage">与えうるダメージ値</param>
    /// <param name="radius">円の半径[px]</param>
    /// <param name="double_suicide">対象に当たった後オブジェクトごと死ぬかどうか</param>
    BulletCollisionComponent(GameObjectHandle obj, MainScene* scene, int upd_priority, unsigned int mytag, unsigned int enemytag, unsigned int damage, double radius, bool double_suicide = true);
    ~BulletCollisionComponent();
    void Update();
    void CheckHitComponent();
private:
    unsigned int enemy_tag_;
    double radius_;
    bool double_suicide_;
    MainScene* scene_;
};

