#pragma once
#include "list.h"
#include<iostream>
#include<string>
#include<math.h>
#include<algorithm>
using namespace std;
list::list()//默认构造函数
{
}
list::list(int a1, int b1, int c1, double cor_num, int a2, int b2, int c2, double len, double x, double y) {
	//参数构造函数
	list::a1 = a1;
	list::b1 = b1;
	list::c1 = c1;
	list::a2 = a2;
	list::b2 = b2;
	list::c2 = c2;
	list::cor_num = cor_num;
	list::len = len;
	list::x = x;
	list::y = y;
	change_view_angle(a1, b1, c1);
	change_coor_angle(a2, b2, c2);
	change_dx_and_dy();
}
list::~list()
{
	//析构函数
}
void list::change_view_angle(int a, int b, int c) {
	//将角度制转化为弧度制（观测右角）
	list::view_angle = PI / 180 * (a + b / 60.0 + c / 3600.0);
	return;
}
void list::change_coor_angle(int a, int b, int c) {
	//将角度制转化为弧度制（坐标方位角）
	list::coor_angle = PI / 180 * (a + b / 60.0 + c / 3600.0);
	return;
}
void list::change_dx_and_dy() {
	//计算距离
	list::dx = len * cos(coor_angle);
	list::dy = len * sin(coor_angle);
	return;
}
void list::calcul_coor_angle(list* previous_list) {
	//计算除了点号1的其他点号的坐标方位角
	int previous[3] = { 0 }, new_[3] = { 0 };
	int ans[3] = { 0 };
	previous[0] = previous_list->a2 + 180;
	previous[1] = previous_list->b2;
	previous[2] = previous_list->c2;
	new_[0] = list::a1;
	new_[1] = list::b1;
	new_[2] = list::c1;
	for (int i = 2;i >= 0;i--) {
		if (previous[i] - new_[i] < 0 && i >= 1) {
			previous[i] += 60;
			previous[i - 1]--;
		}
		ans[i] = previous[i] - new_[i];
	}
	ans[2] -= list::cor_num;
	for (int i = 2;i >= 1;i--) {
		if (ans[i] >= 60) {
			ans[i - 1] += ans[i] / 60;
			ans[i] %= 60;
		}
	}
	if (ans[0] >= 360)ans[0] -= 360;
	if (ans[2] < 0) {
		ans[2] += 60;
		ans[1]--;
	}
	if (ans[1] < 0) {
		ans[1] += 60;
		ans[0]--;
	}
	list::a2 = ans[0];
	list::b2 = ans[1];
	list::c2 = ans[2];
	return;
}