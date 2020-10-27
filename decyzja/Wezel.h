#include <cstdlib>
#include <iostream>
#include "Warunek.h"

class Wezel
{
public:
    std::string wejscie;
    Warunek war;
    std::string wyjscieNie;
    std::string wyjscieTak;
    Wezel * nie;
    Wezel * tak;
public:
    std::string znajdzEtykiete(std::string dane);
    
    ~Wezel()
    {
        delete nie;
        delete tak;
    }

private:
  /** abdc
   * @author imie b
   * @return wskaźnik obiekt Wezeł
   * @param std::string wart
   * */
    Wezel * nastepny(std::string wartosc, std::string & etykieta);
    Wezel * dodajWezel(Wezel * ptr, const std::string & tekst);
};