#ifndef KOLKO_I_KRZYZYK.HPP
#define KOLKO_I_KRZYZYK.HPP
#include<iostream>
struct wezel    //Lisc drzewa przechowujacy dane o rozgrywce
{
    char** plansza;
    int wysokosc;
    int znak;
    int waga;  //Waga wezla
    wezel** drogi;  //Mozliwe dalsze scenariusze gry
};

class DrzewoGry
{
private:
    wezel* tworz_wezel(int dzieci, char ** &plansza, char poprzedni_gracz, int poz, int bok);

public:
    wezel *korzen;  //Aktualny stan gry
    int sprawdz_wygrana(char** plansza, int bok);
    void TworzDrzewo(int bok, char wiersz, int kolumna);
    wezel* get_korzen();
    void zmien_korzen(int pole);
    void ruch_uzytkownika(int wymiar, char wiersz, int kolumna);
    void ruch_komputera(int wymiar);
    void wyswietl_plansze(int wymiar);
};
#endif
