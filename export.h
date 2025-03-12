#ifndef OOP_LAB6_7_EXPORT_H
#define OOP_LAB6_7_EXPORT_H

#include "Medicament.h"
#include <vector>
using std::vector;

void exportCSV(string& nume, const vector<Medicament>& meds);

void exportHTML(string& nume, const vector<Medicament>& meds);

#endif //OOP_LAB6_7_EXPORT_H
