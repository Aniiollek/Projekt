#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "klasy.cpp"
#include <locale.h>
using namespace std;

template<typename T>
void wypisz(vector<T> my_datas)
{
	cout << endl << "Polskie litery zostanły zastąpione znakiem: _" << endl;
	for (auto i : my_datas)
	{
		cout << i << endl;
	}
	cout << endl << endl;
}

string polskie_znaki(string str)
{
	int ktory = 0;// polskie znaki zamieniaja sie zazwyczaj na 2 dziwne znaki 
	int przes = 0;//liczenie ile przesuniec
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] < 'A' || str[i] > 'Z')
		{
			str[i] = '_';
			if (str[i + 1] < 'A' || str[i + 1] > 'Z')//  jesli dana polska litera zajmuje 2 znaki to trzeba przesunac reszte o 1 znak w przód
			{
				str.erase(i + 1, 1);// usuwamy drugi znak
			}
		}
	}
	return str;
}

vector<datas> wczytaj_1(string file_name, char znak)// wczytujemy dane z pliku
{
	ifstream fs{ file_name };

	vector<datas> Nam_Num = {};// wektor obiektów klasy datas

	string temp;// zmienna do wyrzucania niepotrzebnych linijek
	string n; // bedziemy łapac imiona
	string l;// bedziemy łapac liczby
	int p; //liczby przekonwertujemy na int
	datas v_temp;
	
	getline(fs, temp);// pozbywanie sie 1 linijki 

	while (!fs.eof()) // dopóki nie przeczytamy calego pliku
	{
		getline(fs, n, znak);// imiona
		n = polskie_znaki(n);//polskie znaki w imionach zamienimy na _
		
		getline(fs, temp, znak);
		
		getline(fs, l, '\n');
		p = atoi(l.c_str());
		
		v_temp.load(n, p);
		Nam_Num.push_back(v_temp);
	}
	
	fs.close();
	return Nam_Num;
}

vector<datas> wczytaj_2(string file_name, char znak)// potrzebne 2 funkcje bo w niektorych plikach miedzy imieniem a liczba jest napisana plec
{
	ifstream fs{ file_name }; // plik do odczytu

	vector<datas> Nam_Num = {};// wektor obiektów klasy datas
	
	string temp;// zmienna do wyrzucania niepotrzebnych linijek
	string n; // bedziemy lapac imiona
	string l;// bedziemy lapac liczby
	int p; //liczby przekonwertujemy na int
	datas v_temp;
	
	getline(fs, temp);// pozbywanie sie 1 linijki 

	while (!fs.eof()) // dopóki nie przeczytamy calego pliku
	{
		getline(fs, n, znak);//wez pierwszy wyraz
		n = polskie_znaki(n);//polskie znaki w imionach zamienimy na _
		
		getline(fs, l, '\n');// wez 2 wyraz ( w pliku z jednej linijce sa tylko 2 wyrazy)
		p = atoi(l.c_str());// zrob ze stringu int
		
		v_temp.load(n, p);//zaladuj  wczytane dane do zmiennej
		Nam_Num.push_back(v_temp);// zaladuj zmienna do vectora
	}

	fs.close();
	return Nam_Num; //zwroc vector
}

vector<datas> wczytaj_szkocja(string file_name)// wczytujemy dane z imionami w szkocji z pliku
{
	ifstream fs{ file_name };

	vector<datas> Nam_Num = {};// wektor obiektów klasy datas

	string temp;// zmienna do wyrzucania niepotrzebnych linijek
	string n; // bedziemy lapac imiona
	string l;// bedziemy lapac liczby
	int p; //liczy przekonwertujemy na int
	datas v_temp;
	
	for (int i{ 0 }; i < 6; i++)// pozbywanie sie 6 linijek 
	{
		getline(fs, temp);
	}
	
	while (!fs.eof())// dopoki plik niepusty
	{
		getline(fs, temp, ',');
		getline(fs, n, ',');
		getline(fs, l, ',');
		
		for (int i{ 0 }; i < n.size(); i++) {// zmieniamy wczytane imiona by byly zapisane duzyli literami
			n[i] = toupper(n[i]);
		}
		
		n = polskie_znaki(n);
		
		p = atoi(l.c_str());// konwertujemy string na int
		v_temp.load(n, p);
		Nam_Num.push_back(v_temp);
		getline(fs, temp);//do końca lini
	}

	fs.close();
	return Nam_Num;
}

