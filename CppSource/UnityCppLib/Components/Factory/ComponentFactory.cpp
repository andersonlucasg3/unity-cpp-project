#include "ComponentFactory.h"
#include "../../UnityAPI/UnityAPIExtern.h"

using namespace UnityEngine;

namespace CppSource::Components::Factory {
    ComponentFactory *_shared = nullptr;

    ComponentFactory *ComponentFactory::Instance() {
        if (!_shared) {
            Debug::Log("Creating new instance of the ComponentFactory");
            _shared = new ComponentFactory();
        }
        return _shared;
    }

    ComponentFactory::ComponentFactory() {
        _componentMap = map<string, NativeComponent *(*)()>();
    }

    NativeComponent *ComponentFactory::InstantiateHandle(const char *clsName) {
        string className(clsName);
        Debug::Log(className.append(" Should be instantiated").c_str());
        return _componentMap[clsName]();
    }

    void ComponentFactory::RegisterComponent(const char *clsName, NativeComponent *(*constructor)()) {
        string className(clsName);
        Debug::Log(className.append(" Registered").c_str());
        _componentMap[clsName] = constructor;
    }
}