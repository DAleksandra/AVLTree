#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;



struct wezel
{
    int dana, wysokosc;
    wezel *lewy;
    wezel *prawy;

};


class DrzewoAVL
{
    private:
    wezel *korzen;

    //Usuwa wszystkie elementy w drzewie
    void usunWszystko(wezel *w);
    //Dodaje nowy element do drzewa
    wezel *dodaj(int x, wezel* w);
    //Pojedyncza rotacja prawa
    wezel* pojPrawaRotacja(wezel* &w);
    //Pojedyncza rotacja lewa
    wezel* pojLewaRotacja(wezel* &w);
    //Podwojna rotacja prawa
    wezel* pdwPrawaRotacja(wezel* &w);
    //Pojedyncza rotacja lewa
    wezel* pdwLewaRotacja(wezel* &w);
    //Znajduje minimum w drzewie
    wezel* minimum(wezel* w);
    //Usuwa element w drzewie
    wezel* usun(int x, wezel* w);
    //Zwraca wysokosc drzewa
    int wysokosc(wezel* w);

    //Przejscia
    void inorder(wezel* w);
    void postorder(wezel* w);
    void preorder(wezel* w);

    public:
        DrzewoAVL(); //Konstruktor bezparametryczny
        //Dodawanie elementu
        void dodaj(int x);
        //Usuwanie wybranego elementu
        void usun(int x);
        //Wyswietla wszystkie elementy drzewa
        void wyswietl();
        //Wyswietla element w korzeniu drzewa
        void getKorzen();
        //Wyswietla wysokosc drzewa
        void wysokosc();
        void usun_wszystko();

};

int main()
{
    DrzewoAVL drzewo;
    clock_t start = clock();
    clock_t dodanie;
    int z=100;

/*
    for(int i = 0; i<z ; i++)
    {
        drzewo.dodaj(i);
    }
    dodanie=(clock()-start)/(CLOCKS_PER_SEC/1000);
    cout<<"Czas:  "<<dodanie<<endl;

    drzewo.usun(1);

    cout<<"Czas: "<<(clock()-dodanie)/(CLOCKS_PER_SEC/1000)<<endl;*/


    drzewo.dodaj(20);
    drzewo.dodaj(15);
    drzewo.dodaj(25);
    drzewo.dodaj(23);
    drzewo.dodaj(30);
    drzewo.dodaj(5);
    drzewo.dodaj(10);

    drzewo.wyswietl();
    drzewo.usun(23);
    drzewo.wyswietl();



    }

void DrzewoAVL::usunWszystko(wezel *w)
{
    if(w == NULL)
        return;
    usunWszystko(w->lewy);
    usunWszystko(w->prawy);
    delete w;
}

wezel* DrzewoAVL::dodaj(int x, wezel* w)
    {
        if(w == NULL) // Stwórz nowy węzeł, jeśli doszedłeś do pustego liścia
        {
            w = new wezel;
            w->dana = x;
            w->wysokosc = 0;
            w->lewy = w->prawy = NULL;
        }
        else if(x < w->dana) //x mniejsze od wartości w liściu, idzie na lewo
        {
            w->lewy = dodaj(x, w->lewy);
            if(wysokosc(w->lewy) - wysokosc(w->prawy) == 2)  //Sprawdzanie balansu drzewa
            {
                if(x < w->lewy->dana)
                    w = pojPrawaRotacja(w);
                else
                    w = pdwPrawaRotacja(w);
            }
        }
        else if(x > w->dana) //x większe od wartości w liściu, idzie w prawo
        {
            w->prawy = dodaj(x, w->prawy);
            if(wysokosc(w->prawy) - wysokosc(w->lewy) == 2) //Sprawdzenie balansu drzewa
            {
                if(x > w->prawy->dana)
                    w= pojLewaRotacja(w);
                else
                    w = pdwLewaRotacja(w);
            }
        }

        w->wysokosc = max(wysokosc(w->lewy), wysokosc(w->prawy))+1; //Ustawienie nowej wysokości dla węzła
        return w;
    }

    wezel* DrzewoAVL::pojPrawaRotacja(wezel* &w)
    {
        wezel* u = w->lewy;
        w->lewy = u->prawy;
        u->prawy = w;
        w->wysokosc - max(wysokosc(w->lewy), wysokosc(w->prawy))+1;
        u->wysokosc = max(wysokosc(u->lewy), w->wysokosc)+1;
        return u;
    }

    wezel* DrzewoAVL::pojLewaRotacja(wezel* &w)
    {
        wezel* u = w->prawy;
        w->prawy = u->lewy;
        u->lewy = w;
        w->wysokosc - max(wysokosc(w->lewy), wysokosc(w->prawy))+1;
        u->wysokosc = max(wysokosc(u->prawy), w->wysokosc)+1;
        return u;
    }

    wezel* DrzewoAVL::pdwLewaRotacja(wezel* &w)
    {
        w->prawy = pojPrawaRotacja(w->prawy);
        return pojLewaRotacja(w);
    }

    wezel* DrzewoAVL::pdwPrawaRotacja(wezel* &w)
    {
        w->lewy = pojLewaRotacja(w->lewy);
        return pojPrawaRotacja(w);
    }

    wezel* DrzewoAVL::minimum(wezel* w)
    {
        if(w == NULL)
            return NULL;
        else if(w->lewy == NULL)
            return w;
        else
            return minimum(w->lewy);
    }


