#include "Manager.h"

Manager::Manager() {
    // llenamos el contenedor con guiones bajos
    for (int i = 0; i < MAX_SIZE; i++)
            container[i] = '_';
    // setteamos los valores que tendrá por defecto        
    isProducer = true;
    stopExecution = false;
    srand(time(NULL));
}

Manager::~Manager() {}

void Manager::StartSimulation() {
    while (true) {
        CLEAR;
        // se obtienen datos aleatorios
        GetRandomData();

        // termina el programa al presionar la tecla ESC
        if(KBHIT())
            if(GETCH() == ESC)
                break;

        // imprime los datos y el contenedor
        PrintContainer();
        PrintStatus();

        // se evalua que el productor o consumidor puedan usar el contenedor
        if (!stopExecution)
            WorkOnContainer();
        
        SLEEP(TIME);
    }
}

void Manager::PrintStatus() {
    std::cout << std::endl << "Productor: ";
    if (producer.isSleep)
        std::cout << "esta dormido" << std::endl;
    else
        if (producer.canWork){
            std::cout << "esta trabajando" << std::endl
                      << "turnos restantes: " << producer.moves << std::endl;
        }
        else
            std::cout << "intenta trabajar" << std::endl;
    std::cout << "Consumidor: ";
    if (consumer.isSleep)
        std::cout << "esta dormido" << std::endl;
    else
        if (consumer.canWork) {
            std::cout << "esta trabajando" << std::endl
                      << "turnos restantes: " << consumer.moves << std::endl;
        }
        else
            std::cout << "intenta trabajar" << std::endl;
}

void Manager::PrintContainer() {
    std::cout << std::endl;
    for (int i = 0; i < MAX_SIZE; i++){
            std::cout << container[i] << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < MAX_SIZE; i++){
        if (i < 9)
            std::cout << i+1 << "  ";
        else
            std::cout << i+1 << " ";
 
    } 
    std::cout << std::endl;
}

void Manager::GetRandomData() {
    // se decide quien usará el contenedor de forma aleatoria
    bool randAux = (rand() % 2 == 0 ? true: false);

    // se genera un número de turnos que se usarán
    int moves = 3 + (rand() % 4);
    
    if (stopExecution && randAux != isProducer)
        stopExecution = false;

    // según el resultado del random, se usa uno u otro
    if (randAux){
        if (consumer.moves == 0) {
            isProducer = true;
            if (producer.moves == 0)
                producer.moves = moves;
            producer.isSleep = false;
            consumer.isSleep = true;
        }
    }
    else {
        if (producer.moves == 0) {
            isProducer = false;
            if (consumer.moves == 0)
                consumer.moves = moves;
            consumer.isSleep = false;
            producer.isSleep = true;
        }
    }
}

int Manager::FindNextPosition(char val, int pos) {
    for (int i = pos; i < MAX_SIZE; i++)
        if (container[i] == val)
            return i;
    for (int i = 0; i < pos; i++)
        if (container[i] == val)
            return i;
}

void Manager::WorkOnContainer() {
    
    if (isProducer) {
        if (container[producer.pos % MAX_SIZE] == '*')
            producer.pos = FindNextPosition('_', producer.pos);
        else {
            container[(producer.pos++) % MAX_SIZE] = '*';
            producer.moves = producer.moves -1;
        }
    }
    else {
        if (container[consumer.pos % MAX_SIZE] == '_')
            consumer.pos = FindNextPosition('*', consumer.pos);
        else {
            container[(consumer.pos++) % MAX_SIZE] = '_'; 
            consumer.moves = consumer.moves -1;
        }
    }

    if (IsContainerFull())
        stopExecution = true;
}

bool Manager::IsContainerFull() {
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++) 
        if (container[i] == '*')
            count++;
    // el contenedor esta lleno
    if (count == 20) {
        producer.canWork = false;
        producer.moves = 0;
        consumer.canWork = true;
        return true;
    }
    // el contenedor esta vacio
    if (count == 0) {
        producer.canWork = true;
        consumer.canWork = false;
        consumer.moves = 0;
        return true;
    }

    if (isProducer){
        producer.canWork = true;
        consumer.canWork = false;
    }
    else{
        producer.canWork = false;
        consumer.canWork = true;
    }
    return false;
}
