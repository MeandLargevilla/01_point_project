#ifndef COMMON_H
#define COMMON_H

// ===== 常量 =====
constexpr int t_y = 10;
constexpr int t_z = 10;
constexpr int colorSelect = 0;// 0: m1, 1: m2
// ===== 结构体 =====
struct point {
	float x, y, z;
	float m1, m2;
	point(float a, float b, float c, float d, float e) : x(a), y(b), z(c), m1(d), m2(e) {}
};

#endif
