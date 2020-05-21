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
		int count = 0，err = 0;
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
	T(count,err);
	if(expr
}
void Manage::T(string expr,int& count,int& err)
{

}
void Manage::F(string expr,int& count,int& err)
{

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
