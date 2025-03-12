#ifndef OOP_LAB6_7_UI_H
#define OOP_LAB6_7_UI_H
#include "Service.h"
class UI
{
private:
    Service& service;
public:
    UI(Service& service): service{service}{};
    UI(const UI& other) = delete;
    static void printMenu();
    void run();
    ~UI()=default;

};
#endif //OOP_LAB6_7_UI_H
