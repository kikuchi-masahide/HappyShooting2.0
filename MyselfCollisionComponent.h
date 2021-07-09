#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "GameObject.h"

class MyselfMediatorComponent;
class MainScene;

/// <summary>
/// ���@�p�̓����蔻��R���|�[�l���g
/// </summary>
class MyselfCollisionComponent :
    public CollisionComponent
{
public:
    MyselfCollisionComponent(MainScene* scene, GameObjectHandle myself, ComponentHandle<MyselfMediatorComponent> mediator);
    //���@�̓����蔻��g�̃^�O
    static constexpr unsigned int myself_tag_ = 0;
    static constexpr unsigned int damage_ = 200;
    ~MyselfCollisionComponent();
    void Update() override;
    void CheckHitComponent() override;
    //�����蔻��~�̔��a
    static constexpr double circle_radius_ = 0.01;
private:
    MainScene* scene_;
    CircleGeometry geometry_;
    GameObjectHandle myself_;
    ComponentHandle<MyselfMediatorComponent> mediator_;
};

