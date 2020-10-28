#include <cstdlib>
#include <iostream>
#include "Warunek.h"

class Wezel
{
public:
    std::string znajdzEtykiete(std::string dane);
    bool wczytajDrzewo(std::string nazwaPliku);

    Wezel (std::string etykieta)
    {
        this->etykieta = etykieta;
        this->nie = NULL;
        this->tak = NULL;
    }
    
    ~Wezel()
    {
        delete nie;
        delete tak;
    }

private:
  /** 
   * @author imie b
   * @return bool
   * @param std::string wart
   * */
    bool dodajWezel(std::string tekst);

    std::string etykieta;
    Warunek war;
    Wezel * nie;
    Wezel * tak;
};