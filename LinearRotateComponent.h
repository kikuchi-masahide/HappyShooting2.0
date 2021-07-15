#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

//�����̃I�u�W�F�N�g�𖈃t���[�����p�x��]������
class LinearRotateComponent :
    public Component
{
public:
    /// <param name="object">��]������I�u�W�F�N�g</param>
    /// <param name="theta">��tick�̉�]�p�x</param>
    LinearRotateComponent(GameObjectHandle object, double theta);
    ~LinearRotateComponent();
    void Update() override;
private:
    double theta_;
};

