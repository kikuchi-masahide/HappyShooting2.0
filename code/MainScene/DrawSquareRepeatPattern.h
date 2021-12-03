#pragma once
#include "MainSceneDrawComponent.h"

#include "../Helper/HSquareRepeatPattern.h"

class DrawSquareRepeatPattern :
    public MainSceneDrawComponent
{
public:
    DrawSquareRepeatPattern(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z, unsigned int texture_id, double texture_width, double texture_height);
    ~DrawSquareRepeatPattern();
    void Draw() override;
    double square_width_;
    double square_height_;
    double alpha_;
    MatVec::Vector2 center_;
private:
    Helpers::HSquareRepeatPattern drawer_;
};

