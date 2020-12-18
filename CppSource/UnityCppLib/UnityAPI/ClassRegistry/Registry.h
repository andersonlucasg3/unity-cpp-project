#pragma once

#include <map>
#include "UnityAPI/UnityEngine/MonoBehaviour.h"

using namespace std;
using namespace UnityEngine;

class Registry {
    typedef UnityEngine::MonoBehaviour *(*ClassConstructor)(ManagedInstance instance, const GameObject *gameObject);
private:
    static map<string_c, ClassConstructor> _registers;

public:
    static void reg(string_c className, ClassConstructor constructor);
    static MonoBehaviour *create(string_c className, ManagedInstance instance, const GameObject *gameObject);
};
