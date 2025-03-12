#include "Teste.h"
#include <cassert>
#include <fstream>

void testAll()
{
    testAddRepo();
    testAddService();
    testDelete();
    testCauta();
    testModifica();
    testValidator();
    testFilter();
    testSort();
    testAddReteta();
    testDeleteReteta();
    testGenerateRandom();
    testFileRepo();
    testUndo();
    testExport();
    testCalculeaza();
}

void testAddRepo()
{
    Repo repository;
    Medicament m{"nurofen",12,"prod","ibuprofen"};
    repository.addMed(m);
    assert(repository.getAll().size() == 1);
    assert(repository.getAll()[0].getNume() == "nurofen");
    assert(repository.getAll()[0].getPret() == 12);
    assert(repository.getAll()[0].getProducator() == "prod");
    assert(repository.getAll()[0].getSubstanta() == "ibuprofen");

    try{
        repository.addMed(m);
    }
    catch(MyException& ex){
        assert(true);
    }

}

void testAddService()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    assert(service.getAll().size() == 2);
    try
    {
        service.add("nurofen",12,"ceva","ibruprofen");
    }
    catch(MyException& ex){
        assert(ex.getMesaj() == "Medicament deja existent!");
    }
}

void testDelete()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");

    service.deleteMed("nurofen");
    assert(service.getAll().size() == 1);
    try{
        service.deleteMed("sgsh");
        assert(false);
    }
    catch(MyException& ex){
        //cout<<ex.getMesaj();
        assert(ex.getMesaj() == "Acest medicament nu exista!");
    }
}

void testCauta()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");

    Medicament m = service.cauta("nurofen");

    assert(m.getNume() == "nurofen");
    assert(m.getSubstanta() == "ibruprofen");
    assert(m.getProducator() == "ceva");
    assert(m.getPret() == 12);

    try{
        service.cauta("aaaa");
    }
    catch(MyException &str){
        assert(str.getMesaj() == "Acest medicament nu exista!");
    }
}

void testModifica()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");

    service.modifica("nurofen",13,"altceva","ibuprofen");

    assert(service.getAll().size() == 2);
    assert(service.getAll()[1].getNume() == "nurofen");
    assert(service.getAll()[1].getPret() == 13);
    assert(service.getAll()[1].getProducator() == "altceva");
    assert(service.getAll()[1].getSubstanta() == "ibuprofen");

    try{
        service.modifica("nu exista",45,"skdjfn","sfjn");
    }
    catch(MyException& str){
        assert(str.getMesaj() == "Acest medicament nu exista!");
    }

    try{
        service.modifica("nurofen",-1,"s","k");
    }
    catch(ValidationException& ex){
        assert(ex.getMesaj() == "Substanta trebuie sa aiba cel putin 2 caractere!\nProducatorul trebuie sa aiba cel putin 2 caractere!\nPretul nu poate fi mai mic decat 1!\n" );
    }
}

void testValidator()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    try{
        service.add("a",-1,"s","d");
    }
    catch(ValidationException& ex){
        assert(ex.getMesaj() == "Titlul trebuie sa aiba cel putin 2 caractere!\nSubstanta trebuie sa aiba cel putin 2 caractere!\nProducatorul trebuie sa aiba cel putin 2 caractere!\nPretul nu poate fi mai mic decat 1!\n");
    }

    try{
        service.add("a",1,"kdfj","ksfjg");
    }
    catch(ValidationException& ex){
        assert(ex.getMesaj() == "Titlul trebuie sa aiba cel putin 2 caractere!\n");
    }
}

void testFilter()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");


    vector<Medicament> m= service.filtrareSubstanta("ibruprofen");
    assert(m.size()==2);
    assert(service.filtrarePret(100).size()==2);
}

void testSort()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    vector<Medicament> rez1 = service.generalSort(cmpNume);
    vector<Medicament> rez2 = service.generalSort(cmpProducator);
    vector<Medicament> rez3 = service.generalSort(cmpSubstantaPret);

    assert(rez1[0].getNume() == "d,f");
    assert(rez1[5].getNume() == "xf,vj");

    assert(rez2[0].getProducator() == "ceva");
    assert(rez2[5].getProducator() == "skdjfn");

    assert(rez3[0].getNume() == "nurofen");
    assert(rez3[1].getNume() == "mfxnv");
    assert(rez3[2].getNume() == "d,f");
}

