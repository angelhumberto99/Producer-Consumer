#include <iostream>
#include "Manager.h"

int main() {
    HIDE_CURSOR;
    Manager m;
    m.StartSimulation();
    SHOW_CURSOR;
    std::cout << "Simulacion terminada, presione [ENTER] para continuar" << std::endl;
    std::cin.get();
    CLEAR;
    return 0;
}