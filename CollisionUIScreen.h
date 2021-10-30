#pragma once
#include "code/Engine/UIScreen.h"

#include "code/Engine/Math/Math.h"

class PolygonGeometry;
class PolygonGeometryDrawer;

/// <summary>
/// ICollisionGeometryを画面上に表示する
/// </summary>
class CollisionUIScreen :
    public UIScreen
{
public:
    CollisionUIScreen(Scene* scene);
    ~CollisionUIScreen();
    void Update() override;
    void Output() override;
    //描画対象の追加(消去するときはDelete~を呼び出す必要がある)
    void AddPolygonGeometry(PolygonGeometry* polygon,MatVec::Vector3 color);
    void DeletePolygonGeometry(PolygonGeometry* polygon);
private:
    std::unordered_map<PolygonGeometry*, PolygonGeometryDrawer> polygon_drawers_;
};

