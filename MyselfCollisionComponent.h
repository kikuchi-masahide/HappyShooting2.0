#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "code/Engine/GameObject.h"

class MyselfMediatorComponent;
class MainScene;

/// <summary>
/// ���@�p�̓����蔻��R���|�[�l���g
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
    //�����蔻��~�̔��a
    static constexpr double circle_radius_ = 0.01;
private:
    CircleGeometry geometry_;
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

