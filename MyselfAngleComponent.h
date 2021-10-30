#pragma once
#include "code/Engine/Component.h"

#include "code/Engine/GameObject.h"

class LayerManager;
class Scene;

class MyselfAngleComponent :
    public Component
{
public:
    MyselfAngleComponent(GameObjectHandle handle,boost::shared_ptr<LayerManager> layer_manager);
    ~MyselfAngleComponent();
    void Update() override;
private:
    boost::shared_ptr<LayerManager> layer_manager_;
    Scene* scene_;
};

