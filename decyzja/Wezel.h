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
    Wezel * nastepny(std::string wartosc, std::string & etykieta);

    ~Wezel()
    {
        delete nie;
        delete tak;
    }
};