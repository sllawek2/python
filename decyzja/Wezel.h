#include <cstdlib>
#include <iostream>
#include "Warunek.h"

struct Wezel
{
    std::string wejscie;
    Warunek war;
    std::string wyjscieNie;
    std::string wyjscieTak;
    Wezel * nie;
    Wezel * tak;
  

  /** abdc
   * @author imie b
   * @return wskaźnik obiekt Wezeł
   * @param std::string wart
   * */
    Wezel * nastepny(std::string wartosc, std::string & etykieta)
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

    ~Wezel()
    {
        delete nie;
        delete tak;
    }
};