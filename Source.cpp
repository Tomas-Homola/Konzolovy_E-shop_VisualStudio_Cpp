#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int pocet_produktov, pocet_kupenych_produktov = 0;
float minute_peniaze = 0.0;

struct PRODUKT
{
	int ID;
	string nazov;
	string vyrobca;
	int pocet_kusov;
	float cena;
};

PRODUKT* produkty;

struct ZAKAZNIK
{
	string meno;
	string priezvisko;
	float rozpocet;
};

ZAKAZNIK* zakaznik;

PRODUKT* produkty_nacitaj_zo_suboru(string filename)
{
	PRODUKT* produkty;
	fstream subor;

	subor.open(filename, ios::in);
	if (!subor.is_open())
		return NULL;

	subor >> pocet_produktov;

	cout << "pocet produktov je " << pocet_produktov << endl;

	produkty = new PRODUKT[pocet_produktov];

	for (int i = 0; i < pocet_produktov; i++)
	{
		subor >> produkty[i].ID;
		subor >> produkty[i].nazov;
		subor >> produkty[i].vyrobca;
		subor >> produkty[i].pocet_kusov;
		subor >> produkty[i].cena;
	}

	subor.close();
	cout << "produkty nacitane" << endl;
	return produkty;
}


int main()
{
	PRODUKT* produkty;

	produkty = produkty_nacitaj_zo_suboru("produkty.txt");

	/*for (int i = 0; i < pocet_produktov; i++)
	{
		cout << "ID: " << produkty[i].ID << "; nazov: " << produkty[i].nazov << "; vyrobca: " << produkty[i].vyrobca << "; pocet kusov: " << produkty[i].pocet_kusov << "; cena: " << produkty[i].cena << endl;
	}*/

	return 0;
}