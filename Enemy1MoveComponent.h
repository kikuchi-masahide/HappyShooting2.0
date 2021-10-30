#pragma once
#include "code/Engine/Component.h"

#include "code/Engine/Math/Math.h"

class Enemy1MoveComponent :
    public Component
{
public:
    /// <param name="wait_count">¶¬Œã‰½tick–Ú‚©‚ç“®‚«n‚ß‚é‚©</param>
    /// <param name="direct">1tick‚ ‚½‚è‚ÌˆÚ“®—Ê</param>
    /// <param name="angle">1tick‚ ‚½‚è‚Ì‰ñ“]—Ê</param>
    Enemy1MoveComponent(GameObjectHandle handle, unsigned int wait_count, MatVec::Vector2 direct, double angle);
    void Update() override;
private:
    ~Enemy1MoveComponent();
    //‰½tick–Ú‚©‚ç“®‚«n‚ß‚é‚©
    unsigned int wait_count_;
    //©•ª‚ª¶‚Ü‚ê‚Ä‚©‚ç‰½tick–Ú‚ÌUpdate()‚©(‚Í‚¶‚ß‚Ä‚ÌŒÄ‚Ño‚µ‚ÌŠÔ0)
    unsigned int counter_;
    //1tick‚ ‚½‚è‚ÌˆÚ“®—Ê
    MatVec::Vector2 direct_;
    //1tick‚ ‚½‚è‚Ì‰ñ“]—Ê
    double angle_;
};

