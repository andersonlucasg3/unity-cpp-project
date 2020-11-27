#include "ComponentFactory.h"

namespace CppSource::Components::Factory {
    ComponentFactory *_shared = nullptr;

    ComponentFactory ComponentFactory::Instance() {
        if (!_shared) {
            _shared = new ComponentFactory();
        }
        return *_shared;
    }

    ComponentFactory::ComponentFactory() {
        _componentMap = new map<string, CustomComponent *(*)()>;
    }

    intptr_t ComponentFactory::InstantiateHandle(const string& clsName) {
        return intptr_t(_componentMap->find(clsName)->second());
    }

    void ComponentFactory::RegisterComponent(const string &clsName, CustomComponent *(*constructor)()) {
        _componentMap->insert(make_pair(clsName, constructor));
    }
}