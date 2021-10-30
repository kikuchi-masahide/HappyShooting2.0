#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;

/// <summary>
/// �e�I�u�W�F�N�g���W����C�������ɔ��ł����G�ʏ�e�����p�x�Ō��R���|�[�l���g
/// </summary>
class NormalShootComponent :
    public Component
{
public:
    /// <param name="direction">����</param>
    /// <param name="period">��tick��1��ł�</param>
    /// <param name="attack">�U����</param>
    NormalShootComponent(GameObjectHandle handle, int priority, MatVec::Vector2 direction, double radius, unsigned int period, unsigned int attack, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager, MatVec::Vector3 edge_rgb = MatVec::Vector3(1.0,0.0,0.0),double edge_alpha = 1.0);
    ~NormalShootComponent();
    void Update() override;
private:
    MatVec::Vector2 direction_;
    unsigned int attack_;
    unsigned int period_;
    unsigned int counter_;
    double radius_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    MatVec::Vector3 edge_rgb_;
    double edge_alpha_;
};

