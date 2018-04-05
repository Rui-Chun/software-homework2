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
	case ')':return 0;//�����������ȼ�С��Ϊ�˲��������κ����������
	case '+':
	case '-':return 1;//�����ȼ������������ȼ�
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

//��string�ж�ȡһ��double����push
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

	//OPTR�������ջ��OPEN��������ջ
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


//�������ԭʼ���ʽ������ΪexpNum
vector<string> fomularCore::geneExp(int expNum)
{
	vector<string> res;
	string temp;
	int num, opch;
	string numstr;
	int loc1, loc2;//����λ��
	int opnum,bracketNum;

	for (int i = 0; i < expNum; i++)
	{
		opnum = random(1, maxopNum);//ѡ�����������

		for (int j = 0; j < opnum; j++)
		{
			num = random(1, range);//��ʱ����0.��
			numstr = to_string(num);

			opch = ops[random(0, ops.size() - 3)];//ѡ�������
			temp.append(numstr);
			temp.push_back(opch);
		}
		num = random(1, range);//��ʱ����0.��
		numstr = to_string(num);
		temp.append(numstr);

		bracketNum = random(1, opnum);//ѡ�����Ŷ���

		while (bracketNum-- >0)
		{
			loc1 = random(0, temp.size() - 1);
			loc2 = random(loc1 + 1, temp.size());//����λ��

			while (loc1 != 0 && (!isNum(temp[loc1]) || !isOperate(temp[loc1 - 1])))
			{
				loc1--; 
			}
			temp.insert(loc1, 1, '(');

			while (loc2 != temp.size() && (!isNum(temp[loc2 - 1]) || !isOperate(temp[loc2])))
			{
				loc2++;
			}//�ƶ����ŵ�����λ�ò�����
			temp.insert(loc2, 1, ')');
		}


		cout << temp << endl;
		res.push_back(temp);
		temp.clear();

	}
	return res;
}