vector<statystyki> sporzadz_statystyki(vector<datas> vec0, vector<datas> vec1, vector<datas> vec2)
{
	vector<statystyki> stats = {};// vector w ktorym bedziemy przechowywac statystyki
	for (auto el : vec0)
	{
		statystyki st(el.get_name(), el.get_number(), find(el.get_name(), vec1), find(el.get_name(), vec2));// wszystkie imiona z 2020 dopelnione imionami z pozniejszych lat 
		stats.push_back(st);
		
	}
	if (!vec1.empty())
	{
		for (auto el : vec1)
		{
			statystyki st(el.get_name(), 0, el.get_number(), find(el.get_name(), vec2));// wszystkie imiona z 2021 (które nie były w 2020) dopelnione 2022 rokiem
			stats.push_back(st);
		}
	}
	
	if (!vec2.empty())
	{
		for (auto el : vec2)
		{
			statystyki st(el.get_name(), 0, 0, el.get_number());// wszystkie imiona z 2022 których nie było w zeszłych latach
			stats.push_back(st);
		}
	}

	return stats;
}

void zapis_2021(vector<statystyki> st)// zapisujemy do pliku dane o roku 2021
{
	fstream fs{ "myfile.txt", ios::out };// zapisz do pliku
	fs << "Ilość męskich imion nadanych w 2021 " << endl;
	fs << "Numer \t Imie \t Ilość  \t Tendencja" << endl;
	string str;// do przechowywania czy mniejsz czy wieksza
	int i{ 1 };// do wyliczania imion
	for (auto el : st)
	{
		if ((el.num2021 - el.num2020) < 0)//patrznie czy tendencja rosnąca czy malejąca
			str = "malejaca";
		else if ((el.num2021 - el.num2020) > 0)
			str = "rosnaca";
		else
			str = "stala";
		fs << i << ". \t" << el.name << "\t" << el.num2021 << "\t" << str << endl;
		i++;
	}
}

void zapis_2022(vector<statystyki> st)// zapisujemy do pliku dane o roku 2022
{
	fstream fs{ "myfile.txt", ios::app };// dopisz do pliku
	fs << endl;
	fs << "Ilość męskich imion nadanych w 2022 " << endl;
	fs << "Numer \t Imie \t Ilość \t Tendencja " << endl;
	string tendencja{};
	int i = 1;
	for (auto el : st)
	{
		if ((el.num2022 - el.num2021) < 0) // patrznie czy tendencja rosnąca czy malejąca
			tendencja = "malejaca";
		else if ((el.num2022 - el.num2021) > 0)
			tendencja = "rosnaca";
		else
			tendencja = "stala";
		fs << i << ".\t" << el.name << "\t" << el.num2022 << "\t" << tendencja << endl;
		i++;
	}
}

void zapis_nie20_tak21(vector<statystyki> st, vector<string>& zap)// zapisujemy do pliku dane o imionach ktorych nie bylo w 2020, a byly w 2021
{
	fstream fs{ "myfile.txt", ios::app };// dopisz do pliku
	fs << endl;
	fs << "Imiona których nie było w 2020 (były w 2021) " << endl;
	fs << "Numer \t Imie \t Ilość  " << endl;
	int i = 1;

	for (auto el : st)
	{
		if (el.num2020 == 0 && el.num2021 != 0)// ktorych imion nie bylo w 2020, a byly w 2021
		{
			fs << i << ".\t" << el.name << "\t" << el.num2021 << endl;
			zap.push_back(el.name);
		}
		i++;
	}
}

