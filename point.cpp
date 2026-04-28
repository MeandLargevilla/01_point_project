#include "point.h"
#include "common.h"
#include <iostream>
std::vector<float> creatmm(int n)
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
    return pointres;
}

