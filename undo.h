#ifndef OOP_LAB6_7_UNDO_H
#define OOP_LAB6_7_UNDO_H
#include "Repository.h"
#include "Medicament.h"

class ActiuneUndo{

public:
    virtual void doUndo()=0;
    virtual ~ActiuneUndo()=default;
};

class UndoAdauga: public ActiuneUndo{
    RepoAbstract& repo;
    Medicament medicament;
public:
    UndoAdauga(RepoAbstract& repo, const Medicament& m) : repo{repo}, medicament{m}{};
    void doUndo() override{
        repo.deleteMed(medicament.getNume());
    }
};

class UndoSterge: public ActiuneUndo{
    RepoAbstract& repo;
    Medicament medicament;
public:
    UndoSterge(RepoAbstract& repo, const Medicament& m): repo{repo}, medicament{m}{};
    void doUndo() override{
        repo.addMed(medicament);
    }
};

class UndoModifica: public ActiuneUndo{
    RepoAbstract& repo;
    Medicament medicamentBefore;
    Medicament medicamentAfter;
public:
    UndoModifica(RepoAbstract& repo, const Medicament& m1,const Medicament& m2): repo{repo},medicamentBefore{m1}, medicamentAfter{m2}{};
    void doUndo() override{
        repo.deleteMed(medicamentAfter.getNume());
        repo.addMed(medicamentBefore);
    }
};
#endif //OOP_LAB6_7_UNDO_H
