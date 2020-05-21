#include"Polynomial.h"
using namespace std;
//給系數數組賦值
//從最高次（下標爲０）到最低次（下標爲size - 1）
void Polynomial::set(const double p_ce,const int i)
{
	ce[i] = p_ce;
	ex[i] = size - 1 - i;
}
Polynomial::Polynomial(int max_size)
{
	//name = p_name;
	size = max_size;
	ce = new double[size];
	ex = new int[size];
}
Polynomial::Polynomial(const Polynomial& p)
{
	//name = p.name;
	size = p.size;
	ce = new double[p.size];
	ex = new int[size];
	for(int i = 0;i < size;i++){
		ce[i] = p.ce[i];
		ex[i] = p.ex[i];
	}
}
Polynomial Polynomial::operator + (const Polynomial& p)
{
	return *this;
}
Polynomial Polynomial::operator * (const Polynomial& p)
{
	return *this;
}
Polynomial Polynomial::derivative()
{
	return *this;
}
Polynomial Polynomial::integral(const double a,const double b)
{
	return *this;
}
Polynomial::~Polynomial()
{
	delete ce;
	delete ex;
}

