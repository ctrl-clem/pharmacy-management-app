#ifndef OOP_LAB6_7_SERVICE_H
#define OOP_LAB6_7_SERVICE_H
#include <string>
#include <functional>
#include <map>
#include "Medicament.h"
#include "Repository.h"
#include "Validator.h"
#include "Reteta.h"
#include "undo.h"
#include <memory>
using std::unique_ptr;
using std::string;
using std::function;
using std::map;

class Service
{
private:
    RepoAbstract& repository;
    Validator& validator;

    vector<unique_ptr<ActiuneUndo>> actiuniUndo;
    Reteta currentReteta;


public:
    Service(RepoAbstract& repository, Validator& val) : repository{repository}, validator{val} {};

    Service(const Service& ot) = delete;

    /*Adauga un medicament. Arunca exceptie daca nu este valid.*/
    void add(string nume, int pret, string producator, string substanta);

    /*Cauta un medicament in farmacie si il returneaza, arunca exceptie daca nu exista*/
    const Medicament& cauta(const string& nume) const;

    /*Sterge un medicament cu numele dat.*/
    void deleteMed(const string& nume);

    /*Returneaza un vector cu toate medicamentele*/
    [[nodiscard]] const vector<Medicament>& getAll() const;

    /*Modifica un medicament, arunca exceptie daca nu exista*/
    void modifica(const string& nume, int pret, const string& producator, const string& substanta);


    [[nodiscard]] vector<Medicament> filtrarePret(int pret) const;

    [[nodiscard]] vector<Medicament> filtrareSubstanta(const string& substanta) const;

    vector<Medicament> generalSort(function<bool(const Medicament&, const Medicament&)> fct) const;

    void addReteta(const string& nume);

    void deleteReteta();

    void generateRandomReteta(int numar);

    [[nodiscard]] const vector<Medicament>& getAllReteta() const;

    [[nodiscard]] map<string,int> calculeaza() const;

    void exportRetetaCSV(string& nume) const;

    void exportRetetaHTML(string& nume) const;

    void undo();

    ~Service()=default;
};

bool cmpNume(const Medicament& m1, const Medicament& m2);

bool cmpProducator(const Medicament& m1, const Medicament& m2);

bool cmpSubstantaPret(const Medicament& m1, const Medicament& m2);


#endif //OOP_LAB6_7_SERVICE_H