void zapis_nie20_nie21_tak22(vector<statystyki>& st, vector<string>& zap)// zapisujemy do pliku dane o imionach ktorych nie bylo w 2021, a byly w 2022
{
	fstream fs{ "myfile.txt", ios::app };// dopisz do pliku
	fs << endl;
	fs << "Imiona których nie było w 2020 ani 2021 (były w 2022) " << endl;
	fs << "Numer \t Imie \t Ilość  " << endl;
	int i = 1;
	for (auto el : st)
	{
		if (el.num2020 == 0 && el.num2021 == 0 && el.num2022 != 0)// ktorych imion nie bylo w 2020, ani 2021 a pojawily sie w 2022
		{
			fs << i << ".\t" << el.name << "\t" << el.num2022 << endl;
			zap.push_back(el.name);
		}
		i++;
	}
}

template<typename T>// przekazemy albo wszystkie imiona z lat 2020, 2021 i 2022 albo tylko imiona w 2021
void Szkocja_i_Pl(vector<T> vec1, vector<datas> szkocja, vector<string> &zap)// zapisujemy do pliku dane o imionach w Szkocji i w Polsce
{
	fstream fs{ "myfile.txt", ios::app };// dopisz do pliku
	fs << endl;
	fs << "Męskie imiona, które zostały zadane zarowno w Szkocji jak i w Polsce w 2021 " << endl;
	fs << "Numer \t Imie" << endl;
	
	int i = 1;
	for (auto el : vec1)// przechodzenie po vektorze z imionami w 2021
	{
		for (auto x : szkocja)//przechodzenie po vektorze z  imionami w szkocji w 2021
		{
			if (x.name == el.name)// jesli imie w szkocji takie same jak w polsce to zapisz do pliku
			{
				fs << i << ".\t" << el.name << endl;
				zap.push_back(el.name);
			}
		}
		i++;
	}
}

void menu()
{
	cout << "Wybierz :" << endl;
	cout << "0  -  Zakoncz" << endl;
	cout << "1  -  Zobacz statystyki o jakims imieniu" << endl;
	cout << "2  -  Zobacz imiona których nie było w 2020 (były w 2021)" << endl;
	cout << "3  -  Imiona których nie było w 2020 ani 2021 (były w 2022) " << endl; 
	cout << "4  -  Zobacz jakie imiona były nadane zarówno w Szkocji i w Polsce w 2021" << endl;
	cout << "5  -  Zobacz jakie imiona były nadane zarówno w Szkocji (w 2021) i w Polsce w latach (2020, 2021 i 2022)" << endl;
	cout << "6  -  Wypisz 15 imion na litere" << endl;
}

void zobacz_konkretne_imie(vector<statystyki> st, vector<datas> szkocja)// wczytamy imie z konsoli i wyszukamy o nim dane
{
	int f{ 0 };// 0 gdy imienia nie znaleziono, 1 gdy znaleziono
	string imie;// tu bedziemy przechowywac wczytane imie
	string tendencja{};
	
	cout << "O jakim imieniu chcialbys/chcialabys zobaczyc statystyki? \n";
	cin >> imie;
	
	for (int i{ 0 }; i < imie.size(); i++) {// zamieniamy napisane przez uzytkownika imie na duze litery
		imie[i] = toupper(imie[i]);
	}

	for (auto el : st)
	{
		if (el.name == imie)
		{
			f = 1;// 1 bo znalezlismy to imie
			cout << "Imie: \t " << el.name << endl;
			cout << "Ilosc osob o tym imieniu w 2020: \t" << el.num2020 << endl;
			cout << "Ilosc osob o tym imieniu w 2021: \t" << el.num2021 << endl;
			cout << "Ilosc osob o tym imieniu w 2022: \t" << el.num2022 << endl;
			
			if ((el.num2021 - el.num2020) < 0) //patrzymy jaka tendencja z 2020 na 2021 rok
				tendencja = "malejaca";
			else if ((el.num2021 - el.num2020) > 0)
				tendencja = "rosnaca";
			else
				tendencja = "stala";
			
			cout << "Tendencja tego imienia w 2021: \t" << tendencja << endl;
			
			if ((el.num2022 - el.num2021) < 0)//patrzymy jaka tendencja z 2021 na 2022 rok
				tendencja = "malejaca";
			else if ((el.num2022 - el.num2021) > 0)
				tendencja = "rosnaca";
			else
				tendencja = "stala";
			
			cout << "Tendencja tego imienia w 2022: \t" << tendencja << endl;
			
			for (auto el : szkocja)// szukamy podanego imienia wsrod imion andanych w szkocji
			{
				if (imie == el.name)// jesli znalezlismy to wypisujemy komunikat
					cout << "To imie bylo nadane rowniez w Szkocji w 2021 " << endl;
			}
			break;//jesli znalezlismy to imie to nie przeszukujmy dalej tablicy tylko z niej wyjdzmy
		}
	}
	
	if (f == 0)
		cout << "Nie znaleziono takiego imienia. \n";
	
	cout << endl;
}

