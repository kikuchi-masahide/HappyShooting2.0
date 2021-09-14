#pragma once
#include "UIScreen.h"

#include "Game.h"

class MainScenePauseUI :
    public UIScreen
{
public:
    MainScenePauseUI(Scene* scene);
    ~MainScenePauseUI();
    void Update() override;
    void Output() override;
private:
};

