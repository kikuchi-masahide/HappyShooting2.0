#pragma once
#include "../Engine/Component.h"

class LayerManager;
class DrawTextureComponent;
class DrawSquareRepeatPattern;

//画面に上下の帯，!マーク，"Boss Incoming"を表示する
class BossIncomingUpdate :
    public Component
{
public:
    BossIncomingUpdate(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager);
    ~BossIncomingUpdate();
    void Update() override;
private:
    //初Update()で0
    unsigned int counter_;
    ComponentHandle<DrawTextureComponent> danger_mark_;
    ComponentHandle<DrawTextureComponent> boss_incoming_;
    //上下の動く帯
    ComponentHandle<DrawSquareRepeatPattern> square_up_;
    ComponentHandle<DrawSquareRepeatPattern> square_down_;
    static constexpr double danger_mark_centerx_ = -175.0;
    static constexpr double danger_mark_centery_ = 50.0;
    static constexpr double boss_incoming_centerx_ = 75.0;
    static constexpr double boss_incoming_centery_ = 50.0;
    static constexpr double square_up_centery_ = 120.0;
    static constexpr double square_down_centery_ = -20.0;
};

