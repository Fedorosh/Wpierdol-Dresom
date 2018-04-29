#pragma once
#include <std_lib_facilities.hpp>
#include <Windows.h>

namespace dresiarnia
{
	class Postac
	{
	protected:
		int hp;
		int atak_damage;
		int szansa;
		int stale;
	public:
		Postac(int a, int b, int c) : hp(a), atak_damage(b), szansa(c) { stale = a; }
		virtual void dzialaj(Postac &a) = 0;
		friend void odejmij(Postac &a, int b)
		{
			if (a.hp > 0)
				a.hp -= b;
			if (a.hp < 0)
				a.hp = 0;
		}
		friend void dodaj(Postac &a, int b)
		{
			if (a.hp != 0)
			{
				if (a.hp < a.stale)
					a.hp += b;
				if (a.hp > a.stale)
					a.hp = a.stale;
			}
		}
		friend void wyzeruj(Postac &a)
		{
			a.hp = 0;
		}
		friend ostream & operator<<(ostream& operand, Postac &a)
		{
			operand << a.hp << endl << a.atak_damage << endl << a.szansa << endl;
			return operand;
		}
		friend void rozgrywka();
		friend void mapka(Postac &a, Postac &b, Postac &c, Postac &d);
	};
	class Dres_1 :public Postac
	{
	public:
		Dres_1(int a = 15, int b = 3, int c = 20) :Postac(a, b, c) {}
		void dzialaj(Postac &a) {
			odejmij(a, atak_damage);
		}
	};
	class Dres_2 :public Postac
	{
	public:
		Dres_2(int a = 10, int b = 6, int c = 10) :Postac(a, b, c) {}
		void dzialaj(Postac &a) {
			odejmij(a, atak_damage);
		}
	};
	class Dres_3 :public Postac
	{
	public:
		Dres_3(int a = 10, int b = 2, int c = 100) :Postac(a, b, c) {}
		void dzialaj(Postac &a) {
			dodaj(a, atak_damage);
		}
		void lecz(Dres_1 &a, Dres_2 &b)
		{
			dzialaj(a);
			dzialaj(b);
		}
	};
	class Bohater :public Postac
	{
	protected:
		int specjal_damage;
		bool maczeta;
	public:
		Bohater(int a = 30, int b = 5, int c = 100, int d = 1) :Postac(a, b, c), specjal_damage(d) { maczeta = true; }
		void dzialaj(Postac &a)
		{
			odejmij(a, atak_damage);
		}
		void specjal(Dres_1 &a, Dres_2 &b, Dres_3 &c)
		{
			odejmij(a, specjal_damage);
			odejmij(b, specjal_damage);
			odejmij(c, specjal_damage);
		}
		void zabij(Postac &a)
		{
			wyzeruj(a);
			maczeta = false;
		}
		bool czy_maczeta()
		{
			if (maczeta)
				return true;
			return false;
		}
	};
	void wybor_atak(Dres_1 &a, Dres_2 &b, Dres_3 &c, Bohater &d, char &h);
	void wybor_dres(Dres_1 &a, Dres_2 &b, Dres_3 &c, Bohater &d);
	void mapka(Postac &a, Postac &b, Postac &c, Postac &d)
	{
		cout << "Bliski Seba: " << a.hp << " HP   ";
		cout << "Mati Dlugodystansowiec: " << b.hp << " HP   ";
		cout << "Gruby the Healer: " << c.hp << " HP   " << endl;
		cout << endl << endl;
		cout << " __        __        __                     __  " << endl;
		cout << "(__)__    (__)__    (__)__          ___    / /      " << endl;
		cout << "(-,-)     (o,o)     (o,o)          [o o]  / / " << endl;
		cout << " ---      (---)     |---|          |_'_|  || " << endl;
		cout << endl << endl << endl;
		cout << "Twoje HP: " << d.hp << endl;
	}
	void rozgrywka()
	{
		Bohater hero;
		Dres_1 dres1;
		Dres_2 dres2;
		Dres_3 dres3;

		int suma = dres1.hp + dres2.hp + dres3.hp;
		mapka(dres1, dres2, dres3, hero);
		while (hero.hp != 0 && suma != 0)
		{
			if (hero.czy_maczeta())
				wybor_dres(dres1, dres2, dres3, hero);
			system("cls");
			mapka(dres1, dres2, dres3, hero);
			if (dres1.hp == 0)
			{
				system("cls");
				mapka(dres1, dres2, dres3, hero);
				cout << endl << "Bliski Seba jest martwy" << endl;
			}
			else {
				dres1.dzialaj(hero);
				system("cls");
				mapka(dres1, dres2, dres3, hero);
				cout << endl << "Bliski Seba uzyl: wpierdol" << endl;
			}
			Sleep(1400);
			if (dres2.hp == 0)
			{
				system("cls");
				mapka(dres1, dres2, dres3, hero);
				cout << endl << "Mati Dlugodystansowiec jest martwy" << endl;
			}
			else {
				dres2.dzialaj(hero);
				system("cls"); mapka(dres1, dres2, dres3, hero);
				cout << endl << "Mati Dlugodystansowiec uzyl: rzut butelka" << endl;
			}
			Sleep(1400);
			if (dres3.hp == 0)
			{
				system("cls");
				mapka(dres1, dres2, dres3, hero);
				cout << endl << "Gruby the Healer jest martwy" << endl;
			}
			else {
				dres3.lecz(dres1, dres2);
				system("cls"); mapka(dres1, dres2, dres3, hero);
				cout << endl << "Gruby the Healer uzyl: hymn kiboli" << endl;
			}
			Sleep(1400);
			suma = dres1.hp + dres2.hp + dres3.hp;
		}
		if (hero.hp != 0) { cout << endl << "Zwyciestwo!" << endl; }
		else { cout << endl << "Porazka..." << endl; }
	}
	void wybor_atak(Dres_1 &a, Dres_2 &b, Dres_3 &c, Bohater &d, char &g)
	{
		char h;
		cout << "1 Bliski Seba ---- 2 Mati Dlugodystansowiec ---- 3 Gruby the Healer ---- 4 Popraw wybor";
		do {
			h = _getch();
			switch (h)
			{
			case '1': if (g == '1') d.dzialaj(a); else d.zabij(a); break;
			case '2': if (g == '1') d.dzialaj(b); else d.zabij(b); break;
			case '3': if (g == '1') d.dzialaj(c); else d.zabij(c); break;
			case '4': {
				g = '0';
				cout << "\r                                                                                         \r"; }break;
			default: {
				cout << "wybierz tylko od 1 do 4!"; Sleep(1500);
				cout << "\r                                                                \r"; break;
			}
			}
		} while (h != '1'&& h != '2'&& h != '3' && h != '4');
	}
	void wybor_dres(Dres_1 &a, Dres_2 &b, Dres_3 &c, Bohater &d)
	{
		char g;
		cout << endl << "Wybierz atak i przeciwnika: ";
		cout << endl << "1 Cios z maczety (5pkt obrazen) ---- 2 Wir rozpaczy(3 pkt obrazen) ---- 3 Rzut maczeta(sprawdz sam) ---- 4 Wyjscie" << endl << endl;
		do {
			g = _getch();
			switch (g)
			{
			case '1': wybor_atak(a, b, c, d, g); break;
			case '2': d.specjal(a, b, c); break;
			case '3': wybor_atak(a, b, c, d, g); break;
			case '4': exit(0); break;
			default: {
				cout << "wybierz tylko od 1 do 4!"; Sleep(1500);
				cout << "\r                        \r"; break;
			}
			}
		} while (g != '1'&& g != '2'&& g != '3' && g != '4');
	}
}