#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Wezel.h"

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
        std::cout<<"Nie udalo sie utworzyc pliku wyjsciowego: "<<nazwaPliku<<std::endl;
        return false;
    }
    
    return true;
}

/** Funkcja sprawdzajaca parametry
 * @return true albo false
 */
bool wczytajParametry(const int argc, const char * argv[], std::string & wejsciowy, std::string & drzewa, std::string & wyjsciowy)
{
    if (argc != 7)
    {
        std::cout<<"Nieprawidlowa ilosc parametrow."<<std::endl;
        return false;
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
    if (wejsciowy.empty() || drzewa.empty() || wyjsciowy.empty())
    {
        std::cout<<"Nieprawidlowe parametry"<<std::endl;
        return false;
    }
    return true;
}

int main(const int argc, const char * argv[])
{

    // nazwy plikow
    std::string plikWejsciowy;
    std::string plikDrzewa;
    std::string plikWyjsciowy;
  
    // sprawdzenie wczytanych nazw plikow
    if (wczytajParametry(argc, argv, plikWejsciowy, plikDrzewa, plikWyjsciowy) == false)
    {
        std::cout<<"Przyklad uzycia:\n"<<argv[0]<<" -i plik_wejsciowy -t plik_drzewa -o plik_wyjsciowy"<<std::endl;
        return 1;
    }

    // wczytanie drzewa z pliku do struktury drzewa
    Wezel * korzen = new Wezel("0");
    if (korzen->wczytajDrzewo(plikDrzewa) == false)
    {
        std::cout<<"Nie udalo sie wczytac drzewa z pliku: "<<plikDrzewa<<std::endl;
        delete korzen;
        return 1;
    }

    // wczytanie danych z pliku
    std::vector<std::string> dane;
    if (wczytajDane(dane, plikWejsciowy) == false)
    {
        std::cout<<"Nie udalo sie wczytac danych z pliku: "<<plikWejsciowy<<std::endl;
    }

    // przyporzadkowanie wartosci do odpowiednich etykiet
    std::vector<Grupa> wynik;
    for(std::vector<std::string>::iterator iter = dane.begin(); iter != dane.end(); ++iter)
    {
        korzen->dodajDoGrupy(wynik, *iter);
    }

    // zapisanie wyniku ze struktury do pliku
    if (zapiszWynik(wynik, plikWyjsciowy) == false)
    {
        delete korzen;
        return 1;
    }

    delete korzen;
    return 0;
}