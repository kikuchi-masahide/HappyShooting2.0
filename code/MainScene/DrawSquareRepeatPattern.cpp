#include "DrawSquareRepeatPattern.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"

DrawSquareRepeatPattern::DrawSquareRepeatPattern(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z, unsigned int texture_id, double texture_width, double texture_height)
	:MainSceneDrawComponent(object, layer_manager, z),
	drawer_(object->mScene->mGame, texture_id, texture_width, texture_height)
{
}

DrawSquareRepeatPattern::~DrawSquareRepeatPattern()
{
}

void DrawSquareRepeatPattern::Draw()
{
	drawer_.Draw(mObj->mScene->mGame, center_, square_width_, square_height_, alpha_, 600.0, 900.0);
}
