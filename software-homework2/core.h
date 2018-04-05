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
	int value;
	bool chFlag;//if true��value is ascii
	fomularNode* lchild;
	fomularNode* rchild;
	fomularNode() :value(0),chFlag(false),lchild(NULL),rchild(NULL){}
	fomularNode(int val, bool flag, fomularNode* lch=NULL, fomularNode* rch=NULL)
	{
		value = val;
		chFlag = flag;
		lchild = lch;
		rchild = rch;
	}
};

class fomularCore
{
private:
	vector<fomularNode*> fomulars;
	vector<char> ops = {'+','-','*','/','(',')'};//all ops
	int maxopNum = 5;
	int range = 1000;//���ʽÿ����������
	int precise = 2;//������ȣ���û����
	int fomuNum;//���ʽ����

	bool deletefomu(fomularNode* ro)
	{
		if (ro->lchild != NULL)
			deletefomu(ro->lchild);
		if (ro->rchild != NULL)
			deletefomu(ro->rchild);
		delete ro;
		return true;
	}

	//Calc depending func
	bool isOperate(char ch);
	int Rank(char s);
	double CalcNum(double a, double b, char c);
	void doublepush(stack<double> & st, string exp, int & pos);
	double arthimetic(string & exp);
	//Calc depending func

	bool isNum(char ch)
	{
		if (ch <= '9'&&ch >= '0')
			return true;
		else
			return false;
	}
	int random(int a, int b)//random int [a,b]
	{
		return (rand() % (b - a + 1)) + a;

	}

	//ԭʼ���ʽת��׺������
	bool toPostTree(vector<string> & fomus);

	//���ݸ��ֹ����жϲ����������
	bool toJudgeTree()
	{

	}

	vector<string> geneExp(int expNum);//�������ԭʼ���ʽ

public:
	fomularCore(int Num=10)//Num��Ҫ���ɵı��ʽ����
	{
		srand((unsigned int)(time(NULL)));

		fomuNum = Num;
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
		//�����ǲ���
		vector<string> rawFomu;

		rawFomu = geneExp(5);
		for (size_t i = 0; i < rawFomu.size(); i++)
		{
			cout << arthimetic(rawFomu[i]) << endl;
		}

		toPostTree(rawFomu);

		return true;
	}

};