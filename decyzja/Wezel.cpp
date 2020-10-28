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
        if ( ptr->nie == NULL || ptr->tak == NULL)
        {
            return ptr->etykieta;
        }
        else if(ptr->war.oper == "<")
        {
            if (atof(wartosc.c_str()) < ptr->war.wartosc)
            {
                ptr = ptr->nie;
            }
            else
            {
                ptr = ptr->tak;
            }
        }
        else
        {
            if (atof(wartosc.c_str()) > ptr->war.wartosc)
            {
                ptr = ptr->nie;
            }
            else
            {
                ptr = ptr->tak;
            }
        }        
        dane = dane.substr(pos+1);
    }
}

bool Wezel::dodajWezel(std::string linia)
{
    bool ret = false;
    std::size_t pos = linia.find(' ');
    std::string indeks = linia.substr(0, pos);
    if (this->etykieta == indeks)
    {
        linia = linia.substr(pos+1); 
        pos = linia.find(' ');
        this->war.atrybut = linia.substr(0, pos);

        linia = linia.substr(pos+1);
        pos = linia.find(' ');
        this->war.oper = linia.substr(0, pos);

        linia = linia.substr(pos+1);
        pos = linia.find(' ');
        this->war.wartosc = atof(linia.substr(0, pos).c_str());

        linia = linia.substr(pos+1);
        pos = linia.find(' ');
        this->nie = new Wezel(linia.substr(0, pos));

        linia = linia.substr(pos+1);
        pos = linia.find(' ');
        this->tak = new Wezel(linia.substr(0, pos));
        ret = true;
    }
    if (ret == false && this->tak != NULL)
    {
        ret = this->tak->dodajWezel(linia);
    }
    if (ret == false && this->nie != NULL)
    {
        ret = this->nie->dodajWezel(linia);        
    }
    return ret;
}

bool Wezel::wczytajDrzewo(std::string nazwaPliku)
{
    std::ifstream plik(nazwaPliku.c_str(), std::ios::in);
    std::string linia;

    if(plik.good())
    {
        while(std::getline(plik, linia))
        {
            if( this->dodajWezel(linia) == false)
            {
                std::cout<<"Problem z plikiem drzewa: nie ma takiego indeksu wejscia"<<std::endl;
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

void Wezel::dodajDoGrupy(std::vector<Grupa> &wynik, std::string dane)
{
   std::string etykieta = this->znajdzEtykiete(dane);
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
