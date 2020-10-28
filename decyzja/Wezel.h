#include <cstdlib>
#include <iostream>
#include <vector>
#include "Warunek.h"
#include "Grupa.h"

class Wezel
{
public:
    void dodajDoGrupy(std::vector<Grupa> &wynik, std::string dane);
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
   * @param std::string tekst
   * */
    bool dodajWezel(std::string tekst);

  /** 
   * @author imie b
   * @return string
   * @param std::string dane
   * */
    std::string znajdzEtykiete(std::string dane);

    std::string etykieta;
    Warunek war;
    Wezel * nie;
    Wezel * tak;
};