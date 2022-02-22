#include "EnemyWaveBase.h"

#include "Math.h"
#include "../Engine/GameObject.h"
#include "EnemyWaveManager.h"
#include "MainScene.h"

EnemyWaveBase::EnemyWaveBase(unsigned int tick_after_clear, MainScene* main_scene)
	:tick_after_clear_(tick_after_clear), main_scene_(main_scene)
{
}

EnemyWaveBase::~EnemyWaveBase()
{
}
