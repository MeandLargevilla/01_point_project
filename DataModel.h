// DataModel.h
#pragma once
#include <vector>

// 点的基础结构（绝对统一）
struct Point {
    float x, y, z;
    float m1, m2;
};

// 包围盒（极其重要：拯救 B 的初始相机视角）
struct BoundingBox {
    float minX, maxX, minY, maxY, minZ, maxZ;
};

// 最终交付的数据包
struct PointCloudData {
    std::vector<Point> points;
    BoundingBox bbox;
};

// A 提供给 B 调用的唯一接口
PointCloudData getPoints();