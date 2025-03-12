#include "Repository.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;

void Repo::addMed(const Medicament &m) {

    auto it = std::find_if(this->getAll().begin(),this->getAll().end(),[=](const Medicament& m1){
        return m1.getNume() == m.getNume();
    });
    if(it == this->getAll().end())
        medicamente.push_back(m);
    else
        throw MyException("Medicament deja existent!");
    /*
    for (const Medicament &M: this->medicamente)
        if (M.getNume() == m.getNume()) {
            throw MyException("Medicament deja existent!");
        }
    medicamente.push_back(m);
     */
}

void Repo::deleteMed(const std::string &nume) {
    auto it = std::find_if(this->getAll().begin(),this->getAll().end(),[=](const Medicament& m1){
        return m1.getNume() == nume;
    });
    if(it == this->getAll().end())
        throw MyException("Medicamentul nu exista!");
    else
        medicamente.erase(it);

    /*for (auto i = medicamente.begin(); i != medicamente.end(); ++i)
        if (i->getNume() == nume) {
            medicamente.erase(i);
            return;
        }
    throw MyException("Medicamentul nu exista!");*/

}

void Repo::modificaMed(const Medicament &m) {
    //stergem medicamentul vechi
    deleteMed(m.getNume());
    //il adaugam in farmacie pe cel nou
    addMed(m);
}

void RepoFile::loadFromFile() {
    ifstream medFile(this->fileName);
    if (!medFile.is_open())
        throw MyException("Nu pot citi din fisierul "+ fileName);

    string line;
    while(getline(medFile,line))
    {
        string nume,producator,substanta;
        int pret;

        stringstream linestream(line);
        string curent;
        int nr=0;
        while(getline(linestream,curent,','))
        {
            if(nr==0)
                nume=curent;
            if(nr==1)
                pret=stoi(curent);
            if(nr==2)
                producator=curent;
            if(nr==3)
                substanta=curent;

            nr++;
        }

        Medicament m{nume,pret,producator,substanta};

        Repo::addMed(m);
    }

    medFile.close();

}


void RepoFile::saveToFile() {

    ofstream medFile(this->fileName);
    if(!medFile.is_open())
        throw MyException("Nu pot scrie in fisierul "+ fileName);
    for(const auto& med: getAll())
        medFile<<med.getNume()<<","<<med.getPret()<<","<<med.getProducator()<<","<<med.getSubstanta()<<endl;

    medFile.close();
}

void RepoFile::addMed(const Medicament &m) {
    Repo::addMed(m);
    saveToFile();
}

void RepoFile::deleteMed(const string &nume) {
    Repo::deleteMed(nume);
    saveToFile();
}

void RepoFile::modificaMed(const Medicament &m) {
    Repo::modificaMed(m);
    saveToFile();
}
