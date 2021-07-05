#pragma once
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "GameObject.h"

class MainScene;

class TestCollisionComponent :
    public CollisionComponent
{
public:
    TestCollisionComponent(unsigned int tag, GameObjectHandle obj, double radius, bool delete_flag, MainScene* scene);
    ~TestCollisionComponent();
    void Update() override;
    void AddGeometryToManager(CollisionManager& manager) override;
private:
    CircleGeometry circle_;
    GameObjectHandle obj_;
    bool delete_flag_;
    MainScene* scene_;
};

