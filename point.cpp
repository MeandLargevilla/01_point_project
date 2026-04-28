#include "point.h"
#include "common.h"
#include <iostream>
#include <algorithm> // 用于 std::max

// 建议将 maxX 等变量放在函数内部，避免全局变量污染
static std::vector<float> creatmm(int n)
{
    std::vector<float> result(n * 2);
    for (int i = 0; i < n; i++)
    {
        result[i * 2] = (float)i;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        result[i * 2 + 1] = (float)(n - 1 - i);
    }
    return result;
}

std::vector<point> creatpoints(int n)
{
    std::vector<float> mm = creatmm(n);
    std::vector<point> pointres;

    // 1. 生成原始坐标
    for (int i = 0; i < n; i++)
    {
        pointres.emplace_back(
            static_cast<float>(i / (t_y * t_z)),
            static_cast<float>(i % t_y),
            static_cast<float>(i / t_y % t_z),
            static_cast<float>(mm[2 * i] / (n - 1)),
            static_cast<float>(mm[2 * i + 1] / (n - 1))
        );
    }

    // 2. 寻找最大值（初始化为极小值或第一个点）
    float maxX = 0.0001f, maxY = 0.0001f, maxZ = 0.0001f;
    for (const auto& p : pointres) {
        if (p.x > maxX) maxX = p.x;
        if (p.y > maxY) maxY = p.y;
        if (p.z > maxZ) maxZ = p.z;
    }

    // 3. 归一化处理（注意：这里去掉了 const，使用 auto&）
    for (auto& p : pointres) {
        p.x = (p.x / maxX) * 2.0f - 1.0f;
        p.y = (p.y / maxY) * 2.0f - 1.0f;
        p.z = (p.z / maxZ) * 2.0f - 1.0f;
    }

    return pointres;
}

// 修正输出函数
void printpoint(const point& p)
{
    // 直接输出 p 里面的成员，因为值已经改写进去了
    std::cout << "Point Details: "
        << "x = " << p.x << ", "
        << "y = " << p.y << ", "
        << "z = " << p.z << ", "
        << "m1 = " << p.m1 << ", "
        << "m2 = " << p.m2 << std::endl;
}