#include"Polynomial.h"
using namespace std;
class Manage
{
private:
	vector<pair<string,int> >type;
	vector<string>output;
	map<string,Polynomial>search;
public:
	Manage();
	void input();
	void check();
	void choose();
	void E(string expr,int& count,int& err);
	void T(string expr,int& count,int& err);
	void F(string expr,int& count,int& err);
	void ConvertPostfix(string expr);
	Polynomial ComputePostfix(vector<string>&output);
	void HybridOperation();
	int prior(string opt);
	double stringToDouble(const string& str);
	void isDouble(string expr,int& i);
	bool isOperator(string str);
	bool isOperand(string str);
	void getTwodouble(string str,double& a,double& b);
	void popTwoOperand(stack<Polynomial>&s,Polynomial& first,Polynomial& second);
	void WordAndType();
	~Manage();
};
