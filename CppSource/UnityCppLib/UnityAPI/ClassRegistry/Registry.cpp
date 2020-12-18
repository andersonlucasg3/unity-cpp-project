#include "Registry.h"

map<string_c, ClassConstructor> Registry::_registers = map<string_c, ClassConstructor>();

void Registry::reg(string_c className, ClassConstructor constructor) {
    _registers[className] = constructor;
}

MonoBehaviour *Registry::create(string_c className, ManagedInstance instance, const GameObject *gameObject) {
    ClassConstructor constructor = _registers[className];
    return constructor(instance, gameObject);
}
