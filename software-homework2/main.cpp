#include "core.h"
#include <iostream>

using namespace std;

int main()
{
	fomularCore test(3000);//��ʼ������ʽ�Ӹ���
	vector<string> out;
	vector<string> outRes;
	vector<char> ops = { '+','-','*','/','(',')' };
	test.setting(300, 6, 20, ops, 1, 3);
	out=test.Generate();
	outRes = test.getRes();


	return 0;
}