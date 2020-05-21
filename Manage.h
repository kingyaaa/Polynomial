#include"Polynomial.h"
using namespace std;
class Manage
{
private:
	vector<pair<string,int> >type;
	map<string,Polynomial>search;
public:
	Manage();
	void input();
	void check();
	void E(string expr,int& count,int& err);
	void T(string expr,int& count,int& err);
	void F(string expr,int& count,int& err);
	void HybridOperation();
	void WordAndType();
	~Manage();
};
