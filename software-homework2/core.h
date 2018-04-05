#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <ctime>
#define MAX_FOMU_NUM 200

using namespace std;

class fomularNode
{
public:
	int value;
	bool chFlag;//if true，value is ascii
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
	vector<char> ops = {'+','-','*','/','(',')'};//all ops 需要保持最后两个是括号
	int maxopNum = 5;
	int range = 20;//表达式每个数的上限
	int precise = 2;//输出精度（还没处理
	int fomuNum;//表达式个数
	double result[MAX_FOMU_NUM];
	bool okFlag[MAX_FOMU_NUM];


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
	bool computeTree(fomularNode* ro,double &res)//计算表达式二叉树，若不违反非负，返回res结果
	{
		double re1=0, re2=0;
		bool b1, b2;
		if (ro == NULL) return false;
		if (ro->chFlag == true)
		{
			b1=computeTree(ro->lchild, re1);
			b2=computeTree(ro->rchild, re2);
			res = CalcNum(re1, re2, char(ro->value));
			if (res < 0)return false;
			else return b1 && b2;
		}
		else
		{
			res = ro->value;
			return true;
		}
	}

	//原始表达式转后缀并建树
	bool toPostTree(vector<string> & fomus);

	bool isSameTree(fomularNode* ro1, fomularNode* ro2)
	{
		if (ro1 == NULL && ro2 == NULL)
			return true;
		else if (ro1 == NULL || ro2 == NULL)
			return false;

		if (ro1->value != ro1->value)
			return false;
		else
			return isSameTree(ro1->rchild, ro2->rchild) && isSameTree(ro1->rchild, ro2->rchild);

	}

	bool isEqualTree(fomularNode* fo1,fomularNode* fo2)
	{
		bool bl1, bl2;
		if (isSameTree(fo1, fo2))
			return true;
		else
		{
			bl1 = isEqualTree(fo1->lchild, fo2->lchild) && isEqualTree(fo1->rchild, fo2->rchild);
			bl2 = isEqualTree(fo1->rchild, fo2->lchild) && isEqualTree(fo1->lchild, fo2->rchild);
			return bl1 || bl2;
		}

	}


	//根据各种规则判断并处理二叉树
	//采用先随机生成两倍或以上的原始表达式，再从里面挑选符合要求的,由okFlag决定
	bool toJudgeTree()
	{
		int rfomuNum = fomulars.size();

		int regene=0;

		for (int i = 0; i < rfomuNum; i++)
		{
			okFlag[i] = computeTree(fomulars[i], result[i]);//判断无负
			for (int j = 0; j < i; j++)                   //先判断答案是否一致，一致才有可能是相等表达式
			{
				if (result[i] == result[j] && isEqualTree(fomulars[i], fomulars[j]))
				{
					okFlag[i] = false;
					break;
				}
			}
		}
		return true;
	}

	vector<string> geneExp(int expNum);//随机生成原始表达式

	void treeTostr(fomularNode* ro,string &pre)
	{

		if (ro == NULL)return;
		if (ro->chFlag == false)//只看左边就行，不考虑括号
		{
			pre.append(to_string(ro->value));
			return;
		}


		if(ro->lchild->chFlag==false)
			treeTostr(ro->lchild, pre);
		else if (Rank(ro->value) > Rank(ro->lchild->value))
			{
			pre.push_back('(');
			treeTostr(ro->lchild, pre);
			pre.push_back(')');
			}
		else 
			treeTostr(ro->lchild, pre);

		pre.push_back(char(ro->value));

		if (ro->rchild->chFlag == false)
			treeTostr(ro->rchild, pre);
		else if (Rank(ro->value) >= Rank(ro->rchild->value))
		{
			pre.push_back('(');
			treeTostr(ro->rchild, pre);
			pre.push_back(')');
		}
		else
			treeTostr(ro->rchild, pre);

		return;
	}

	vector<string> fomusToStr(vector<fomularNode*> jFomus)
	{
		string tempstr;
		vector<string> outstr;
		for (int i = 0; i < fomuNum; i++)
		{
			treeTostr(jFomus[i], tempstr);
			outstr.push_back(tempstr);
			tempstr.clear();
		}
		return outstr;
	}

public:
	fomularCore(int Num=10)//Num是要生成的表达式个数
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
	
	vector<string> Generate()
	{
		//以下是测试
		vector<string> rawFomu;
		vector<fomularNode*> judgedFomu;
		vector<string> finalFomu;
		double temp;

		rawFomu = geneExp(3*fomuNum);

		for (size_t i = 0; i < rawFomu.size(); i++)
		{
			cout << rawFomu[i] << '=';
			cout << arthimetic(rawFomu[i]) << endl;
		}

		toPostTree(rawFomu);
		toJudgeTree();

		for (int i = 0; i < fomulars.size(); i++)
		{
			if (okFlag[i] == true)
				judgedFomu.push_back(fomulars[i]);
		}
		
		cout << endl << judgedFomu.size();
		cout << endl << endl;

		finalFomu=fomusToStr(judgedFomu);

		return finalFomu;
	}

};