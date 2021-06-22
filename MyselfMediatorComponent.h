#pragma once
#include "Component.h"

class DrawTextureComponent;

//自機の複数コンポーネントをまとめるコンポーネント それらのブジェクトへの追加は行わない
//まとめるコンポーネントは，
//・DrawTextureComponent
//・あたり判定コンポーネント
class MyselfMediatorComponent :
    public Component
{
public:
    MyselfMediatorComponent(ComponentHandle<DrawTextureComponent> draw_texture_component);
    void Update() override;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
};

