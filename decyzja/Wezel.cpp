#include "Wezel.h"
#include <fstream>

std::string Wezel::znajdzEtykiete(std::string dane)
{
    Wezel * ptr = this;
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

Wezel * Wezel::nastepny(std::string wartosc, std::string & etykieta)
{
    if(war.oper == "<")
    {
        if (atof(wartosc.c_str()) < war.wartosc)
        {
            etykieta = wyjscieNie;
            return this->nie;
        }
        else
        {
            
            etykieta = wyjscieTak;
            return this->tak;
        }
    }
    else
    {
        if (atof(wartosc.c_str()) > war.wartosc)
        {
            etykieta = wyjscieNie;
            return this->nie;
        }
        else
        {
            etykieta = wyjscieTak;
            return this->tak;
        }
    }
}

Wezel * Wezel::dodaj(const std::string & tekst)
{
    return dodajWezel(this, tekst);
}

Wezel * Wezel::dodajWezel(Wezel * ptr, const std::string & tekst)
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

bool Wezel::wczytajDrzewo(std::string nazwaPliku)
{
    std::ifstream plik(nazwaPliku.c_str(), std::ios::in);
    std::string linia;
    
    Wezel * ptr = this;
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
                ptr = this->dodaj(indeks);
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
    return true;
}
