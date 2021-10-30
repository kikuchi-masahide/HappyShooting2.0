#pragma once
#include "code/Engine/Component.h"

class Enemy5MoveComponent :
    public Component
{
public:
    Enemy5MoveComponent(GameObjectHandle obj,int counter0);
    ~Enemy5MoveComponent();
    void Update() override;
private:
    int counter_;
};

