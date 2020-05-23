#include"Manage.h"
using namespace std;
Manage::Manage()
{

}
void Manage::HybridOperation()
{
	bool op = true;
	char reply;
	while(op){
		cout << "請輸入表達式:";
		string expr;
		cin >> expr;
		int count = 0;
		int err = 1;
		E(expr,count,err);
		if(err == -1){
			cout << "表達式錯誤，是否重新輸入(y/n):";
			cin >> reply;
			if(reply != 'y')
				op = false;
		}
		if(err == 1){
			//計算
			cout<<"運算成功！是否繼續運算(y/n):";
			cin >> reply;
			if(reply != 'y')
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
		count++;
		return;
	}
	if(expr[count] == '$'){
		count++;
		if(expr[count] == '['){
			count++;
			if(expr[count] >='0' && expr[count] <= '9'){
				if(expr[++count] == ','){
					count++;
					if(expr[count] >= '0' && expr[count] <= '9'){
						if(expr[++count] == ']'){
							count++;
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
		if(flag)
			count--;
		if(expr[count] != '+' && expr[count] != '*' && expr[count] != ')')
		{
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
	 	 char reply;
		 cin >> reply;
         if(reply != 'y'){
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
