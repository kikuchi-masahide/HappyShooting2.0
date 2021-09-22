#include "stdafx.h"
#include "TransGradUIScreen.h"

#include "HBetapaint.h"
#include "Scene.h"

TransGradUIScreen::TransGradUIScreen(Scene* scene, bool input, bool update, MatVec::Vector4 start, MatVec::Vector4 end, unsigned int time, std::function<void(TransGradUIScreen*)> terminate)
	:UIScreen(scene,input,update),
	start_(start),end_(end),time_(time),counter_(0),terminate_(terminate)
{
}

TransGradUIScreen::~TransGradUIScreen()
{
}

void TransGradUIScreen::Update()
{
	counter_++;
	if (counter_ == time_)
	{
		terminate_(this);
	}
}

void TransGradUIScreen::Output()
{
	double theta = (double)counter_ * PI / (time_ * 2);
	double t = sin(theta);
	t = t * t;
	MatVec::Vector4 color = start_ * (1.0 - t) + end_ * t;
	HBetapaint::Beta(mScene->mGame, color);
}
