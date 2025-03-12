#ifndef OOP_LAB6_7_RETETA_H
#define OOP_LAB6_7_RETETA_H
#include <vector>
#include "Medicament.h"
using std::vector;
class Reteta{
private:
    vector<Medicament> medicamenteReteta;

public:
    Reteta()=default;

    void addMedicamentReteta(const Medicament& m);

    void deleteReteta();

    void generateRandom(int numar, vector<Medicament> m);

    [[nodiscard]] const vector<Medicament>& getAllReteta() const;

    ~Reteta()=default;
};
#endif //OOP_LAB6_7_RETETA_H
