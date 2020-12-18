#include "Registry.h"

map<string, ClassConstructor> Registry::_registers = map<string, ClassConstructor>();

void Registry::reg(string_c className, ClassConstructor constructor) {
    _registers[string(className)] = constructor;
}

MonoBehaviour *Registry::create(string_c className, ManagedInstance instance, const GameObject *gameObject) {
    ClassConstructor constructor = _registers[string(className)];
    return constructor(instance, gameObject);
}
