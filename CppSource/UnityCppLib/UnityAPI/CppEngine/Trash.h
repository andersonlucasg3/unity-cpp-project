#pragma once

#include "UnityAPI/UnityEngine/Object.h"
#include <list>
#include <thread>

using namespace UnityEngine;

namespace CppEngine {
    class Trash {
    private:
        static list<Object *> _trashBag;
        static thread _thread;
        static mutex _mutex;
        static bool _running;

        static void garbageDisposer();
        static void incinerate();

    public:
        static void setup();
        static void add(Object *garbage);
        static void empty();
    };
}