#include <fstream>
#include <iostream>
#include "export.h"
#include "Repository.h"
void exportCSV(string& nume, const vector<Medicament>& meds)
{
    std::ofstream out(nume,std::ios::trunc);
    if(!out.is_open())
        throw MyException("Nu pot deschide fisierul "+nume);
    for(const auto& m:meds)
    {
        out<<m.getNume()<<","<<m.getPret()<<","<<m.getProducator()<<","<<m.getSubstanta()<<std::endl;
    }

    out.close();
}

void exportHTML(string& nume, const vector<Medicament>& meds)
{
    std::ofstream out(nume, std::ios::trunc);
    if(!out.is_open())
        throw MyException("Nu pot deschide fisierul "+nume);

    out<<"<html><body>"<<std::endl;
    out<<"<table border= \"1\" style=\"width:100 % \" > "<<std::endl;
    for(const auto& m:meds)
    {
        out<<"<tr>"<<std::endl;
        out<<"<td>"<<m.getNume()<<"</td>"<<std::endl;
        out<<"<td>"<<m.getPret()<<"</td>"<<std::endl;
        out<<"<td>"<<m.getProducator()<<"</td>"<<std::endl;
        out<<"<td>"<<m.getSubstanta()<<"</td>"<<std::endl;
        out<<"</tr>"<<std::endl;
    }

    out<<"</table>"<<std::endl;
    out<<"</body></html>"<<std::endl;
    out.close();
}