void imiona_na_litere ( vector<statystyki> st )// funkcja do szukania imion na podana przez uzytkownika litere
{
	char litera;// tu zapiszemy podana przez uzytkownika litere
	
	cout << "Podaj litere: ";
	cin >> litera;
	
	if (litera < 'A' || (litera > 'Z' && litera < 'a') || litera>'z')
		return;

	litera = toupper(litera);//zmienianie podanej litery na duza
	cout << "Imiona na litere " << litera << " :" << endl;
	
	int i = 0;
	for (auto el : st)
	{
		if (el.name.at(0) == litera)
		{
			cout << el.name << endl;
			i++;
		}
		if (i == 15)break;
	}
}

int find(string na, vector<datas> &vec)// funkcjia wykorzystywana do tworzenia vectora statystyk
{
	int temp{ 0 };
	for (int i{0};i<vec.size();i++)
	{
		if (na == vec[i].name)// szukanie imienia wyslanego do tej funkcji w vektorze
		{
			temp = vec[i].number;
			vec.erase(vec.begin()+i); //usuwanie imienia ktore juz wystapilo zeby pozniej nie przeszukiwac jeszcze raz
			return temp;
		}	
	}
	return 0;
}

using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Polish"); // wyswietla polskie znaki w konsoli
	char znak = '\t';
	char znak2 = ';';
	
	vector<datas> PL_2020 = wczytaj_2("imiona2020.txt",znak);
	vector<datas> PL_2021 = wczytaj_1("imiona2021.txt",znak);
	vector<datas> PL_2022 = wczytaj_1("imiona2022.csv",znak2);
	vector<datas> SZK_2021 = wczytaj_szkocja("szkocja2021.txt");
	
	vector<statystyki> stat=sporzadz_statystyki(PL_2020, PL_2021, PL_2022);
	
	zapis_2021(stat);

	zapis_2022(stat);

	vector<string> nowe_w_21;
	zapis_nie20_tak21(stat, nowe_w_21);

	vector<string> nowe_w_22;
	zapis_nie20_nie21_tak22(stat, nowe_w_22);

	vector<string> Sz_Pl_21;
	Szkocja_i_Pl(PL_2021, SZK_2021,Sz_Pl_21);

	vector<string> Sz_Pl_20_21_22;
	Szkocja_i_Pl(stat, SZK_2021, Sz_Pl_20_21_22);

	char wybor{};
	do {
		menu();
		cin >> wybor;
		system("cls");
		
		switch (wybor)
		{
		case  '1':
		{
			zobacz_konkretne_imie(stat, SZK_2021);
			break;
		}
		case '2':
		{
			wypisz(nowe_w_21);
			break;
		}
		case '3':
		{
			wypisz(nowe_w_22);
			break;
		}
		case '4':
		{
			wypisz(Sz_Pl_21);
			break;
		}
		case '5':
		{
			wypisz(Sz_Pl_20_21_22);
			break;
		}
		case '6':
		{
			imiona_na_litere(stat);
		}
		default:
			break;
		}
		
	} while (wybor != '0');
	
	return 1;
}
