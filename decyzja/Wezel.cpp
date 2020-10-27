#include "Wezel.h"

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