#include "core.h"
#include <iostream>

using namespace std;

int main()
{
	//fomularCore test(3000);//初始化传入式子个数
	//vector<string> out;
	//vector<string> outRes;
	//string ops="+-*/^()";
	//test.setting(10000, 6, 20, ops, 1, 3);
	//out=test.Generate();
	//outRes = test.getRes();

	fomularCore test(100);//这里需要初始化式子个数
	vector<string> out, Res;
	string temp;
	string ops = "+-*/^()";//最后两个要为括号

	test.setting(4000, 10, 5,10, ops, true, 4);//参数分别为 式子个数，运算符个数，
											 //操作数最大范围，运算符，是否支持分数，小数精度（最多6
											 //test.settingXml("info.xml"); 也可以使用xml文件

	out = test.Generate();//生成表达式，返回vector

	temp = test.Calc("2+33");//可选单独功能，计算式子

	Res = test.getRes();//返回结果vector<string>

	test.Clear();
	out=test.Generate();

	Res = test.getRes();

	cout << out[10];



	return 0;
}