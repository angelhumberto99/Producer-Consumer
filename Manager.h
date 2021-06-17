#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <time.h>
#include "Cursor.h"
#define MAX_SIZE 20
#define ESC 27
#define TIME 1000

struct Individual {
    bool isSleep;
    int pos;
    bool canWork;
    int moves;
    Individual() {
        canWork = false;
        isSleep = false;
        pos = 0;
        moves = 0;
    }
};

class Manager {
    private:
        char container[MAX_SIZE];
        Individual producer;
        Individual consumer;
        bool isProducer;
        bool stopExecution;

        int FindNextPosition(char val, int pos);
        bool IsContainerFull();
        void PrintStatus();
        void PrintContainer();
        void WorkOnContainer();
        void GetRandomData();
    public:
        Manager();
        ~Manager();
        void StartSimulation();

};

#endif // MANAGER_H