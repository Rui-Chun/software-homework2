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
	int maxopNum = 5;
	int range = 1000;//表达式每个数的上限
	int precise = 2;//输出精度（还没处理
	int fomuNum;//表达式个数

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

	//原始表达式转后缀并建树(还没写好)
	bool toPostTree(vector<string> fomus)
	{
		vector<string> res;
		string exp,num;
		stack<char> OPTR; 
		stack<char> OPEN;



		for (size_t i = 0; i < fomus.size(); i++)
		{
			exp = fomus[i];
			//OPTR是运算符栈，OPEN是运算数栈
			exp.push_back('\0');
			OPTR.push('#');

			char ch = 'a', ch2;//'a'to init set ch
			int pos = 0;


			while (ch != '\0' || OPTR.top() != '#')
			{
				if (ch != '\0')ch = exp[pos++];

				if (pos == 1 && ch == '+') { pos++; continue; }
				if (pos == 1 && ch == '-') { exp.insert(0, 1, '0'); pos--; continue; }
				//to deal with  '+8+1'

				if (!isOperate(ch) && ch != '\0')
				{
					//pos is the next position
					if (ch == ' ');//skip space
					else
					{
						while (!isOperate(exp[pos - 1])&&exp[pos-1]!='\0')
						{
							OPEN.push(exp[pos - 1]);
							pos++;
						}
						pos--;
					}
					continue;
				}
				switch (ch)
				{
				case '(':OPTR.push(ch); break;
				case ')':
					ch2 = OPTR.top();
					while (ch2 != '(')
					{
						OPEN.push(ch2);
						OPTR.pop();
						ch2 = OPTR.top();
					}
					OPTR.pop();
					break;
				default:
					ch2 = OPTR.top();
					while (Rank(ch2) >= Rank(ch))
					{
						OPTR.pop();
						OPEN.push(ch2);
						ch2 = OPTR.top();
					}
					if (ch != '\0')OPTR.push(ch);
					break;
				}//switch
			}//while
			 //cout << ' ' << OPEN.top();
			while (!OPEN.empty())
			{
				res[i].insert(0, 1, OPEN.top());
				OPEN.pop();
			}
		}
		return true;
	}

	vector<string> geneExp(int expNum);//随机生成原始表达式

public:
	fomularCore(int Num=10)//Num是要生成的表达式个数
	{
		srand((unsigned int)(time(NULL)));

		fomuNum = Num;
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
		//以下是测试
		vector<string> rawFomu;

		rawFomu = geneExp(5);
		for (size_t i = 0; i < rawFomu.size(); i++)
		{
			cout << arthimetic(rawFomu[i]) << endl;
		}
		return true;
	}

};