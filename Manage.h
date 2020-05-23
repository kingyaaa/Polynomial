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
	void E(string expr,int& count,int& err);
	void T(string expr,int& count,int& err);
	void F(string expr,int& count,int& err);
	void ConvertPostfix(string expr);
	string ComputePostfix(vector<string>&output);
	void HybridOperation();
	int prior(string opt);
	bool isDouble(string expr,int& i);
	bool isOperator(string str);
	bool isOperand(string str);
	void WordAndType();
	~Manage();
};
