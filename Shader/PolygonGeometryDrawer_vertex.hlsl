#include "PolygonGeometryDrawer_header.hlsli"

float4 main( float4 pos : POSITION ) : SV_POSITION
{
    return mul(pos,conv_);
}