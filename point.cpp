#include"point.h"
#include"common.h"

static std::vector<float> creatmm(int n)
{
	std::vector<float> result(n * 2);
	for (int i = 0; i < n; i++)
	{
		result[i * 2] = i;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		result[i * 2 + 1] = n - 1 - i;
	}
	return result;
}
//创建一个函数，生成点
std::vector<point> creatpoints(int n)
{
	std::vector<float> mm = creatmm(n);
	std::vector<point> pointres;
	for (int i = 0;i < n;i++)
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
//输出函数
void printpoint(const point& p,int index)
{
	std::cout << "Point " << index << ": "
		<< "x = " << p.x << ", "
		<< "y = " << p.y << ", "
		<< "z = " << p.z << ", "
		<< "m1 = " << p.m1 << ", "
		<< "m2 = " << p.m2 << std::endl;
}