#ifndef OOP_LAB6_7_MEDICAMENT_H
#define OOP_LAB6_7_MEDICAMENT_H
#include <string>
#include <iostream>
#include <utility>
using std::cout;
using std::string;

class Medicament
{
private:
    string nume;
    int pret;
    string producator;
    string substanta;

public:
    Medicament() = default;

    Medicament(string nume, int pret, string producator, string substanta) : nume{ std::move(nume) }, pret{ pret }, producator{std::move(producator)}, substanta{std::move(substanta)}{
    }

    //constructor de copiere
    Medicament(const Medicament& other) = default;

    /*Returneaza numele medicamentului*/
    [[nodiscard]] std::string getNume() const{
        return this->nume;
    }

    /*Returneaza producatorul medicamentului*/
    [[nodiscard]] std::string getProducator() const{
        return this->producator;
    }

    /*Returneaza substanta medicamentului*/
    [[nodiscard]] std::string getSubstanta() const{
        return this->substanta;
    }

    /*Returneaza pretul medicamentului*/
    [[nodiscard]] int getPret() const{

        return this->pret;
    }

    ~Medicament() = default;
};




#endif //OOP_LAB6_7_MEDICAMENT_H
