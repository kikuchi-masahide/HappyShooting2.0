#pragma once
#include "CollisionComponent.h"

#include "GameObject.h"
#include "CircleGeometry.h"

class MainScene;

//自機弾用の当たり判定コンポーネント
class MyBulletCollisionComponent :
    public CollisionComponent
{
public:
    /// <param name="damage">与えうるダメージ値</param>
    /// <param name="radius">円の半径[px]</param>
    /// <param name="double_suicide">対象に当たった後オブジェクトごと死ぬかどうか</param>
    MyBulletCollisionComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> manager, unsigned int damage, double radius);
    ~MyBulletCollisionComponent();
    void Update();
    void CheckHitComponent();
private:
    double radius_;
    CircleGeometry circle_;
};

