#pragma once
#include<iostream>
#include"list.h"
#include<math.h>
#include"angle.h"
using namespace std;
void printf_main_menu() {//输出菜单函数
	cout << "========================" << endl;
	cout << "|    1.闭合导线运算    |" << endl;
	cout << "|    2.计算改正数      |" << endl;
	cout << "|    3.角度计算(加或减)|" << endl;
	cout << "|    4.测量模式        |" << endl;
	cout << "|    9.制作者名单      |" << endl;
	cout << "|    0.退出程序        |" << endl;
	cout << "========================" << endl;
	cout << "请输入菜单号：";
	return;
}
void create_list(list* new_list, list* previous_list, int a1, int b1, int c1, double cor_num, double len) {
	//创建除了点号1的其他点号函数
	//列表之间建立连接
	new_list->previous = previous_list;
	previous_list->next = new_list;
	//将观测右角进行赋值
	new_list->a1 = a1;
	new_list->b1 = b1;
	new_list->c1 = c1;
	//将距离进行赋值
	new_list->len = len;
	//将改正数进行赋值
	new_list->cor_num = cor_num;
	//调用角度转换函数
	new_list->change_view_angle(a1, b1, c1);
	//计算坐标方位角
	new_list->calcul_coor_angle(previous_list);
	//调用角度转换函数
	new_list->change_coor_angle(new_list->a2, new_list->b2, new_list->c2);
	//计算坐标增量
	new_list->change_dx_and_dy();
	return;
}
list* sum_list(list* list_head, list* previous_list, int n) {
	//previous_list是最后一个链表
	//创建求和列表，对表中数据进行求和
	list* tmp1 = new list;//最后一个
	list* tmp2 = list_head;//用来当指针
	//声明变量并且初始化
	double sum_len = 0, sum_dx = 0, sum_dy = 0;
	double sum_cor_num = 0;
	//建立与其他链表的连接
	previous_list->next = tmp1;
	tmp1->previous = previous_list;
	//开始循环累加
	for (int i = 1;i <= n;i++) {
		sum_len += tmp2->len;
		sum_dx += tmp2->dx;
		sum_dy += tmp2->dy;
		sum_cor_num += tmp2->cor_num;
		//转换到下一个链表
		tmp2 = tmp2->next;
	}
	//对求和链表进行赋值操作
	tmp1->len = sum_len;
	tmp1->dx = sum_dx;
	tmp1->dy = sum_dy;
	tmp1->cor_num = sum_cor_num;
	//返回求和链表的指针
	return tmp1;
}

