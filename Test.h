
#ifndef OOP_LAB6_7_TEST_H
#define OOP_LAB6_7_TEST_H
#include "Medicament.h"
#include "TemplateVectorDinamic.h"
#include <cassert>
#include <iostream>
using std::cout;
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    int totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.getPret();
    }
    Medicament p{ "total",totalPrice,"tt", "ksdfjb"};
    v.add(p);
    return v;
}

template <typename MyVector>
void addMeds(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Medicament p{ std::to_string(i)+"_name", i, std::to_string(i)+"_prod",std::to_string(i)+"_subst"};
        v.add(p);
    }
}

template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addMeds(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).getNume() == "50_name");


    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).getNume() == "50_name");


    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);


    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);

}
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addMeds(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}

template <typename MyVector>
void testAll1() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}
#endif //OOP_LAB6_7_TEST_H
