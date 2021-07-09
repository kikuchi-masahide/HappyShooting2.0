#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "GameObject.h"

class MyselfMediatorComponent;
class MainScene;

/// <summary>
/// 自機用の当たり判定コンポーネント
/// </summary>
class MyselfCollisionComponent :
    public CollisionComponent
{
public:
    MyselfCollisionComponent(MainScene* scene, GameObjectHandle myself, ComponentHandle<MyselfMediatorComponent> mediator);
    //自機の当たり判定枠のタグ
    static constexpr unsigned int myself_tag_ = 0;
    static constexpr unsigned int damage_ = 200;
    ~MyselfCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    //当たり判定円の半径
    static constexpr double circle_radius_ = 0.01;
private:
    MainScene* scene_;
    CircleGeometry geometry_;
    GameObjectHandle myself_;
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

