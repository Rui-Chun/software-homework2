#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "core.h"

bool fomularCore::isOperate(char ch)
{
	auto it = find(ops.begin(), ops.end(), ch);
	if (it == ops.end())
		return false;
	else
		return true;
}

int fomularCore::Rank(char s)
{
	switch (s)
	{
	case '#':return -2;
	case '\0':return -1;
	case '(':return 0;
	case ')':return 0;//左右括号优先级小是为了不被其余任何运算符挤出
	case '+':
	case '-':return 1;//低优先级将挤出高优先级
	case '*':
	case '%':
	case '/':return 2;
	case '^':return 3; 
	default:return 4;
	}
}

double fomularCore::CalcNum(double a, double b, char c)
{
	switch (c)
	{
	case '+':return (a + b);
	case '-':return (a - b);
	case '*':return (a*b);
	case '/':return a / b;
	case '%':return (int)a % (int)b;
	case '^':return pow(a, b);
	default:return a;
	}
}

//从string中读取一个double数并push
void fomularCore::doublepush(stack<double> & st, string exp, int & pos)
{
	string fl;
	char c;

	while (!isOperate(exp[pos - 1]) && exp[pos - 1] != '\0')
	{
		//pos is the next position
		c = exp[pos - 1];
		fl.push_back(c);
		pos++;
	}
	pos--;
	st.push(atof(fl.c_str()));
}

double fomularCore::arthimetic(string & exp)
{

	//OPTR是运算符栈，OPEN是运算数栈
	exp.push_back('\0');
	stack<char> OPTR; OPTR.push('#');
	stack<double> OPEN;
	char ch = 'a', ch2;//'a'to init set ch
	double c1, c2;
	int pos = 0;



	while (ch != '\0' || OPTR.top() != '#')
	{
		if (ch != '\0')ch = exp[pos++];

		if (pos == 1 && ch == '+') { pos++; continue; }
		if (pos == 1 && ch == '-') { exp.insert(0, 1, '0'); pos--; continue; }
		//to deal with  '+8+1' '-8+2'

		if (!isOperate(ch) && ch != '\0')
		{
			//pos is the next position
			if (ch == ' ');//skip space
			else doublepush(OPEN, exp, pos);
			continue;
		}
		switch (ch)
		{
		case '(':OPTR.push(ch); break;
		case ')':
			ch2 = OPTR.top();
			while (ch2 != '(')
			{
				c1 = OPEN.top(); OPEN.pop();
				c2 = OPEN.top(); OPEN.pop();
				OPEN.push(CalcNum(c2, c1, ch2));
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
				c1 = OPEN.top(); OPEN.pop();
				c2 = OPEN.top(); OPEN.pop();
				OPEN.push(CalcNum(c2, c1, ch2));
				ch2 = OPTR.top();
			}
			if (ch != '\0')OPTR.push(ch);
			break;
		}//switch
	}//while
	 //cout << ' ' << OPEN.top();
	return OPEN.top();
}


//随机生成原始表达式，个数为expNum
vector<string> fomularCore::geneExp(int expNum)
{
	vector<string> res;
	string temp;
	int num, opch;
	string numstr;
	int loc1, loc2;//括号位置
	int opnum,bracketNum;

	for (int i = 0; i < expNum; i++)
	{
		opnum = random(1, maxopNum);//选定运算符个数

		for (int j = 0; j < opnum; j++)
		{
			num = random(1, range);//暂时不管0.。
			numstr = to_string(num);

			opch = ops[random(0, ops.size() - 3)];//选择运算符
			temp.append(numstr);
			temp.push_back(opch);
		}
		num = random(1, range);//暂时不管0.。
		numstr = to_string(num);
		temp.append(numstr);

		bracketNum = random(1, opnum);//选定括号对数

		while (bracketNum-- >0)
		{
			loc1 = random(0, temp.size() - 1);
			loc2 = random(loc1 + 1, temp.size());//括号位置

			while (loc1 != 0 && (!isNum(temp[loc1]) || !isOperate(temp[loc1 - 1])))
			{
				loc1--; 
			}
			temp.insert(loc1, 1, '(');

			while (loc2 != temp.size() && (!isNum(temp[loc2 - 1]) || !isOperate(temp[loc2])))
			{
				loc2++;
			}//移动括号到合适位置并插入
			temp.insert(loc2, 1, ')');
		}


		cout << temp << endl;
		res.push_back(temp);
		temp.clear();

	}
	return res;
}

