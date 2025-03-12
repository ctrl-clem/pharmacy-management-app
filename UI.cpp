#include "UI.h"
#include <iostream>
#include <stdexcept>
using std::cout;
using std::cin;
void UI::printMenu()
{
    cout<<" 1. Adaugare medicament\n 2. Stergere medicament\n 3. Modifica medicament\n 4. Afiseaza farmacie\n 5. Cauta\n 6. Filtrare pret\n 7. Filtrare substanta\n 8. Sortare nume\n"
          " 9. Sortare producator\n 10. Sortare substanta activa+pret\n 11. Adauga medicament in reteta dupa nume\n 12. Sterge reteta\n 13. Genereaza reteta\n 14. Afiseaza reteta\n"
          " 15. Afiseaza dictionar\n 16. Export reteta CSV\n 17. Export reteta HTML\n 18. Undo\n 0. Exit\n";
}

void UI::run()
{
    while(true)
    {
        int cmd=0;
        printMenu();
        cin>>cmd;
        if(cmd == 0)
            break;
        else if(cmd == 1)
        {
            string nume,producator,substanta;
            int pret=0;
            cout<<"Nume: ";
            cin>>nume;
            cout<<"Pret: ";
            cin >> pret;
            cout<<"Producator: ";
            cin>>producator;
            cout<<"Substanta: ";
            cin>>substanta;
            try {
                service.add(nume, pret, producator, substanta);
                cout<<"Medicament adaugat cu succes!\n";
            }
            catch(MyException& ex){
                cout<<ex.getMesaj()<<"\n";
            }
            catch(ValidationException& ex){
                cout<<ex.getMesaj()<<"\n";
            }

        }
        else if(cmd == 2)
        {
            string nume;
            cout<<"Introduceti numele medicamentului de sters: ";
            cin>>nume;
            try{
                service.deleteMed(nume);
                cout<<"Stergerea a fost efectuata cu succes!\n";
            }
            catch(MyException& ex){
                cout<<ex.getMesaj()<<"\n";
            }
        }
        else if(cmd == 3)
        {
            string nume,prodNou,subNoua;
            cout<<"Introduceti numele medicamentului pe care doriti sa il modificati: ";
            cin>>nume;
            int pretNou=0;
            cout<<"Introduceti noul pret: ";
            cin>>pretNou;
            cout<<"Introduceti noul producator: ";
            cin>>prodNou;
            cout<<"Introduceti noua substanta activa: ";
            cin>>subNoua;
            try{
                service.modifica(nume,pretNou,prodNou,subNoua);
                cout<<"Medicament modificat cu succes!\n";
            }
            catch(ValidationException& ex){
                cout<<ex.getMesaj()<<"\n";
            }
            catch(MyException& ex){
                cout<<ex.getMesaj()<<"\n";
            }
        }
        else if(cmd == 4)
        {
            const vector<Medicament>& m = service.getAll();
            for(const auto& med:m)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";

        }
        else if(cmd == 5)
        {
            string nume;
            cout<<"Introduceti numele medicamentului pe care doriti sa il cautati\n";
            cin>>nume;
            try {
                Medicament med = service.cauta(nume);
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";
            }
            catch(MyException &str){
                cout<<str.getMesaj()<<"\n";
            }
        }
        else if(cmd==6)
        {
            int pret;
            cout<<"Introduceti pretul dupa care doriti sa filtrati\n";
            cin>>pret;
            vector<Medicament> rez = service.filtrarePret(pret);
            for(const auto& med: rez)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";
        }

        else if(cmd==7)
        {
            string substanta;
            cout<<"Introduceti substanta dupa care doriti sa filtrati\n";
            cin>>substanta;
            vector<Medicament> rez = service.filtrareSubstanta(substanta);
            for(const auto& med: rez)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";
        }
        else if(cmd == 8)
        {
            vector<Medicament> rez = service.generalSort(cmpNume);
            if(rez.size()>0)
            for(const auto& med: rez)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";

        }
        else if(cmd == 9)
        {
            vector<Medicament> rez = service.generalSort(cmpProducator);
            for(const auto& med: rez)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";

        }
        else if(cmd == 10)
        {
            vector<Medicament> rez = service.generalSort(cmpSubstantaPret);
            for(const auto& med: rez)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";

        }
        else if(cmd == 11)
        {
            cout<<"Introduceti numele medicamentului pe care doriti sa il adaugati in reteta: ";
            string nume;
            cin>>nume;
            try {
                service.addReteta(nume);
                cout<<"Medicament introdus cu succes!\n";

            }
            catch(const MyException& s){
                cout<<s.getMesaj()<<"\n";
            }
            cout<<"Reteta are: "<<service.getAllReteta().size()<<" medicamente\n";
        }
        else if(cmd == 12)
        {
            service.deleteReteta();
            cout<<"Reteta stearsa cu succes!\n";
            cout<<"Reteta are: "<<service.getAllReteta().size()<<" medicamente\n";
        }
        else if(cmd == 13)
        {
            cout<<"Introduceti numarul de medicamente dorit: ";
            int numar;
            cin>>numar;
            service.generateRandomReteta(numar);
            cout<<"Reteta creata cu succes!\n";
            cout<<"Reteta are: "<<service.getAllReteta().size()<<" medicamente\n";
        }
        else if(cmd==14)
        {
            vector<Medicament> reteta = service.getAllReteta();
            for(const auto& med: reteta)
                cout<<"Nume: "<< med.getNume()<<" Pret: "<<med.getPret()<<" Producator: "<< med.getProducator()<<" Substanta: "<<med.getSubstanta()<<"\n";

            cout<<"Reteta are: "<<reteta.size()<<" medicamente\n";
        }
        else if(cmd == 15)
        {
            map<string, int> d = service.calculeaza();
            for(const auto& it:d)
            {
                cout<<"Producatorul "<<it.first<<" are "<<it.second<<" medicamente\n";
            }
        }
        else if(cmd==16)
        {
            string numeFisier;
            cout<<"Numele fisierului CSV: ";
            cin>>numeFisier;
            service.exportRetetaCSV(numeFisier);
            cout<<"Reteta are: "<<service.getAllReteta().size()<<" medicamente\n";
        }
        else if(cmd==17)
        {
            string numeFisier;
            cout<<"Numele fisierului HTML: ";
            cin>>numeFisier;
            service.exportRetetaHTML(numeFisier);
            cout<<"Reteta are: "<<service.getAllReteta().size()<<" medicamente\n";
        }
        else if(cmd==18)
        {
            try{
                service.undo();
                cout<<"Undo-ul a fost realizat cu succes!\n";
            }
            catch(MyException& ex){
                cout<<ex.getMesaj();
            }
        }

    }
}


