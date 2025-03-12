#include "Service.h"
#include "export.h"
#include <utility>
#include <algorithm>
void Service::add(std::string nume, int pret, std::string producator, std::string substanta)
{
    Medicament m{std::move(nume),pret,std::move(producator),std::move(substanta)};
    validator.valideaza(m);
    repository.addMed(m);
    actiuniUndo.push_back(std::make_unique<UndoAdauga>(repository,m));
}

const vector<Medicament>& Service::getAll() const
{
    return this->repository.getAll();
}

void Service::deleteMed(const std::string& nume)
{
    Medicament m{cauta(nume).getNume(),cauta(nume).getPret(), cauta(nume).getProducator(),cauta(nume).getSubstanta()};
    repository.deleteMed(nume);
    actiuniUndo.push_back(std::make_unique<UndoSterge>(repository,m));

}

const Medicament& Service::cauta(const string& nume) const
{
    auto it = std::find_if(this->getAll().begin(),this->getAll().end(),[=](const Medicament& m){
        return m.getNume() == nume;
    });
    if(it!= this->getAll().end())
        return (*it);
    else
        throw MyException("Acest medicament nu exista!");
    /*for(const Medicament& med : repository.getAll())
    {
        if(med.getNume() == nume)
            return med;
    }
    throw string("Acest medicament nu exista!");*/
}

void Service::modifica(const string& nume, const int pret, const string& producator, const string& substanta)
{
    Medicament m{cauta(nume).getNume(),cauta(nume).getPret(), cauta(nume).getProducator(),cauta(nume).getSubstanta()};
    Medicament m1 {nume,pret,producator,substanta};
    validator.valideaza(m1);
    repository.modificaMed(m1);
    actiuniUndo.push_back(std::make_unique<UndoModifica>(repository,m,m1));
}

vector<Medicament> Service::filtrarePret(int pret) const {
    vector<Medicament> rez;
    const vector<Medicament>& all = getAll();
    std::copy_if(all.begin(),all.end(),back_inserter(rez),[pret](const Medicament& m){
        return m.getPret() < pret;
    });

    return rez;
}

vector<Medicament> Service::filtrareSubstanta(const string& substanta) const {
    vector<Medicament> rez;
    const vector<Medicament>& all = getAll();
    std::copy_if(all.begin(),all.end(),back_inserter(rez),[substanta](const Medicament& m){
        return m.getSubstanta() == substanta;
    });

    return rez;
}


vector<Medicament> Service::generalSort(function<bool(const Medicament &, const Medicament &)> fct) const  {
    vector<Medicament> rez = getAll();
    sort(rez.begin(),rez.end(), fct);
    return rez;
}

void Service::addReteta(const string &nume) {
    const Medicament& m=cauta(nume);
    currentReteta.addMedicamentReteta(m);
}

void Service::deleteReteta() {
    currentReteta.deleteReteta();
}

void Service::generateRandomReteta(int numar) {
    currentReteta.generateRandom(numar,this->getAll());
}

const vector<Medicament>& Service::getAllReteta() const {
    return currentReteta.getAllReteta();

}

map<string, int> Service::calculeaza() const {
    vector<Medicament> all = getAll();
    map<string, int> dictionar;
    for(const auto& med:all)
    {
        if(dictionar.find(med.getProducator()) == dictionar.end())
        {
            dictionar.insert({med.getProducator(),1});
        }
        else
            dictionar[med.getProducator()]++;
    }

    return dictionar;
}

void Service::exportRetetaCSV(string &nume) const {
    exportCSV(nume, getAllReteta());

}

void Service::exportRetetaHTML(string &nume) const {
    exportHTML(nume,getAllReteta());
}

void Service::undo() {
    if(actiuniUndo.empty())
        throw MyException("Nu mai exista operatii!\n");
    actiuniUndo.back()->doUndo();
    actiuniUndo.pop_back();

}

bool cmpNume(const Medicament& m1, const Medicament& m2) {

        return m1.getNume() < m2.getNume();

}

bool cmpProducator(const Medicament& m1, const Medicament& m2) {

        return m1.getProducator() < m2.getProducator();

}

bool cmpSubstantaPret(const Medicament& m1, const Medicament& m2) {

        if (m1.getSubstanta() == m2.getSubstanta())
            return m1.getPret() < m2.getPret();
        else
            return m1.getSubstanta() < m2.getSubstanta();

}


