#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
#include<map>
#include<vector>
#include<stack>
using namespace std;
class Polynomial
{
private:
	//string name;
	int size;//長度
	double *ce;//系數
	int *ex;//指數
public:
	Polynomial();//默認構造函數
	Polynomial(int max_size);//構造函數
	Polynomial(const double c[],const int x[],const int n);
	Polynomial(const Polynomial& p);//拷貝構造函數
	Polynomial& operator = (const Polynomial& p);
	Polynomial operator + (const Polynomial& p);
	Polynomial operator * (const Polynomial& p);
	Polynomial derivative();
	Polynomial integral(const double a,const double b);
	void set(double p_ce,int i);
	friend ostream& operator << (ostream& output,const Polynomial& p);
	~Polynomial();
};
