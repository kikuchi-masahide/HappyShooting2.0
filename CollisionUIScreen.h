#pragma once
#include "code/Engine/UIScreen.h"

#include "code/Engine/Math/Math.h"

class PolygonGeometry;
class PolygonGeometryDrawer;

/// <summary>
/// ICollisionGeometry����ʏ�ɕ\������
/// </summary>
class CollisionUIScreen :
    public UIScreen
{
public:
    CollisionUIScreen(Scene* scene);
    ~CollisionUIScreen();
    void Update() override;
    void Output() override;
    //�`��Ώۂ̒ǉ�(��������Ƃ���Delete~���Ăяo���K�v������)
    void AddPolygonGeometry(PolygonGeometry* polygon,MatVec::Vector3 color);
    void DeletePolygonGeometry(PolygonGeometry* polygon);
private:
    std::unordered_map<PolygonGeometry*, PolygonGeometryDrawer> polygon_drawers_;
};

