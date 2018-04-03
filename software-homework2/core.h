#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <ctime>
using namespace std;

class fomularNode
{
public:
	char op;
	int lopNum;
	int ropNum;
	fomularNode* lchild;
	fomularNode* rchild;
	fomularNode() :op('\0'), lopNum(0), ropNum(0), lchild(NULL), rchild(NULL){}

};

class fomularCore
{
private:
	vector<fomularNode*> fomulars;
	vector<char> ops = {'+','-','*','/','(',')'};//all ops
	long range = 1000;
	int precise = 2;

	bool deletefomu(fomularNode* ro)
	{
		if (ro->lchild != NULL)
			deletefomu(ro->lchild);
		if (ro->rchild != NULL)
			deletefomu(ro->rchild);
		delete ro;
		return true;
	}

	bool isOperate(char ch);
	int Rank(char s);
	double CalcNum(double a, double b, char c);
	void doublepush(stack<double> & st, string exp, int & pos);
	double arthimetic(string & exp);
	//Calc depending func

	int random(int a, int b)//random int [a,b]
	{
		//srand((unsigned int)(time(NULL)));
		return (rand() % (b - a + 1)) + a;

	}


	
public:
	fomularCore(int Num)
	{
		for (int i = 0; i < Num; i++)
		{
			fomularNode* temp = new fomularNode;
			fomulars.push_back(temp);
		}
	}

	~fomularCore()
	{
		int Num = fomulars.size();
		for (int i = 0; i < Num; i++)
		{
			fomularNode* temp = fomulars[i];
			deletefomu(temp);
		}
	}

	double Calc(string inputFomu)
	{
		return arthimetic(inputFomu);
	}
	
	bool Generate()
	{
		int num = fomulars.size();
		string test;
		for (int i = 0; i < num; i++)
		{
			int opnum = random(1,ops.size());

			for (int j = 0; j < opnum; j++)
			{
				char num1 = random(1, 9)+'0';
				char opch = ops[random(0, ops.size()-3)];
				test.push_back(num1);
				test.push_back(opch);
			} 
			char num1 = random(0, 9) + '0';
			test.push_back(num1);


			cout << test << endl;
			test.clear();

		}
		return true;
	}

};