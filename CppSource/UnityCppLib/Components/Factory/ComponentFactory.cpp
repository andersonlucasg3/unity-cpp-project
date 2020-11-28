#include "ComponentFactory.h"
#include "UnityAPI/UnityEngine/Debug.h"

using namespace UnityEngine;

namespace CppSource::Components::Factory {
    ComponentFactory *_shared = nullptr;

    ComponentFactory *ComponentFactory::Instance() {
        if (!_shared) {
            _shared = new ComponentFactory();
        }
        return _shared;
    }

    ComponentFactory::ComponentFactory() {
        _componentMap = map<string, NativeComponent *(*)()>();
    }

    NativeComponent *ComponentFactory::InstantiateHandle(const char *className) {
        return _componentMap[className]();
    }

    void ComponentFactory::RegisterComponent(const char *className, NativeComponent *(*constructor)()) {
        _componentMap[className] = constructor;
    }
}