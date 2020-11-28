#include "ComponentFactory.h"
#include "../../UnityAPI/UnityAPIExtern.h"

using namespace UnityEngine;

namespace CppSource::Components::Factory {
    ComponentFactory *_shared = nullptr;

    ComponentFactory ComponentFactory::Instance() {
        if (!_shared) {
            Debug::Log("Creating new instance of the ComponentFactory");
            _shared = new ComponentFactory();
        }
        return *_shared;
    }

    ComponentFactory::ComponentFactory() {
        _componentMap = new map<const char *, NativeComponent *(*)()>;
    }

    NativeComponent *ComponentFactory::InstantiateHandle(const char *clsName) {
        return _componentMap->find(clsName)->second();
    }

    void ComponentFactory::RegisterComponent(const char *clsName, NativeComponent *(*constructor)()) {
        Debug::Log(strcat(const_cast<char *>(clsName), " Registered"));
        _componentMap->insert(make_pair(clsName, constructor));
    }
}