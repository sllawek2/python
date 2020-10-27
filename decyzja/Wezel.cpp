#include "Wezel.h"

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