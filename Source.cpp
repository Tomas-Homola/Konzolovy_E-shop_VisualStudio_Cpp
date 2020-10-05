#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int pocet_produktov, pocet_kupenych_produktov = 0;
float minute_peniaze = 0.0;

struct PRODUKT
{
	int ID = -1;
	string nazov;
	string vyrobca;
	int pocet_kusov = 0;
	float cena = 0.0;
};

PRODUKT* produkty;

struct ZAKAZNIK
{
	string meno;
	string priezvisko;
	float rozpocet = 0.0;
	PRODUKT kupene_produkty[25];
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

	//cout << "pocet produktov je " << pocet_produktov << endl;

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
	//cout << "produkty nacitane" << endl;
	return produkty;
}

ZAKAZNIK* registruj_zakaznika()
{
	ZAKAZNIK* zakaznik;

	zakaznik = new ZAKAZNIK;

	cout << "Zadajte meno zakaznika:" << endl;
	cin >> zakaznik->meno;
	cout << "Zadajte priezvisko zakaznika:" << endl;
	cin >> zakaznik->priezvisko;
	cout << "Zadajte rozpocet zakaznika:" << endl;
	cin >> zakaznik->rozpocet;

	cout << "Zakaznik:" << endl << "-meno: " << zakaznik->meno << endl << "-priezvisko: " << zakaznik->priezvisko << endl << "-rozpocet: " << std::setprecision(3) << zakaznik->rozpocet << " EUR" << endl;

	return zakaznik;
}

void main_page();

void produkt_vyber_podla_ID(int vybrane_ID)
{
	int kupit = 0;

	if (produkty[vybrane_ID - 1].pocet_kusov < 1) // produkt NIE JE na sklade
	{
		cout << "Vybrany produkt " << produkty[vybrane_ID - 1].nazov << " NIE JE momentalne na sklade" << endl;
		main_page();
	}
	else // produkt JE na sklade
	{
		cout << "Vybrany produkt '" << produkty[vybrane_ID - 1].nazov << "' je na sklade, cena: " << produkty[vybrane_ID - 1].cena << endl;
		cout << endl << "Zadajte:" << endl << "1 - kupit vybrany produkt" << endl << "0 - nekupit vybrany produkt" << endl;
		cin >> kupit;

		if (kupit == 1)
		{
			if (zakaznik->rozpocet >= produkty[vybrane_ID - 1].cena)
			{
				zakaznik->rozpocet -= produkty[vybrane_ID - 1].cena; // odpocet ceny produktu od rozpoctu zakaznika
				zakaznik->kupene_produkty[pocet_kupenych_produktov].nazov = produkty[vybrane_ID - 1].nazov; // skopirovanie nazvu produktu
				zakaznik->kupene_produkty[pocet_kupenych_produktov].vyrobca = produkty[vybrane_ID - 1].vyrobca; // skopirovanie nazvu vyrobcu produktu
				zakaznik->kupene_produkty[pocet_kupenych_produktov].cena = produkty[vybrane_ID - 1].cena; // skopirovanie ceny

				pocet_kupenych_produktov++;
				minute_peniaze += produkty[vybrane_ID - 1].cena;
				produkty[vybrane_ID].pocet_kusov--;

				cout << "Zostavajuci rozpocet: " << std::setprecision(3) << zakaznik->rozpocet << " EUR" << endl;

				if (produkty[vybrane_ID - 1].pocet_kusov < 0) // kontrola, aby nebol zaporny pocet produktov;
					produkty[vybrane_ID - 1].pocet_kusov = 0;

				cout << "Produkt kupeny" << endl;
			}
			else
				cout << "Nedostatok penazi" << endl;
		}
		else if (kupit == 0)
			cout << "Nekupene" << endl;
		else
			cout << "Zle zadana volba" << endl;
	}

	cout << endl;
	main_page();
}

