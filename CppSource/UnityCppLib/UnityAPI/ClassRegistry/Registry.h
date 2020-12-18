#pragma once

#include <map>
#include "UnityAPI/UnityEngine/MonoBehaviour.h"

using namespace std;
using namespace UnityEngine;

typedef MonoBehaviour *(*ClassConstructor)(ManagedInstance instance, const GameObject *gameObject);

class Registry {
private:
    static map<string, ClassConstructor> _registers;

public:
    static void reg(string_c className, ClassConstructor constructor);
    static MonoBehaviour *create(string_c className, ManagedInstance instance, const GameObject *gameObject);
};
