#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "naglowek.h"
class statystyki;

using namespace std;
class datas
{
	string name;
	int number;//liczba wystapien
public:
	datas() {};
	datas(string n_name, int n_number) :name{ n_name }, number{ n_number }
	{}
	friend ostream& operator<<(ostream& os, datas x)
	{
		os << x.name << "  " << x.number << endl;
		return os;
	}
	void load(string n_name, int n_number) 
	{
		this->name= n_name ;
		this->number=n_number ;
	}
	string get_name()
	{
		return this->name;
	}
	int get_number()
	{
		return this->number;
	}
	friend int find(string na, vector<datas> &vec);
	friend void zobacz_konkretne_imie(vector<statystyki> st, vector<datas> szkocja);
	template<typename T>
	friend void Szkocja_i_Pl(vector<T> vec1, vector<datas> szkocja, vector<string>& zap);
	friend vector<statystyki> nazwa(vector<datas> vec0, vector<datas> vec1, vector<datas> vec2);
};
 
class statystyki 
{
	string name;
	int num2020;
	int num2021;
	int num2022;
	int tendencja_20_na_21;
	int tendencja_21_na_22;

public:
	statystyki(){}
	statystyki(string n, int n0, int n1, int n2)
	{
		this->name = n;
		this->num2020 = n0;
		this->num2021 = n1;
		this->num2022 = n2;
	}
	friend ostream& operator <<(ostream& os, statystyki st)
	{
		os << st.name << " " << st.num2020 << " " << st.num2021 << " " << st.num2022 <<endl;
		return os;
	}
	friend void zobacz_konkretne_imie(vector<statystyki> st, vector<datas> szkocja);
	friend void zapis_nie20_nie21_tak22(vector<statystyki>& st, vector<string>& zap);
	friend void zapis_nie20_tak21(vector<statystyki> st, vector<string>& zap);
	friend void zapis_2022(vector<statystyki> st);
	friend void zapis_2021(vector<statystyki> st);
	friend vector<statystyki> nazwa(vector<datas> vec0, vector<datas> vec1, vector<datas> vec2);
	template<typename T>
	friend void Szkocja_i_Pl(vector<T> vec1, vector<datas> szkocja, vector<string>& zap);
	friend void imiona_na_litere(vector<statystyki> st);
};


