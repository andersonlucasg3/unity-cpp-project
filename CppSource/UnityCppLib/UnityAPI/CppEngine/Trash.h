#pragma once

#include "UnityAPI/UnityEngine/Object.h"
#include <list>
#include <thread>

using namespace UnityEngine;

namespace CppEngine {
    class Trash {
    private:
        static list<Object *> _trashBag;
        static bool _running;

        static thread _thread;
        static mutex _trashBarMutex;
        static mutex _runningMutex;

        static void garbageDisposer();
        static void incinerate();

    public:
        static void setup();
        static void add(Object *garbage);
        static void empty();
    };
}