void produkty_vypis_podla_nazvu(string hladany_vyraz)
{
	int najdene_produkty = 0, vybrane_ID;

	cout << "Vysledky pre hladany vyraz '" << hladany_vyraz << "':" << endl;

	for (int i = 0; i < pocet_produktov; i++)
	{
		size_t najdene = produkty[i].nazov.find(hladany_vyraz);
		if (najdene != string::npos)
		{
			cout << "Vyrobca: " << produkty[i].vyrobca << ", Nazov produktu: " << produkty[i].nazov << ", ID: " << produkty[i].ID << endl;
			najdene_produkty++;
		}

		if (najdene_produkty > 0)
		{
			cout << endl << "Vyberte si produkt podla prislusneho ID" << endl;
			cin >> vybrane_ID;

			if (vybrane_ID > 0 && vybrane_ID <= pocet_produktov)
				produkt_vyber_podla_ID(vybrane_ID);
			else
			{
				cout << "Zle zadane ID produktu" << endl;
				main_page();
			}
		}
		else
		{
			cout << "Pod hladanym nazvom '" << hladany_vyraz << "' sa nic nenaslo" << endl;
			main_page();
		}
	}
}

void produkty_vypis_podla_vyrobcu(string hladany_vyraz)
{
	int najdene_produkty = 0, vybrane_ID;

	cout << "Vysledky pre hladany vyraz '" << hladany_vyraz << "':" << endl;

	for (int i = 0; i < pocet_produktov; i++)
	{
		size_t najdene = produkty[i].vyrobca.find(hladany_vyraz);
		if (najdene != string::npos)
		{
			cout << "Vyrobca: " << produkty[i].vyrobca << ", Nazov produktu: " << produkty[i].nazov << ", ID: " << produkty[i].ID << endl;
			najdene_produkty++;
		}

		if (najdene_produkty > 0)
		{
			cout << endl << "Vyberte si produkt podla prislusneho ID" << endl;
			cin >> vybrane_ID;

			if (vybrane_ID > 0 && vybrane_ID <= pocet_produktov)
				produkt_vyber_podla_ID(vybrane_ID);
			else
			{
				cout << "Zle zadane ID produktu" << endl;
				main_page();
			}
		}
		else
		{
			cout << "Pod hladanym nazvom '" << hladany_vyraz << "' sa nic nenaslo" << endl;
			main_page();
		}
	}
}

void main_page()
{
	fstream blocik;
	int volba = 0;
	string hladany_vyraz;

	do
	{
		cout << "Vyberte moznost\n1 -> pre hladanie podla nazvu produktu\n2 -> pre hladanie podla nazvu vyrobcu produktu\n3 -> pre ukoncenie nakupu" << endl;
		cin >> volba;
		if (volba > 3 || volba < 1)
			cout << "Zle zadana moznost" << endl;

	} while (volba > 3 || volba < 1);

	if (volba == 1)
	{
		cout << "Hladat podla:" << endl;
		cin >> hladany_vyraz;

		produkty_vypis_podla_nazvu(hladany_vyraz);
	}
	else if (volba == 2)
	{
		cout << "Hladat podla:" << endl;
		cin >> hladany_vyraz;

		produkty_vypis_podla_vyrobcu(hladany_vyraz);
	}
	else if (volba == 3)
	{
		cout << "Koniec nakupu" << endl;

		cout << "Minute peniaze: " << setprecision(3) << minute_peniaze << " EUR" << endl;

		blocik.open("blocik_od_nakupu.txt", ios::out);
		if (!blocik.is_open())
		{
			cout << "Nepodarilo sa otvorit blocik" << endl;
			exit(1);
		}

		blocik << "E-shop Obchodik\nUlica, Mesto, Krajina\nDatum a cas nakupu: 30/09/20 11:58\n";
		blocik << "******************************\n";
		blocik << "Zakaznik si zakupil nasledujuce polozky:\n";

		for (int i = 0; i < pocet_kupenych_produktov; i++)
		{
			blocik << "1x " << zakaznik->kupene_produkty[i].nazov << " ... " << setprecision(3) << zakaznik->kupene_produkty[i].cena << endl;
		}

		blocik << "______________________________\n";
		blocik << "Suma celkovo: " << setprecision(3) << minute_peniaze << " EUR\n\nDakujeme za vas nakup";

		blocik.close();

		delete zakaznik;
		delete[] produkty;

		exit(0);
	}

}

int main()
{

	produkty = produkty_nacitaj_zo_suboru("produkty.txt");

	zakaznik = registruj_zakaznika();

	/*for (int i = 0; i < pocet_produktov; i++)
	{
		cout << "ID: " << produkty[i].ID << "; nazov: " << produkty[i].nazov << "; vyrobca: " << produkty[i].vyrobca << "; pocet kusov: " << produkty[i].pocet_kusov << "; cena: " << produkty[i].cena << endl;
	}*/

	main_page();

	return 0;
}