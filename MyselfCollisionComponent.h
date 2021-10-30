#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "code/Engine/GameObject.h"

class MyselfMediatorComponent;
class MainScene;

/// <summary>
/// 自機用の当たり判定コンポーネント
/// </summary>
class MyselfCollisionComponent :
    public CollisionComponent
{
public:
    MyselfCollisionComponent(GameObjectHandle myself, boost::shared_ptr<CollisionManager> manager, ComponentHandle<MyselfMediatorComponent> mediator);
    static constexpr unsigned int damage_ = 200;
    ~MyselfCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    //当たり判定円の半径
    static constexpr double circle_radius_ = 0.01;
private:
    CircleGeometry geometry_;
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

