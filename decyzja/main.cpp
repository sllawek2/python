#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Wezel.h"
#include "Grupa.h"


Wezel * korzen = NULL;

/** doxygen
@author: imie nazwisko
@param: Wezel* wskaznik na Wezel
*/
void wyswietlDrzewo(Wezel * ptr)
{

    if(ptr != NULL)
    {
        std::cout << ptr->wyjscieNie<< " - "<< ptr->wyjscieTak <<std::endl;
        wyswietlDrzewo(ptr->nie);
        wyswietlDrzewo(ptr->tak);
    }
}

std::string znajdzEtykiete(Wezel * ptr,std::string dane)
{
    while (dane.empty() == false)
    {
        std::size_t pos = dane.find(' ');
        std::string wartosc = dane.substr(0, pos);
        std::string etykieta;
        Wezel * nastepny = ptr->nastepny(wartosc, etykieta);
        if (nastepny == NULL)
        {
            return etykieta;
        }
        else
        {
            ptr = nastepny;
        }
        dane = dane.substr(pos+1);
    }
}

Wezel * dodajWezel(Wezel * ptr, const std::string & tekst)
{
    // sprawdź etykiety
    if (ptr->wyjscieNie == tekst)
    {
        ptr->nie = new Wezel();
        return ptr->nie;
    }
    else if (ptr->wyjscieTak == tekst)
    {
        ptr->tak = new Wezel();
        return ptr->tak;
    }
    else
    {
        // etykiety nie zgadzały się, przejdź dalej po drzewie
        Wezel * tmp = NULL;
        if(ptr->nie != NULL)
        {
            tmp = dodajWezel(ptr->nie, tekst);
            if(tmp != NULL)
            {
                return tmp;
            }
        }
        if(ptr->tak != NULL)
        {
            tmp = dodajWezel(ptr->tak, tekst);
            if(tmp != NULL)
            {
                return tmp;
            }
        }
    }
    // koniec drzewa
    return NULL;
}

bool wczytajDrzewo(std::string nazwaPliku)
{
    std::ifstream plik(nazwaPliku.c_str(), std::ios::in);
    std::string linia;
    
    korzen = new Wezel();
    Wezel * ptr = korzen;
    bool pierwszyWezel = true;
    if(plik.good())
    {
        while(std::getline(plik, linia))
        {
            std::size_t pos = linia.find(' ');
            std::string indeks = linia.substr(0, pos);

            if (pierwszyWezel == true)
            {
                pierwszyWezel = false;
            }
            else
            {
                ptr = dodajWezel(korzen, indeks);
                if (ptr == NULL)
                {
                    std::cout<<"Problem z plikiem drzewa: nie ma takiego indeksu wejscia"<<std::endl;
                    return false;
                }
            }

            linia = linia.substr(pos+1);
            pos = linia.find(' ');
            ptr->war.atrybut = linia.substr(0, pos);

            linia = linia.substr(pos+1);
            pos = linia.find(' ');
            ptr->war.oper = linia.substr(0, pos);

            linia = linia.substr(pos+1);
            pos = linia.find(' ');
            ptr->war.wartosc = atof(linia.substr(0, pos).c_str());

            linia = linia.substr(pos+1);
            pos = linia.find(' ');
            ptr->wyjscieNie = linia.substr(0, pos);

            linia = linia.substr(pos+1);
            pos = linia.find(' ');
            ptr->wyjscieTak = linia.substr(0, pos);

            // std::cout << ptr->wyjscieNie<< " - "<< ptr->wyjscieTak <<std::endl;
        }
    }
    else
    {
        return false;
    }
    
    // wyswietlDrzewo(korzen);
    return true;
}

void dodajDoGrupy(std::vector<Grupa> &wynik, std::string dane)
{
   std::string etykieta = znajdzEtykiete(korzen, dane);
   bool juzIstnieje = false;
   for(std::vector<Grupa>::iterator iter = wynik.begin(); iter != wynik.end(); iter++)
   {
       if (iter->etykieta == etykieta)
       {
           juzIstnieje = true;
           iter->dane.push_back(dane);
       }
   }
   if (juzIstnieje == false)
   {
       Grupa tmp;
       tmp.etykieta = etykieta;
       tmp.dane.push_back(dane);
       wynik.push_back(tmp);
   }

}

bool wczytajDane(std::vector<std::string> & dane, std::string nazwaPliku)
{
    std::ifstream plik(nazwaPliku.c_str(), std::ios::in);
    if(plik.good())
    {
        std::string linia;
        if(std::getline(plik, linia))
        {
            while(std::getline(plik, linia))
            {
                dane.push_back(linia);
            }
        }
        else
        {
            std::cout<<"Plik: "<<nazwaPliku<<" jest pusty"<<std::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}


bool zapiszWynik(std::vector<Grupa> wynik, std::string nazwaPliku)
{
    std::ofstream plik(nazwaPliku.c_str(), std::ios::out);

    if(plik.good())
    {

        for (std::vector<Grupa>::iterator iter = wynik.begin(); iter != wynik.end(); ++iter)
        {
            plik<<iter->etykieta<<std::endl;
            for (std::vector<std::string>::iterator iter2 =  iter->dane.begin(); iter2 != iter->dane.end(); ++iter2)
            {
                plik<<*iter2<<std::endl;
            }
            plik<<std::endl;
        }
    }
    else
    {
        std::cout<<"Nie udało się utworzyć pliku wyjściowego"<<std::endl;
        return false;
    }
    
    return true;
}


int main(const int argc, char * argv[])
{
    // wczytanie parametrów
    std::string wejsciowy;
    std::string drzewa;
    std::string wyjsciowy;
    if (argc != 7)
    {
        std::cout<<"Nieprawidłowa ilość parametrów. Przykład użycia:\n"<<argv[0]<<" -i plik_wejsciowy -t plik_drzewa -o plik_wyjsciowy"<<std::endl;
        return 1;
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string parametr = argv[i];
            if (parametr == "-i") 
            {
                ++i;
                if(i<argc)
                {
                    wejsciowy = argv[i];
                }
            }
            if (parametr == "-t") 
            {
                ++i;
                if(i<argc)
                {
                    drzewa = argv[i];
                }
            }
            if (parametr == "-o") 
            {
                ++i;
                if(i<argc)
                {
                    wyjsciowy = argv[i];
                }
            }
        } 
    }

    // sprawdzenie wczytanych nazw plików
    if (wejsciowy.empty() || drzewa.empty() || wyjsciowy.empty())
    {
        std::cout<<"Nieprawidłowe parametry. Przykład użycia:\n"<<argv[0]<<" -i plik_wejsciowy -t plik_drzewa -o plik_wyjsciowy"<<std::endl;
        return 1;
    }

    // wczytanie danych z pliku do struktury drzewa
    if (wczytajDrzewo(drzewa) == false)
    {
        std::cout<<"Nie udało się wczytac drzewa z pliku: "<<drzewa<<std::endl;
        return 1;
    }

    std::vector<std::string> dane;
    if (wczytajDane(dane, wejsciowy) == false)
    {
        std::cout<<"Nie udało się wczytać danych z pliku: "<<wejsciowy<<std::endl;
    }

    std::vector<Grupa> wynik;

    for(std::vector<std::string>::iterator iter = dane.begin(); iter != dane.end(); ++iter)
    {
        dodajDoGrupy(wynik, *iter);
    }

    std::cout<<"--------WYNIK---------"<<std::endl;

    zapiszWynik(wynik, wyjsciowy);

    delete korzen;
    return 0;
}