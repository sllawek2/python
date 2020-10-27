#include "Wezel.h"

Wezel * Wezel::znajdzWezel(const std::string & etykieta)
{
    Wezel * tmp = this;

    // if (tmp->wejscie != etykieta)
    // {
    //     tmp
    // }





    if (this->wejscie == etykieta)
    {
        return this;
    }
    else
    {
        Wezel * tmp = nullptr;
        if(this->nie != nullptr)
        {
            tmp = this->nie->znajdzWezel(etykieta);
        }
        if (tmp != nullptr && )
    }
    return 
}

