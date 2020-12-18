#include "Registry.h"

map<string_c, Registry::ClassConstructor> Registry::_registers = map<string_c, ClassConstructor>();

void Registry::reg(string_c className, Registry::ClassConstructor constructor) {
    _registers[className] = constructor;
}

MonoBehaviour *Registry::create(string_c className, ManagedInstance instance, const GameObject *gameObject) {
    ClassConstructor constructor = _registers[className];
    return constructor(instance, gameObject);
}
