#include "Reteta.h"
#include "Repository.h"
#include <algorithm>
#include <random>
using std::shuffle;

void Reteta::addMedicamentReteta(const Medicament& m) {
    for(const auto& med: medicamenteReteta)
    {
        if(med.getNume()==m.getNume())
        {
            throw MyException("Acest medicament exista deja in reteta!");            return;
        }
    }

    medicamenteReteta.push_back(m);

}

void Reteta::deleteReteta() {

    medicamenteReteta.clear();

}

void Reteta::generateRandom(int numar, vector<Medicament> m) {

    deleteReteta();
    shuffle(m.begin(),m.end(),std::default_random_engine(std::random_device{}()));
    for(int i=0; i<numar && !m.empty(); i++)
    {
        medicamenteReteta.push_back(m.back());
        m.pop_back();
    }
}

const vector<Medicament> &Reteta::getAllReteta() const {
    return medicamenteReteta;
}
