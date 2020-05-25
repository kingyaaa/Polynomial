#include"Polynomial.h"
using namespace std;
//給系數數組賦值
//從最高次（下標爲０）到最低次（下標爲size - 1）
void Polynomial::set(const double p_ce,const int i)
{
	ce[i] = p_ce;
	ex[i] = size - 1 - i;
	//cout << ce[i] << endl;
	//cout << ex[i] << endl;
}
Polynomial::Polynomial()
{
	size = 0;
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
Polynomial::Polynomial(const double c[],const int x[],const int n)
{
	size = n;
	ce = new double[size];
	ex = new int[size];
	for(int i = 0; i < size;i++)
	{
		ce[i] = c[i];
		ex[i] = x[i];
	}
}
Polynomial& Polynomial::operator = (const Polynomial& p)
{
	if(this == &p)
		return *this;
	size = p.size;
	ce = new double[size];
	ex = new int[size];
	for(int i = 0;i < size;i++){
		ce[i] = p.ce[i];
		ex[i] = p.ex[i];
	}
	return *this;
}
/*
Polynomial Polynomial::operator + (const Polynomial& p)
{
	int sum_size = size + p.size;
	double sum_ce[sum_size];
	int sum_ex[sum_size];
	int i = 0,j = 0,count = 0;
	while(i < size && j < p.size)
	{
		if(ex[i] == p.ex[j])
		{
			sum_ex[count] = ex[i];
			sum_ce[count] = ce[i] + p.ce[j];
			count++;
			i++;
			j++;
		}
		else if(ex[i] > p.ex[j]){
			sum_ex[count] = ex[i];
			sum_ce[count] = ce[i];
			count++;
			i++;
		}
		else
		{
			sum_ex[count] = p.ex[j];
			sum_ce[count] = p.ce[j];
			count++;
			j++;
		}
	}
	Polynomial tmp(sum_ce,sum_ex,count);
	return tmp;
}*/
Polynomial Polynomial::operator + (const Polynomial& p)
{
	if(size >= p.size){
		Polynomial sum = *this;
		for(int i = 0; i < p.size;i++){
			for(int j = 0; j < size;j++){
				if(sum.ex[j] == p.ex[i])
					sum.ce[j] += p.ce[i];
			}
		}
		return sum;
	}
	else{
		Polynomial sum = p;
		for(int i = 0;i < size;i++){
			for(int j = 0;j < p.size;j++){
				if(sum.ex[j] == ex[i])
					sum.ce[j] += ce[i];
			}
		}
		return sum;
	}
}
Polynomial Polynomial::operator * (const Polynomial& p)
{
	Polynomial temp = *this;
	int sum_size = temp.ex[0] + p.ex[0] + 1;
	Polynomial sum(sum_size);
	for(int i = 0; i < sum_size;i++){
		sum.ex[i] = sum.size - 1 - i;
		sum.ce[i] = 0;
	}
	for(int i = 0;i < p.size;i++){
		for(int j = 0;j < size;j++){
			sum.ce[i+j] += ce[j] * p.ce[i];
			//cout << sum.ce[i+j] << " ";
		}
	}
	return sum;
}
Polynomial Polynomial::derivative()
{
	Polynomial p = *this;
	if(p.size == 1){
		Polynomial A(1);
		A.ex[0] = 0;
		A.ce[0] = 0;
		return A;
	}
	Polynomial temp(p.size - 1);
	for(int i = 0;i < p.size - 1;i++){
		temp.ex[i] = p.ex[i] - 1;
		temp.ce[i] = p.ex[i] * p.ce[i];
	}
	return temp;
}
Polynomial Polynomial::integral(const double a,const double b)
{
	Polynomial A(1);
	double up = 0,down = 0,result = 0;
	for(int i = 0;i < this->size;i++)
	{
		up += (this->ce[i] / (this->ex[i] + 1)) * pow(b,this->ex[i] + 1);
		down += (this->ce[i] / (this->ex[i] + 1)) * pow(a,this->ex[i] + 1);
	}
	result = up - down;
	A.ex[0] = 0;
	A.ce[0] = result;
	return A;
}
Polynomial::~Polynomial()
{
	delete ce;
	delete ex;
}
ostream &operator << (ostream &output,const Polynomial &p)
{
	if(p.size == 1){
		output << p.ce[0];
		return output;
	}
	if(p.size == 2){
		if(p.ce[0] != 0 && p.ce[0] != 1 && p.ce[0] != -1)
			output << p.ce[0] << "x";
		if(p.ce[0] == 1)
			output << "x";
		if(p.ce[0] == -1)
			output << "-x";
	}
	if(p.size > 2){
		if(p.ce[0] != 1 && p.ce[0] != 0 && p.ce[0] != -1)
			output << p.ce[0] << "x^" << p.ex[0];
		if(p.ce[0] == 1)
			output << "x^" << p.ex[0];
		if(p.ce[0] == -1)
			output << "-x^" << p.ex[0];
	}
	for(int i = 1;i < p.size;i++){
		if(p.ce[i] == 0)				   
			continue;
		if(p.ex[i] > 1){
			if(p.ce[i] > 1)
				output << "+" << p.ce[i] <<"x^" << p.ex[i];
			if(p.ce[i] == 1)
				output << "+" << "x^"<< p.ex[i];
			if(p.ce[i] < 0 && p.ce[i] != -1)
				output << p.ce[i] << "x^" << p.ex[i];
			if(p.ce[i] == -1)
				output << "-x^" << p.ex[i];
		}
		if(p.ex[i] == 1){					 
			if(p.ce[i] > 1)
				output << "+" << p.ce[i] << "x";
			if(p.ce[i] == 1)
				output << "+x";
			if(p.ce[i] < 1 && p.ce[i] != -1)
				output << p.ce[i] << "x";
			if(p.ce[i] == -1)
				output << "-x";
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

