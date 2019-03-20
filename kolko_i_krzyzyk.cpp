#include "kolko_i_krzyzyk.hpp"

void DrzewoGry::ruch_uzytkownika(int wymiar, char wiersz, int kolumna)
{
    int droga = 0;

            while(droga != 15)
            {
            if(korzen->drogi[droga]->plansza[wiersz-97][kolumna-1] == 'X')
            {
                korzen = korzen->drogi[droga];
                droga = 15;
                break;
            }
            else
                droga++;
            }
}


void DrzewoGry::wyswietl_plansze(int wymiar)
{
    char litera = 'a';
    std::cout<<"  ";
    for(int i = 0; i <wymiar; i++) std::cout<<i+1<<" ";
    std::cout<<std::endl;
    for(int i = 0; i < wymiar; i++)
    {
        std::cout<<litera<<" ";
        litera++;
        for(int j = 0; j<wymiar; j++)
        {
            std::cout<<korzen->plansza[i][j]<<"|";
        }
        std::cout<<std::endl;
    }



}
int DrzewoGry::sprawdz_wygrana(char** plansza, int bok)
{//Zwraca 2 dla wygranej kolek, 1 dla wygranej krzyzykow i 0 dla remisu

int licznikx= 0, liczniko = 0;

for(int i = 0; i < bok; i++)
{
    for(int j = 0; j < bok; j++)
    {
        if(plansza[i][j] == 'X')
        {
            licznikx++;
        }
        if(plansza[i][j] == 'O')
        {
            liczniko++;
        }
    }
    if(licznikx == bok)
    {
        return -1;
    }
    if(liczniko == bok)
    {
        return 1;
    }
    else
    {
        licznikx = 0;
        liczniko = 0;
    }
}
for(int i = 0; i < bok; i++)
{
    for(int j = 0; j < bok; j++)
    {
        if(plansza[j][i] == 'X')
        {
            licznikx++;
        }
        if(plansza[j][i] == 'O')
        {
            liczniko++;
        }
    }
    if(licznikx == bok)
    {
        return -1;
    }
    if(liczniko == bok)
    {
        return 1;
    }
    else
    {
        licznikx = 0;
        liczniko = 0;
    }
}
for(int i = 0; i < bok; i++)
{
    if(plansza[i][i] == 'X')
        {
            licznikx++;
        }
        if(plansza[i][i] == 'O')
        {
            liczniko++;
        }
    if(licznikx == bok)
    {
        return -1;
    }
    if(liczniko == bok)
    {
        return 1;
    }
    else
    {
        licznikx = 0;
        liczniko = 0;
    }

}

return 0;

}

void DrzewoGry::ruch_komputera(int wymiary)
{
    //Wybranie wezla o najwiekszej wartosci
    int i = 0, najlepszy_wezel = i;
    int najwyzsza_wartosc = korzen->drogi[i]->waga;
    i++;
    while(i < korzen->wysokosc)
    {
            if(korzen->drogi[i]->waga > najwyzsza_wartosc)
            {
            najwyzsza_wartosc = korzen->drogi[i]->waga;
            najlepszy_wezel = i;
            }
            if(sprawdz_wygrana(korzen->drogi[i]->plansza, wymiary) ==1)
            {
                najlepszy_wezel = i;
                break;
            }
            i++;
    }

    korzen = korzen->drogi[najlepszy_wezel];


}

void DrzewoGry::TworzDrzewo(int bok, char wiersz, int kolumna)
{
    int i = 0;
    int j = 0;
    korzen = new wezel;
    korzen->wysokosc = bok*bok-1;
    korzen->drogi = new wezel*[bok*bok];
    korzen->waga = 0;
    korzen->plansza = new char*[bok];
    korzen->wysokosc = bok*bok-1;
    for(int i = 0; i < bok; i++)
    {
        korzen->plansza[i]=new char [bok];
    }
    for(int i = 0; i<bok; i++)
    {
        for(int j = 0; j<bok; j++)
        {
            korzen->plansza[i][j] = ' ';
        }
    }

    korzen->plansza[wiersz-97][kolumna-1] = 'X';

     while(i < bok*bok-1)
        {
            if(i > 0)
            {
                if(korzen->plansza[j/bok][j%bok]==' ')
                {
                        korzen->drogi[i] =tworz_wezel(korzen->wysokosc-1, korzen->plansza, 'O', j, bok);

                i++;
                j++;
                }
                else
                    j++;
            }
            else
            {
                if(korzen->plansza[j/bok][j%bok]==' ')
                {

                        korzen->drogi[i] =tworz_wezel(korzen->wysokosc-1, korzen->plansza, 'O', j, bok);
                i++;
                j++;
                }
                else
                {
                    j++;
                }
            }


        }

}

wezel* DrzewoGry::tworz_wezel(int dzieci, char ** &plansza_prev, char w_znak, int poz, int bok)
{
    int i = 0;
    int j = 0;
    wezel * w;
    w = new wezel;
    w->drogi = new wezel*[dzieci];
    w->plansza = new char*[bok];
    w->wysokosc = dzieci;
    w->waga= 0;
    for(int i = 0; i < bok; i++)
    {
        w->plansza[i]=new char [bok];
    }
    for(int i = 0; i <bok; i++)
    {
        for(int j = 0; j <bok; j++)
        {
            w->plansza[i][j]=plansza_prev[i][j];
        }
    }
            for(int i = 0; i < bok*bok; i++)
            {
                if(plansza_prev[poz/bok][poz%bok]==' ')
                w->plansza[poz/bok][poz%bok] = w_znak;
                    else
                    poz++;
            }



    if(sprawdz_wygrana(w->plansza, bok)==-1||sprawdz_wygrana(w->plansza, bok)==1)
    {
        w->waga = sprawdz_wygrana(w->plansza, bok);
        return w;
    }

    if(dzieci<=0)
    {
        w->waga = sprawdz_wygrana(w->plansza, bok);

    }
    else
    {
        for( int i = 0; i< dzieci; i++)
        {
            w->drogi[i] = new wezel[dzieci];
        }

        while(i < dzieci)
        {
            if(i > 0)
            {
                if(w->drogi[i-1]->plansza[j/bok][j%bok]==' ')
                {
                    if(w_znak == 'X')
                    {
                        w->drogi[i] =tworz_wezel(dzieci-1, w->plansza, 'O', j, bok);

                    }
                    else
                    {
                        w->drogi[i] =tworz_wezel(dzieci-1, w->plansza, 'X', j, bok);

                    }
                i++;
                j++;
                }
                else
                    j++;
            }
            else
            {
                if(plansza_prev[j/bok][j%bok]==' ')
                {
                    if(w_znak == 'X')
                    {
                        w->drogi[i] =tworz_wezel(dzieci-1, w->plansza, 'O', j, bok);

                    }
                    else
                    {
                        w->drogi[i] =tworz_wezel(dzieci-1, w->plansza, 'X', j, bok);

                    }
                i++;
                j++;
                }
                else
                {
                    j++;
                }
            }


        }
        w->waga = w->drogi[0]->waga;
        for(int i = 0 ; i<dzieci; i++) //Obliczanie wagi wezla
        {

                w->waga = w->drogi[i]->waga+ w->waga;
        }
    }


    return w;
}

wezel* DrzewoGry::get_korzen()
{
    return korzen;
}
