#include<iostream>
#include<string>
#include<math.h>
#include"list.h"
#include"angle.h"
//ͷ�ļ�
//�����ռ�
using namespace std;
//�������
int main() {
head://���ؽڵ�
	char mod;//ģʽ
	printf_main_menu();//�˵��������
	cin >> mod;//����mod
	switch (mod) {
	case '1':
		mod_one();//�պϵ��߼���
		goto head;
	case '2':
		mod_tow();//���������
		goto head;
	case '3':
		mod_three();//�Ƕȼ���
		goto head;
	case '4':
		mod_four();//�������ģʽ
		goto head;
	case '9':
		mod_nine();
		goto head;
	case '0':
		mod_zero();
		return 0;//�˳�����
	default:
		cout << "��������ȷ�Ĳ˵��ţ�" << endl;
		goto head;
	}
	return 0;
}