void corr_list(list* now_list, list* previous_list, list* end_list) {
	//计算改正后的坐标增量和坐标
	//改正后的坐标增量计算
	now_list->ddx = now_list->dx - end_list->dx * now_list->len / end_list->len;
	now_list->ddy = now_list->dy - end_list->dy * now_list->len / end_list->len;
	//判断该链表是不是头链表，如果是头链表previous_list=NULL,则不用计算坐标，头链表坐标已知
	if (previous_list == NULL)return;
	//否则进行坐标计算
	else {
		//坐标计算
		now_list->x = previous_list->x + previous_list->ddx;
		now_list->y = previous_list->y + previous_list->ddy;
	}
	return;
}
void printf_all_list(list* list_head, int n) {
	//输出所有链表函数
	//创建中间指针来指向要输出的链表
	list* tmp = new list;
	//对指针进行赋值
	tmp = list_head;
	//开始循环输出
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("|    |     观测右角     |改正数|       坐标方位角     |  距离 |    坐标增量     |  改正后坐标增量 |       坐标        |\n");
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("|点号| 度  | 分  |  秒  |  秒  |  度   |  分  |   秒  |  米   |   米   |   米   |   米   |   米   |   米    |   米    |\n");
	for (int i = 1;i <= n;i++) {
		//cout << "点号 " << i << ":" << endl;
		//printf("观测右角：%d %d %d\n", tmp->a1, tmp->b1, tmp->c1);
		//printf("改正数：%.3lf\n", tmp->cor_num);
		//printf("坐标方位角：%d %d %d\n", tmp->a2, tmp->b2, tmp->c2);
		//printf("距离：%.3lf\n", tmp->len);
		//printf("坐标增量：%.3lf %.3lf\n", tmp->dx, tmp->dy);
		//printf("改正后坐标增量：%.3lf %.3lf\n", tmp->ddx, tmp->ddy);
		//printf("坐标：%.3lf %.3lf\n", tmp->x, tmp->y);
		//cout << endl;
		//tmp = tmp->next;//指针移动
		printf("|---------------------------------------------------------------------------------------------------------------------|\n");
		printf("| D%2d| %3d | %2d  |  %2d  |%3.0lf   |  %3d  |  %2d  |   %2d  |%7.3lf|%8.3lf|%8.3lf|%8.3lf|%8.3lf|%9.3lf|%9.3lf|\n",i,tmp->a1,tmp->b1,tmp->c1,tmp->cor_num,tmp->a2,tmp->b2,tmp->c2,tmp->len,tmp->dx,tmp->dy,tmp->ddx,tmp->ddy,tmp->x,tmp->y);
		tmp = tmp->next;//指针移动
	}
	//输出求和链表
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	printf("|求和|                  |%3.0lf   |                              |%8.3lf|%8.3lf|        |        |         |         |\n",tmp->cor_num,tmp->dx,tmp->dy);
	printf("|---------------------------------------------------------------------------------------------------------------------|\n");
	cout << "注意：由于改正数为整数的缘故，所以坐标方位角会出现些许误差，导致坐标增量出现几毫米到几厘米的误差" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	return;
}
int calcul_cor_num(angle* head_angle, int n) {
	int sum_a = 0, sum_b = 0, sum_c = 0;//全部初始化为零，然后求和
	int ans_a = (n - 2) * 180;
	angle* tmp = head_angle;//先让tmp为head_angle
	for (int i = 1;tmp!=NULL;i++) {
		//开始累加
		sum_a += tmp->m_a;
		sum_b += tmp->m_b;
		sum_c += tmp->m_c;
		tmp = tmp->next;
	}
	if (sum_c >= 60) {
		sum_b += sum_c / 60;
		sum_c %= 60;
	}
	if (sum_b >= 60) {
		sum_a += sum_b / 60;
		sum_b %= 60;
	}
	cout << "测量角度数之和为：" << sum_a << " " << sum_b << " " << sum_c << endl;
	if (sum_a >= ans_a) {
		sum_a -= ans_a;
	}
	else {
		sum_c = 60 - sum_c;
		sum_b = 59 - sum_b;
		sum_a = ans_a - 1 - sum_a;
	}
	return sum_a * 3600 + sum_b * 60 + sum_c;
}
void get_cor_num_comb(int cor_num, int n) {
	bool flag;
	if (cor_num >= 0) {
		flag = true;
		cout << "改正数为：" << -cor_num << endl;
		if (cor_num >= 80) {
			cout << "-----改正数过大，建议重新测量!-----" << endl;
		}
	}
	else {
		flag = false;
		cout << "改正数为：" << cor_num << endl;
		if (cor_num >= 80) {
			cout << "-----改正数过大，建议重新测量!-----" << endl;
		}
		cor_num = -cor_num;
	}
	int aveg = cor_num / n;
	int cnt = 0;
	for (int i = 0;i <= n;i++) {
		if (i * aveg + (n - i) * (aveg + 1) == cor_num) {
			cnt = i;
			break;
		}
	}
	if (!flag) {
		cout << "推荐的改正数组合为：";
		cout << cnt << "个" << aveg << "和" << n - cnt << "个" << aveg + 1 << endl;
	}
	else {
		cout << "推荐的改正数组合为：";
		cout << cnt << "个" << -aveg << "和" << n - cnt << "个" << -(aveg + 1) << endl;
	}
	return;
}
void get_cor_mod_four(int* anglea, int* angleb) {
	for (int i = 2;i >= 0;i--) {
		anglea[i] = angleb[i] - anglea[i];
	}
	for (int i = 2;i >= 1;i--) {
		if (anglea[i] < 0) {
			anglea[i] += 60 * (abs(anglea[i]) / 60 + 1);
			anglea[i - 1] -= abs(anglea[i]) / 60 + 1;
		}
	}
	if (anglea[0] < 0)anglea[0] += 360;
	return;
}
void mod_one() {//模式一的运行函数
	cout << endl;
	//声明变量
	int n, a1, b1, c1, a2, b2, c2;
	double len, cor_num, x, y;
	//与用户交互获得信息
	cout << "请输入共有几个点号：";
	cin >> n;
	//声明一个头链表
	list* list_head = new list;
	//与用户交互获得信息
	cout << "请输入第1个点号的观测右角，改正数（整数），坐标方位角，距离以及坐标" << endl;
	//输入
	cin >> a1 >> b1 >> c1 >> cor_num >> a2 >> b2 >> c2 >> len >> x >> y;
	//对头链表进行初始化
	*list_head = list(a1, b1, c1, cor_num, a2, b2, c2, len, x, y);
	//声明一个链表作为上一个链表
	list* previous_list = list_head;
	for (int i = 2;i <= n;i++) {
		//声明一个链表作为当前链表
		list* new_list = new list;
		//与用户交互获得信息
		cout << endl << "请输入第" << i << "个点号的观测角和改正数以及距离" << endl;
		//输入
		cin >> a1 >> b1 >> c1 >> cor_num >> len;
		//调用肺头链表创建链表函数
		create_list(new_list, previous_list, a1, b1, c1, cor_num, len);
		//上一个链表指针移动到当前链表指针，继续循环，直至创建n-1个链表
		previous_list = new_list;
	}
	//当前一共有1+n-1个链表，现在需要创建一个尾链表进行求和
	//创建一个链表
	list* end_list = new list;
	//对尾链表进行初始化求和
	end_list = sum_list(list_head, previous_list, n);
	//求和完之后，创建一个新链表进行改正增量计算
	list* tmp = new list;
	//指针初始化
	tmp = list_head;
	//上一个指针初始化
	previous_list = NULL;
	for (int i = 1;i <= n;i++) {
		//每个链表都调用corr_list()函数进行计算
		corr_list(tmp, previous_list, end_list);
		//指针移动
		previous_list = tmp;
		tmp = tmp->next;
	}
	//循环结束
	//此时tmp=end_list，不进入循环
	//输出全部链表
	printf_all_list(list_head, n);
	//函数执行结束
	return;
	/*
	测试点1
	121 28 12 -14 308 31 38 231.435 1000 1000
	90 7 30 -15 200.441
	135 48 0 -14 241.03
	84 10 30 -15 263.288
	108 27 0 -14 201.783
	测试点2
	121 28 12 -14 302 5 38 231.435 1000 1000
	90 7 30 -15 200.441
	135 48 0 -14 241.03
	84 10 30 -15 263.288
	108 27 0 -14 201.783
	测试点3
	121 28 12 -14 302 30 38 231.435 1000 1000
	90 7 30 -14 200.441
	135 48 0 -15 241.03
	84 10 30 -14 263.288
	108 27 0 -14 201.783
	测试点4
	121 28 12 -14 302 14 38 231.435 1000 1000
	90 7 30 -14 200.441
	135 48 0 -15 241.03
	84 10 30 -14 263.288
	108 27 0 -14 201.783
	测试点5
	137 1 47 7 24 0 0 30.681 1000 1000
	148 2 24 8 39.691
	122 15 10 7 27.555
	88 49 35 8 36.690
	147 9 46 7 49.008
	76 42 2 7 30.469
	测试点6
	92 48 45 8 340 0 0 36.685 1000 1000
	121 14 30 8 36.183
	119 1 42 8 41.540
	96 28 50 8 40.580
	110 25 33 8 51.008
	//
	121 28 12
	90 7 30
	135 48 0
	84 10 30
	108 27 0
	*/
}
void mod_tow() {//模式二函数体
	int n;
	cout << endl;
	cout << "请输入点号个数：";
	cin >> n;
	cout << "在输入" << n << "个内角的测量值（度，分，秒）（整数）" << endl;
	angle* head_angle = new angle;
	cin >> head_angle->m_a >> head_angle->m_b >> head_angle->m_c;
	angle* pre_angle = head_angle;
	for (int i = 1;i < n;i++) {
		angle* tmp = new angle;
		cout << "请输入第" << i + 1 << "个内角的测量值" << endl;
		cin >> tmp->m_a >> tmp->m_b >> tmp->m_c;
		pre_angle->next = tmp;
		tmp->previous = pre_angle;
		pre_angle = tmp;
	}
	int cor_num = calcul_cor_num(head_angle, n);
	get_cor_num_comb(cor_num, n);
	/* 
	测试点1
	144 10 17
	113 23 59
	118 20 28
	112 30 13
	141 19 30
	90 16 24
	测试点2

	*/
	return;
}
void mod_three() {
	int angle1[6];
	char flag;
	string mod;
head:
	memset(angle1, 0, sizeof(angle1));
	cout << "进入角度计算模式（格式输入：xx xx xx +(-) yy yy yy）" << endl;
	for (int i = 0;i <= 2;i++) {
		cin >> angle1[i];
	}
	cin >> flag;
	for (int i = 3;i <= 5;i++) {
		cin >> angle1[i];
	}
	switch (flag) {
	case '+':
		for (int i = 0;i <= 2;i++) {
			angle1[i] += angle1[i + 3];
		}
		for (int i = 2;i >= 1;i--) {
			if (angle1[i] >= 60) {
				angle1[i - 1] += angle1[i] / 60;
				angle1[i] %= 60;
			}
		}
		break;
	case '-':
		for (int i = 0;i <= 2;i++) {
			angle1[i] -= angle1[i + 3];
		}
		for (int i = 2;i >= 1;i--) {
			if (angle1[i] < 0) {
				angle1[i] += 60 * (abs(angle1[i]) / 60 + 1);
				angle1[i - 1] -= abs(angle1[i]) / 60 + 1;
			}
		}
		break;
	}
	cout << angle1[0] << " " << angle1[1] << " " << angle1[2] << endl;
error:
	cout << "进行下一次计算输入continue,退出计算模式输入return" << endl;
	cin >> mod;
	if (mod == "continue")goto head;
	else if (mod == "return")return;
	else {
		cout << "输入错误" << endl;
		goto error;
	}
}
void mod_four() {
	cout << "进入测量模式" << endl;
	int angle1[3] = { 0 }, angle2[3] = { 0 }, angle3[3] = { 0 }, angle4[3] = { 0 };
	for (int i = 1;i <= 2;i++) {
		cout << "第" << i << "测回" << endl;
		cout << "请输入第1、2个角" << endl;
		cin >> angle1[0] >> angle1[1] >> angle1[2];
		cin >> angle2[0] >> angle2[1] >> angle2[3];
		get_cor_mod_four(angle1, angle2);

	}
	return;
}
void mod_nine() {
	cout << "制作者：" << maker1 << " and " << maker2 << endl;
	return;
}
void mod_zero() {
	cout << endl;
	cout << "程序已经退出！" << endl;
	return;
}