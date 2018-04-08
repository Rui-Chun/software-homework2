#include "core.h"
#include <iostream>


using namespace std;

int main()
{
	fomularCore test(10);
	string teststr;
	while (true)
	{
	//cin>>teststr;
	//cout<<test.Calc(teststr)<<endl;
		test.Generate();
		break;
	}


	return 0;
}

//int main()
//{
//	string path = "info.xml";
//	int QuestionNum;
//	int OperandNum;
//	int  NumRange;
//	string OperatorKind;
//	bool  ProperFraction;
//	bool  Decimal;
//	bool  Power;
//	ReadXml(path, QuestionNum, 
//OperandNum, NumRange, OperatorKind,
//ProperFraction, Decimal, Power);
//  cout<<QuestionNum<<endl;
//  cout<<OperandNum<<endl;
//  cout<<NumRange<<endl;
//  cout<<OperatorKind<<endl;
//  cout<<ProperFraction<<endl;
//  cout<<Decimal<<endl;
//  cout<<Power<<endl;
//}




//int main()
//{
//	string s;
//	vector<string> Test = {"123",")","(","+-*/()","+-/","+-(/","0123","99*0","&&-[]","abd","1","","9900","00"};
//	regex isNum("^[1-9]+[0-9]*$");
//	regex isOp("^[+]?[-]?[*]?[/]?[(]?$");
//	regex isBool("^[0-1]$");
//	int i;
//	int len = Test.size();
//	for(i = 0;i <len; ++i)
//	{
//		s = Test[i];
//		cout<<"current str is: "<<s<<endl;
//		bool isnum = regex_match(s.begin(),s.end(),isNum);
//	    bool isstr = regex_match(s.begin(),s.end(),isOp);
//	    bool isbool = regex_match(s.begin(),s.end(),isBool);
//		if(isnum)
//	      cout<<"isNum  "<<endl;
//	    else
//	      cout<<"notNum  "<<endl;
//	      
//	    if(isstr)
//	      cout<<"isOp "<<endl;
//	    else
//	      cout<<"notOp "<<endl;
//	      
//	    if(isbool)
//	      cout<<"isBool "<<endl;
//	    else
//	      cout<<"notBool "<<endl;
//	    
//	}
//	
//	
//	 
//}
