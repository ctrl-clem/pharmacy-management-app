#ifndef OOP_LAB6_7_VALIDATOR_H
#define OOP_LAB6_7_VALIDATOR_H
#include "Medicament.h"
#include <utility>
#include <vector>
#include <string>
using std::string;
using std::vector;

class ValidationException
{
    vector <string> mesaj;
public:
    explicit ValidationException(vector<string> eroare): mesaj{std::move(eroare)} {};

    string getMesaj()
    {
        string msg = "";
        for(const string& e: mesaj)
            msg+= e+"\n";

        return msg;
    }

};

class Validator
{
public:
    void valideaza(const Medicament &m)
{
    vector<string> erori;
    if(m.getNume().length()<2)
        erori.push_back("Titlul trebuie sa aiba cel putin 2 caractere!");
    if(m.getSubstanta().length()<2)
        erori.push_back("Substanta trebuie sa aiba cel putin 2 caractere!");
    if(m.getProducator().length()<2)
        erori.push_back("Producatorul trebuie sa aiba cel putin 2 caractere!");
    if(m.getPret()<1)
        erori.push_back("Pretul nu poate fi mai mic decat 1!");
    if(!erori.empty())
        throw ValidationException(erori);

}
};

#endif //OOP_LAB6_7_VALIDATOR_H
