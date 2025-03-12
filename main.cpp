#include <iostream>
#include "UI.h"
#include "Teste.h"
#include "TemplateVectorDinamic.h"
#include "Test.h"
using std::cin;
using std::cout;
int main() {
    testAll();
    testAll1<MyVector<Medicament>>();
    RepoFile repo{"date.txt"};
    Validator validator;
    Service service{repo,validator};
    UI ui{service};

    ui.run();
    return 0;
}
