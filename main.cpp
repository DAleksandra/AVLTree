 #include <iostream>
#include "kolko_i_krzyzyk.hpp"
#include "kolko_i_krzyzyk.cpp"

int main()
{
    DrzewoGry drzewo;
    int wymiary, ilosc_pol;
    int kolumna;
    char wiersz;
    std::cout<<"Witaj w grze kolko i krzyzyk! Zapraszamy do gry. Sam wybierasz rozmiary planszy. Zawsze jest ona kwadratem, dlatego podajesz tylko ilosc pol w jednym wierszu."<<std::endl;
    std::cout<<"Gre zaczyna krzyzyk. Podaj wymiary planszy:  ";
    std::cin>>wymiary;
    std::cout<<std::endl;
    ilosc_pol = wymiary*wymiary;
        std::cout<<"Ruch gracza:"<<std::endl;
        std::cout<<"Wpisz  wiersz i kolumne:  ";
        std::cin>>wiersz>>kolumna;
        drzewo.TworzDrzewo(wymiary, wiersz, kolumna);
        drzewo.wyswietl_plansze(wymiary);
        ilosc_pol--;

    while(ilosc_pol>0)
    {
        std::cout<<"Ruch komputera:"<<std::endl;
        drzewo.ruch_komputera(wymiary);
        drzewo.wyswietl_plansze(wymiary);
        ilosc_pol--;
        if(drzewo.sprawdz_wygrana(drzewo.get_korzen()->plansza, wymiary) == 1)
        {
            std::cout<<"Wygrana kolek!"<<std::endl;
            break;
        }
        std::cout<<"Ruch gracza:"<<std::endl;
        std::cout<<"Wpisz  wiersz i kolumne:  ";
        std::cin>>wiersz>>kolumna;
        drzewo.ruch_uzytkownika(wymiary, wiersz, kolumna);
        ilosc_pol--;
        drzewo.wyswietl_plansze(wymiary);
        if(ilosc_pol<=0)
        {
            break;
        }
        if(drzewo.sprawdz_wygrana(drzewo.get_korzen()->plansza, wymiary) == -1)
        {
            std::cout<<"Wygrana krzyzykow!"<<std::endl;
            break;
        }


    }

    if(ilosc_pol <= 0)
    {
        std::cout<<"Remis!"<<std::endl;
    }
    std::cout<<"Koniec gry!"<<std::endl;

}