wezel* DrzewoAVL::usun(int x, wezel* w)
    {
         wezel* tmp;

        // Element not found
        if(w == NULL)
            return w;

        // Wyszukanie elementu
        else if(x < w->dana)
            w->lewy = usun(x, w->lewy);
        else if(x > w->dana)
            w->prawy = usun(x, w->prawy);

        // Element found
        // With 2 children
        else if(w->lewy && w->prawy)
        {
            tmp = minimum(w->prawy);
            w->dana = tmp->dana;
            w->prawy = usun(w->dana, w->prawy);
        }
        // Węzeł bez dzieci, lub z jednym
        else
        {
            if(w->lewy == NULL)
                w = w->prawy;
            else if(w->prawy == NULL)
                w = w->lewy;
        }

/*

        w->wysokosc = max(wysokosc(w->lewy), wysokosc(w->prawy))+1;

        // Drzewo jest niezbalansowane po usuniêci lewej ga³êzi drzewa
        if(wysokosc(w->lewy) - wysokosc(w->prawy) == 2)
        {
            if(wysokosc(w->lewy->lewy) - wysokosc(w->lewy->prawy) == 1)
                return pojLewaRotacja(w);
            else
                return pdwLewaRotacja(w);
        }
        // Drzewo jest niezbalansowane po usuniêciu prawej ga³êzi drzewa
        else if(wysokosc(w->prawy) - wysokosc(w->lewy) == 2)
        {
            if(wysokosc(w->prawy->prawy) - wysokosc(w->prawy->lewy) == 1)
                return pojPrawaRotacja(w);
            else
                return pdwPrawaRotacja(w);
        }
*/
        return w;
    }

    int DrzewoAVL::wysokosc(wezel* w)
    {
        return (w == NULL ? -1 : w->wysokosc);
    }


    void DrzewoAVL::inorder(wezel* w)
    {
        if(w == NULL)
            return;
        inorder(w->lewy);
        cout << w->dana << " ";
        inorder(w->prawy);
    }



void DrzewoAVL::preorder(wezel *w)
{
    if (w == NULL)
        return;
    cout<< w->dana <<"  ";
    preorder(w->lewy);
    preorder(w->prawy);

}


void DrzewoAVL::postorder(wezel *w)
{
    if (w == NULL)
        return;
    postorder(w ->lewy);
    postorder (w ->prawy);
    cout<< w->dana <<"  ";
}

    //Funkcje dostępu dla użytkownika
     DrzewoAVL::DrzewoAVL()
    {
        korzen = NULL;
    }

    void DrzewoAVL::dodaj(int x)
    {
        korzen = dodaj(x, korzen);
    }

    void DrzewoAVL::usun(int x)
    {
        korzen = usun(x, korzen);
    }

    void DrzewoAVL::wyswietl()
    {
        cout<<"Inorder: ";
        inorder(korzen);
        cout<<endl<<"Postrder: ";
        postorder(korzen);
        cout<<endl<<"Preorder: ";
        preorder(korzen);
        cout<<endl;
    }

    void DrzewoAVL::getKorzen()
    {
        cout<<"Element w korzeniu drzewa: "<<korzen->dana<<endl;
    }

    void DrzewoAVL::wysokosc()
    {
        cout<<"Wysokosc drzewa: "<<korzen->wysokosc<<endl;
    }

    void DrzewoAVL::usun_wszystko()
    {
        usunWszystko(korzen);
    }

