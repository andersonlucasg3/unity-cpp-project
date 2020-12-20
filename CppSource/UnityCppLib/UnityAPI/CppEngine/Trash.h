#pragma once

#include "UnityAPI/UnityEngine/Object.h"
#include <list>
#include <thread>
#include <semaphore.h>

using namespace UnityEngine;

namespace CppEngine {
    class Trash {
    private:
        static list<Object *> _trashBag;
        static bool _running;

        static thread _thread;
        static sem_t _incinerateSemaphore;
        static sem_t _addSemaphore;
        static sem_t _mutex;

        static void garbageDisposer();
        static void incinerate();

    public:
        static void setup();
        static void add(Object *garbage);
        static void empty();
    };
}