void testAddReteta()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    service.addReteta("nurofen");
    service.addReteta("nume");

    vector<Medicament> m = service.getAllReteta();
    assert(m.size()==2);
    assert(m[0].getNume()=="nurofen");
    assert(m[1].getNume()=="nume");

    try{
        service.addReteta("nurofen");
    }
    catch(const MyException& s){
        assert(s.getMesaj() == "Acest medicament exista deja in reteta!");
    }
}

void testDeleteReteta()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    service.addReteta("nurofen");
    service.addReteta("nume");
    service.deleteReteta();
    assert(service.getAllReteta().empty());
}

void testGenerateRandom()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    service.generateRandomReteta(3);
    vector<Medicament> m = service.getAllReteta();
    assert(m.size()==3);

    service.generateRandomReteta(100);
    m=service.getAllReteta();
    assert(m.size()==6);
}

void testFileRepo()
{
    std::ofstream out("testFileRepo.txt",std::ios::trunc);
    out.close();
    RepoFile repository{"testFileRepo.txt"};
    repository.addMed(Medicament{"nume",12,"prod","substanta"});

    RepoFile repository2{"testFileRepo.txt"};
    auto m=repository2.getAll();
    assert(m[0].getNume()=="nume");
    assert(m[0].getProducator()=="prod");
    assert(m[0].getPret()==12);
    assert(m[0].getSubstanta()=="substanta");

    repository2.deleteMed("nume");
    assert(repository2.getAll().empty());
    try{
        repository2.deleteMed("ceva");
    }
    catch (MyException&){
    }

    RepoFile repository3{"testFileRepo.txt"};
    assert(repository3.getAll().empty());
    repository3.addMed(Medicament{"nume",12,"prod","substanta"});
    repository3.modificaMed(Medicament{"nume",13,"aaaa","bbbb"});

    RepoFile repository4{"testFileRepo.txt"};
    assert(repository4.getAll().size()==1);
    m=repository3.getAll();
    assert(m[0].getNume()=="nume");
    assert(m[0].getProducator()=="aaaa");
    assert(m[0].getPret()==13);
    assert(m[0].getSubstanta()=="bbbb");

    try{
        RepoFile repostory5{"test/FileRepo.txt"};
    }
    catch(...){
    }


}


void testUndo()
{
    Repo repo;
    Validator val;
    Service service{repo,val};
    try{
        service.undo();
    }
    catch (MyException& ex){
        assert(ex.getMesaj()=="Nu mai exista operatii!\n");
    }
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    service.undo();
    assert(service.getAll().size()==5);
    try{
        service.cauta("s,dfj");
    }
    catch(MyException& ex){
        assert(ex.getMesaj()=="Acest medicament nu exista!");
    }
    service.deleteMed("nurofen");
    service.undo();
    assert(service.getAll().size()==5);
    Medicament m = service.cauta("nurofen");
    assert(m.getNume()=="nurofen");
    assert(m.getPret()==12);
    assert(m.getProducator()=="ceva");
    assert(m.getSubstanta()=="ibruprofen");

    service.modifica("d,f",12,"altceva","subst");
    service.undo();
    m = service.cauta("d,f");
    assert(m.getNume()=="d,f");
    assert(m.getProducator()=="ceva");
    assert(m.getPret()==122);
    assert(m.getSubstanta()=="ibruprofen");
}

void testExport()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    service.addReteta("nurofen");
    service.addReteta("nume");

    string nume="testExport.html";
    service.exportRetetaHTML(nume);
    string numeRau="test/Export.html";
    try{
        service.exportRetetaHTML(numeRau);
    }
    catch (MyException& ex){
        assert(ex.getMesaj()=="Nu pot deschide fisierul "+numeRau);
    }

    string nume1="testExport1.cvs";
    service.exportRetetaCSV(nume1);
    string nume1Rau="test/Export.cvs";
    try{
        service.exportRetetaCSV(nume1Rau);
    }
    catch (MyException& ex){
        assert(ex.getMesaj()=="Nu pot deschide fisierul "+nume1Rau);
    }

}

void testCalculeaza()
{
    Repo repo;
    Validator validator;
    Service service{repo,validator};
    service.add("nurofen",12,"ceva","ibruprofen");
    service.add("nume",13,"skdjfn","ksjfn");
    service.add("mfxnv",100,"ceva","ibruprofen");
    service.add("xf,vj",1873,"skdjfn","ksjfn");
    service.add("d,f",122,"ceva","ibruprofen");
    service.add("s,dfj",4,"skdjfn","ksjfn");

    map<string,int> dict = service.calculeaza();
    assert(dict.size()==2);
    assert(dict["ceva"]==3);
    assert(dict["skdjfn"]==3);
}