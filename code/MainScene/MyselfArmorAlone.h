#pragma once
#include "MyselfArmorBase.h"

#include "../Engine/Component.h"

class MyselfMediatorComponent;
class MyselfAddNormalBulletComponent;
class LayerManager;
class CollisionManager;
class DrawTextureComponent;

//���@�g��ł܂������e�������� ��ԍŏ��̕���`��
//TODO:�{����������A�����蔻��E���@�`��E���푕�����āABuilder�N���X�̏o�Ԃł���?���񑽕����Ȃ�����
class MyselfArmorAlone :
    public MyselfArmorBase
{
public:
    MyselfArmorAlone(ComponentHandle<MyselfMediatorComponent> med, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~MyselfArmorAlone() override;
    void Update() override;
    void UpdateAlpha(double alpha) override;
    void SetBulletAvailability(bool act) override;
private:
    ComponentHandle<DrawTextureComponent> texture_;
    ComponentHandle<MyselfAddNormalBulletComponent> add_bullet_;
};

