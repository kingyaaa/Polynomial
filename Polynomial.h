#include<iostream>
#include<string>
#include<cmath>
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
	Polynomial(int max_size);//構造函數
	Polynomial(const Polynomial& p);//拷貝構造函數
	Polynomial operator + (const Polynomial& p);
	Polynomial operator * (const Polynomial& p);
	Polynomial derivative();
	Polynomial integral(const double a,const double b);
	void set(double p_ce,int i);
	friend ostream &operator << (ostream &output,const Polynomial &p)
	{
		if(p.size == 1){
			output << p.ce[0];
			return output;
		}
		if(p.size == 2){
			output << p.ce[0] << "x";
		}
		if(p.size > 2)
			output << p.ce[0] << "x^" << p.ex[0];
	    for(int i = 1;i < p.size;i++){
			if(p.ce[i] == 0)
				continue;
			if(p.ex[i] > 1){
				if(p.ce[i] > 1)
					output << "+" << p.ce[i] <<"x^" << p.ex[i];
				if(p.ce[i] == 1)
					output << "+" << "x^"<< p.ex[i];
				if(p.ce[i] < 0)
					output << p.ce[i] << "x^" << p.ex[i];
			}
			if(p.ex[i] == 1){
				if(p.ce[i] > 1)
					output << "+" << p.ce[i] << "x";
				if(p.ce[i] == 1)
					output << "x";
				if(p.ce[i] < 1)
					output << p.ce[i] << "x";
			}
			if(p.ex[i] == 0){
				if(p.ce[i] > 0)
					output << "+" << p.ce[i];
				if(p.ce[i] < 0)
					output << p.ce[i];
			}
		}
		return output;
	}
	~Polynomial();
};
