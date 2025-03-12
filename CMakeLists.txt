cmake_minimum_required(VERSION 3.27)
project(OOP_lab6_7)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_executable(OOP_lab6_7 main.cpp
        Medicament.cpp
        Medicament.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        UI.cpp
        UI.h
        Teste.cpp
        Teste.h
        Validator.cpp
        Validator.h
        TemplateVectorDinamic.h
        Test.h
        Reteta.cpp
        Reteta.h
        export.cpp
        export.h
        undo.cpp
        undo.h
)


