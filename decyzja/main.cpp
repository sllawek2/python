#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Wezel.h"
#include "Grupa.h"



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
        // etykiety nie zgadzaly sie, przejdź dalej po drzewie
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

bool wczytajDrzewo(Wezel * & korzen, std::string nazwaPliku)
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
        }
    }
    else
    {
        return false;
    }
    
    // wyswietlDrzewo(korzen);
    return true;
}

void dodajDoGrupy(std::vector<Grupa> &wynik, std::string dane, Wezel * korzen)
{
   std::string etykieta = korzen->znajdzEtykiete(dane);
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
        std::cout<<"Nie udalo sie utworzyc pliku wyjsciowego: "<<nazwaPliku<<std::endl;
        return false;
    }
    
    return true;
}

/** Funkcja sprawdzajaca parametry
 * 
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
    Wezel * korzen = NULL;
    if (wczytajDrzewo(korzen, plikDrzewa) == false)
    {
        std::cout<<"Nie udalo sie wczytac drzewa z pliku: "<<plikDrzewa<<std::endl;
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
        dodajDoGrupy(wynik, *iter, korzen);
    }

    // zapisanie wyniku ze struktury do pliku
    if (zapiszWynik(wynik, plikWyjsciowy) == false)
    {
        return 1;
    }

    delete korzen;
    return 0;
}