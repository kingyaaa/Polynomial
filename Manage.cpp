#include"Manage.h"
using namespace std;
Manage::Manage()
{

}
void Manage::choose()
{
	while(true){
		int op;
		cout << "1.輸入	2.混合運算	3.查看"<< endl;
		cout << "選擇:";
		cin >> op;
		switch(op){
			case 1:{ input(); break;}
			case 2:{ HybridOperation(); break;}
			case 3:{ check(); break;}
			default:
				  break;
		}
	}
}
void Manage::HybridOperation()
{
	bool op = true;
	string reply;
	while(op){
		cout << "請輸入表達式:";
		string expr;
		cin >> expr;
		int count = 0;
		int err = 1;
		while(count != expr.size()){
			if(err == -1)
				break;
			E(expr,count,err);
		}
		if(err == -1){
			cout << "表達式錯誤，是否重新輸入(y/n):";
			cin >> reply;
			if(reply != "y" && reply != "Y")
				op = false;
		}
		if(err == 1){
			//進入計算部分，先將中綴表達式轉化爲後綴表達式
			ConvertPostfix(expr);
			cout << endl;
			//最後一步:計算後綴表達式的值
			cout << expr << " = " << ComputePostfix(output) << endl;
			
			cout<<"運算成功！是否繼續運算(y/n):";
			cin >> reply;
			if(reply != "y" && reply != "Y")
				op = false;
		}
	}
}
void Manage::E(string expr,int& count,int& err)
{
	T(expr,count,err);
	if(expr[count] == '+')
	{
		count++;
		T(expr,count,err);
	}
}
void Manage::T(string expr,int& count,int& err)
{
	F(expr,count,err);
	if(expr[count] == '*')
	{
		count++;
		F(expr,count,err);
	}
}
void Manage::F(string expr,int& count,int& err)
{
	if(expr[count] == '(')
	{
		count++;
		E(expr,count,err);
		if(expr[count] != ')')
		{
			err = -1;
			return;
		}
		if(expr[count] == ')'){
			count++;
			if(expr[count] == '!')
				count++;
			if(count != expr.size()){
				if(expr[count] != ')' && expr[count]!= '+' && expr[count] != '*' && expr[count] != '!'){
					err = -1;
					return;
				}
			}
		}
		return;
	}
	if(expr[count] == '$'){
		count++;
		if(expr[count] == '['){
			count++;
			if((expr[count] >='0' && expr[count] <= '9') || expr[count] == '.'){
				isDouble(expr,count);
				if(expr[count] == ','){
					count++;
					if((expr[count] >= '0' && expr[count] <= '9') || expr[count] == '.'){
						isDouble(expr,count);
						if(expr[count] == ']'){
							count++;
							int afterDing = 0;
							if(count != expr.size()){
								if(expr[count] == '(' ||(expr[count] >= 'A' && expr[count] <= 'Z')||(expr[count] >= 'a' && expr[count] <= 'z'))
								{
									afterDing = 1;
								}
								if(!afterDing){
									err = -1;
									return;
								}
							}
							E(expr,count,err);
						}
						else{
							err = -1;
							return;
						}
					}
					else{
						err = -1;
						return;
					}
				}
				else{
					err = -1;
					return;
				}
			}
			else{
				err = -1;
				return;
			}
		}
		else{
			err = -1;
			return;
		}
		return;
	}
	if((expr[count] >='A' && expr[count] <= 'Z') ||(expr[count] >= 'a' && expr[count] <= 'z'))
	{
		string tmp;
		tmp.clear();
		tmp.push_back(expr[count]);
		count++;
		int flag = 0;
		while((expr[count] >='A' && expr[count] <= 'Z') ||(expr[count] >= 'a' && expr[count] <= 'z'))
		{
			tmp.push_back(expr[count]);
			count++;
			flag = 1;
		}
		//查找有沒有這個英文串的存在
		map<string,Polynomial>::iterator it = search.find(tmp);
		if(it == search.end())
		{
			err = -1;
			return;
		}
		if(expr[count] == '!'){
			count++;
			if(count != expr.size())
			{
				if(expr[count] != '+' && expr[count] != '*' && expr[count] != ')'){
					err = -1;
					return;
				}
			}
		}
		//多項式後面只能是雙目運算符，求導符，或右括號
		if(count != expr.size()){
			if(expr[count] != ')' && expr[count]!= '+' && expr[count] != '*' && expr[count] != '!'){
                 err = -1;
				 return;
			}
		}
	}
	//if((expr[count] >='A' && expr[count] <= 'Z') ||(expr[count] >= 'a' && expr[count] <= 'z'))
	//{
	//	count++;
	//	if(expr[count] == '!')
	//		count++;
	//}
		/*******************************
		if(expr[count] != '+' && expr[count] != '*' && expr[count] != ')')
		{
			err = -1;
			return;
		}*******************************/
	else{
		err = -1;
		return;
	}
	return;
}
void Manage::isDouble(string expr,int& i)
{
	string tmp;
	if(expr[i] >= '0' && expr[i] <= '9'){
		while(expr[i] >= '0' && expr[i] <= '9'){
			tmp.push_back(expr[i]);
			++i;
		}
		if(expr[i] == '.'){
			tmp.push_back(expr[i]);
			++i;
			//以 , 結尾
			if(expr[i] == ',' || expr[i] == ']'){
				//tmp.push_back('0');
				return;
			}
			if(expr[i] >= '0' && expr[i] <= '9'){
				while(expr[i] >= '0' &&  expr[i] <= '9'){
					tmp.push_back(expr[i]);
					++i;
				}
				return;
			}
		}
		return;
	}
	//以 . 開頭
	if(expr[i] == '.'){
		//tmp.push_back('0');
		tmp.push_back(expr[i]);
		++i;
		if(expr[i] >= '0' && expr[i] <= '9'){
			while(expr[i] >= '0' && expr[i] <= '9'){
				tmp.push_back(expr[i]);
				++i;
			}
			return;
		}
	}
}
void Manage::WordAndType()
{
	string word;
	word = "+";
	type.push_back(make_pair(word,1));
	word = "*";
	type.push_back(make_pair(word,2));
	word = "$";
	type.push_back(make_pair(word,3));
	word = "!";	
	type.push_back(make_pair(word,4));
	word = "(";	
	type.push_back(make_pair(word,5));
	word = ")";
	type.push_back(make_pair(word,6));
}
bool Manage::isOperator(string str)
{
	if(str[0] == '$')
		return true;
	if(str == "+"||str == "*"|| str == "!")
		return true;
	return false;
}
bool Manage::isOperand(string str)
{
	if((str[0] >= 'A' && str[0] <= 'Z')|| (str[0] >= 'a' && str[0] <= 'z'))
		return true;
	return false;
}
int Manage::prior(string opt)
{
	if(opt == "+")
		return 1;
	else if(opt == "*")
		return 2;
	else if(opt == "!")
		return 4;
	else if(opt[0] == '$')
		return 3;
	else
		return 0;
}
//對十分正確的中綴表達式轉換爲後綴表達式
void Manage::ConvertPostfix(string expr)
{
	//vector<string>output:後綴表達式
	//每次都先做一下清空
	output.clear();
	string tmp;
	stack<string>s;
	for(int i = 0;i < expr.size();i++)
	{
		tmp.clear();
		tmp.push_back(expr[i]);
		//先把定積分符號整塊檢測出來:$[a,b]
		if(expr[i] == '$')
		{
			i++;
			while(expr[i] != ']'){
				tmp.push_back(expr[i]);
				i++;
			}
			tmp.push_back(expr[i]);
		}
		if((expr[i] >= 'A'&& expr[i] <= 'Z') || (expr[i] >= 'a' && expr[i] <= 'z')){
			i++;
			while((expr[i] >= 'A'&& expr[i] <= 'Z') || (expr[i] >= 'a' && expr[i] <= 'z')){
				tmp.push_back(expr[i]);
				i++;
			}
			i--;
		}
		if(isOperand(tmp))//暫時認爲表達式的名稱只是一個字母: F
		{
			output.push_back(tmp);
		}
		if(isOperator(tmp))//	! | + | *
		{
			while(!s.empty()&& isOperator(s.top()) && prior(s.top()) >= prior(tmp))
			{
				output.push_back(s.top());
				s.pop();
			}
			s.push(tmp);
		}
		if(tmp == "("){				// (
			s.push(tmp);
		}
		if(tmp == ")"){				// )
			while(s.top()!="("){
				output.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
	}
	while(!s.empty()){
		output.push_back(s.top());
		s.pop();
	}
	//輸出看看對不對
	vector<string>::iterator it;
	for(it = output.begin();it!=output.end();it++)
		cout << *it;
}
void Manage::popTwoOperand(stack<Polynomial>&s,Polynomial& first,Polynomial& second)
{
	first = s.top();
	s.pop();
	second = s.top();
	s.pop();
}
//計算後綴表達式，返回一個結果(多項式)
Polynomial Manage::ComputePostfix(vector<string>&output)
{
	//Polynomial fir,sec;
	map<string,Polynomial>::iterator pv;  //search//找到string對應的對象
	stack<Polynomial>s;
	vector<string>::iterator it;
	for(it = output.begin();it != output.end();it++){
		//操作數直接入棧
		if(((*it)[0] >= 'A' && (*it)[0] <= 'Z') || ((*it)[0] >= 'a' && (*it)[0] <= 'z'))
		{
			pv = search.find(*it);
			s.push(pv->second);
		}
		if((*it) == "+"){
			Polynomial fir,sec;
			popTwoOperand(s,fir,sec);
			s.push(fir + sec);
		}
		if((*it) == "*"){
			Polynomial fir,sec;
			popTwoOperand(s,fir,sec);
			s.push(fir * sec);
		}
		if((*it) == "!"){
			Polynomial fir;
			fir = s.top();
			s.pop();
			Polynomial tmp = fir.derivative();
			s.push(tmp);//求導，返回一個新的多項式對象
		}
		if((*it)[0] == '$'){
			Polynomial fir;
			double a,b;
			getTwodouble(*it,a,b);
			fir = s.top();
			s.pop();
			s.push(fir.integral(a,b));
		}
	}
	Polynomial result = s.top();
	s.pop();
	return result;
}
double Manage::stringToDouble(const string& str)
{
	double d;
	stringstream ss;
	ss << str;
	ss >> d;
	return d;
}
void Manage::getTwodouble(string str,double& a,double& b)
{
	string tmp1,tmp2;
	int i = 2,flag = 1;
	while(str[i] != ',')
	{
		if(str[i] == '.' && flag){
			tmp1.push_back('0');
			tmp1.push_back('.');
			i++;
			flag = 0;
		}
		else if(str[i] == '.'&& str[i+1] == ',')
		{
			tmp1.push_back('.');
			tmp1.push_back('0');
			i++;
		}
		else{	
			tmp1.push_back(str[i]);
			i++;
		}
	}
	a = stringToDouble(tmp1);
	i++;
	int index = i;
	flag = 1;
	while(str[i] != ']')
	{
		if(str[index] == '.'&& flag){
			tmp2.push_back('0');
		    tmp2.push_back('.');			
			i++;
			flag = 0;
         }
         else if(str[i] == '.'&& str[i+1] == ']')
         {    
			 tmp2.push_back('.');
             tmp2.push_back('0');
             i++;
         }
         else{
			 tmp2.push_back(str[i]);
             i++;
         }
	}
	b = stringToDouble(tmp2);
}
void Manage::input()
{
	 bool in = true;
	 while(in){
		 cout << "輸入多項式的長度:";			  
		 int max_size;
		 cin >> max_size;
		 Polynomial p(max_size);
         cout << "輸入各項系數:";
         int p_ce;
         for(int i = 0;i < max_size;i++){
             cin >> p_ce;
             p.set(p_ce,i);
         }
         cout << "爲多項式命名:";
         string p_name;
         cin >> p_name;
		 //查看是否已經有過多項式叫這個名字
		 if(!search.empty()){
			map<string,Polynomial>::iterator it = search.find(p_name);
			while(it != search.end()){
				cout << "該名字已經被使用過！"<<endl;
				cout << "請重新輸入多項式名字:";
				cin >> p_name;
			    it = search.find(p_name);
			 }
		 }
		 search.insert(pair<string,Polynomial>(p_name,p));
		 cout << "輸入成功，是否繼續輸入(y/n):";
	 	 string reply;
		 cin >> reply;
         if(reply != "y"&& reply != "Y"){
             in = false;
         }
	 }
}
void Manage::check()
{
	cout << "輸入多項式的名字:";
	string name;
	cin >> name;
	map<string,Polynomial>::iterator it = search.find(name);
	if(it != search.end()){
		cout << name << " = ";
		cout << it->second << endl;
	}
	else
		cout << "Not found!"<< endl;
}
Manage::~Manage()
{

}
