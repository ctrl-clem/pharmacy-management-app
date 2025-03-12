#ifndef OOP_LAB6_7_REPOSITORY_H
#define OOP_LAB6_7_REPOSITORY_H
#include <utility>
#include <vector>
#include "Medicament.h"
#include "TemplateVectorDinamic.h"
#include <exception>
#include <stdexcept>
using std::vector;

class RepoAbstract{

public:
    virtual void addMed(const Medicament& m)=0;
    virtual void deleteMed(const string& nume)=0;
    virtual const vector<Medicament>& getAll() const=0;
    virtual void modificaMed(const Medicament& m)=0;
};

class Repo :public RepoAbstract
{
private:
    vector<Medicament> medicamente;

public:
    Repo() = default;

    Repo(const Repo& other) = delete;

    /*Adauga un medicament in Repo*/
    void addMed(const Medicament& m) override;

    /*Sterge un medicament din Repo cu un nume dat. Arunca exceptie daca medicamentul nu exista.*/
    void deleteMed(const string& nume) override;

    /*Returneaza toate medicamentele*/
    [[nodiscard]] const vector<Medicament>& getAll() const override{
        return this->medicamente;
    }

    /*Modifica un medicament din farmacie*/
    void modificaMed(const Medicament& m) override;

    ~Repo()=default;

};


class RepoFile: public Repo{
private:
    string fileName;
    void loadFromFile();
    void saveToFile();
public:
    RepoFile(string filename): Repo(),fileName{filename} {loadFromFile();};
    void addMed(const Medicament& m) override;
    void deleteMed(const string& nume) override;
    void modificaMed(const Medicament& m) override;
};

class MyException{
public:
    string mesaj;
    explicit MyException(string m) : mesaj{std::move(m)}{};
    [[nodiscard]] string getMesaj() const
    {
        return mesaj;
    }
};
#endif //OOP_LAB6_7_REPOSITORY_H
